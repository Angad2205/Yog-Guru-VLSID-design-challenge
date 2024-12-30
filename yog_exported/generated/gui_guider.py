# Copyright 2024 NXP
# NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
# accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
# activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
# comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
# terms, then you may not retain, install, activate or otherwise use the software.

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct
import fs_driver

lv.init()
SDL.init(w=1280,h=720)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(1280*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 1280
disp_drv.ver_res = 720
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init()
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

fs_drv = lv.fs_drv_t()
fs_driver.fs_register(fs_drv, 'Z')

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def anim_width_cb(obj, v):
    obj.set_width(v)

def anim_height_cb(obj, v):
    obj.set_height(v)

def anim_img_zoom_cb(obj, v):
    obj.set_zoom(v)

def anim_img_rotate_cb(obj, v):
    obj.set_angle(v)

global_font_cache = {}
def test_font(font_family, font_size):
    global global_font_cache
    if font_family + str(font_size) in global_font_cache:
        return global_font_cache[font_family + str(font_size)]
    if font_size % 2:
        candidates = [
            (font_family, font_size),
            (font_family, font_size-font_size%2),
            (font_family, font_size+font_size%2),
            ("montserrat", font_size-font_size%2),
            ("montserrat", font_size+font_size%2),
            ("montserrat", 16)
        ]
    else:
        candidates = [
            (font_family, font_size),
            ("montserrat", font_size),
            ("montserrat", 16)
        ]
    for (family, size) in candidates:
        try:
            if eval(f'lv.font_{family}_{size}'):
                global_font_cache[font_family + str(font_size)] = eval(f'lv.font_{family}_{size}')
                if family != font_family or size != font_size:
                    print(f'WARNING: lv.font_{family}_{size} is used!')
                return eval(f'lv.font_{family}_{size}')
        except AttributeError:
            try:
                load_font = lv.font_load(f"Z:MicroPython/lv_font_{family}_{size}.fnt")
                global_font_cache[font_family + str(font_size)] = load_font
                return load_font
            except:
                if family == font_family and size == font_size:
                    print(f'WARNING: lv.font_{family}_{size} is NOT supported!')

global_image_cache = {}
def load_image(file):
    global global_image_cache
    if file in global_image_cache:
        return global_image_cache[file]
    try:
        with open(file,'rb') as f:
            data = f.read()
    except:
        print(f'Could not open {file}')
        sys.exit()

    img = lv.img_dsc_t({
        'data_size': len(data),
        'data': data
    })
    global_image_cache[file] = img
    return img

def calendar_event_handler(e,obj):
    code = e.get_code()

    if code == lv.EVENT.VALUE_CHANGED:
        source = e.get_current_target()
        date = lv.calendar_date_t()
        if source.get_pressed_date(date) == lv.RES.OK:
            source.set_highlighted_dates([date], 1)

def spinbox_increment_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.increment()
def spinbox_decrement_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.decrement()

def digital_clock_cb(timer, obj, current_time, show_second, use_ampm):
    hour = int(current_time[0])
    minute = int(current_time[1])
    second = int(current_time[2])
    ampm = current_time[3]
    second = second + 1
    if second == 60:
        second = 0
        minute = minute + 1
        if minute == 60:
            minute = 0
            hour = hour + 1
            if use_ampm:
                if hour == 12:
                    if ampm == 'AM':
                        ampm = 'PM'
                    elif ampm == 'PM':
                        ampm = 'AM'
                if hour > 12:
                    hour = hour % 12
    hour = hour % 24
    if use_ampm:
        if show_second:
            obj.set_text("%02d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%02d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%02d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%02d:%02d" %(hour, minute))
    current_time[0] = hour
    current_time[1] = minute
    current_time[2] = second
    current_time[3] = ampm

def analog_clock_cb(timer, obj):
    datetime = time.localtime()
    hour = datetime[3]
    if hour >= 12: hour = hour - 12
    obj.set_time(hour, datetime[4], datetime[5])

def datetext_event_handler(e, obj):
    code = e.get_code()
    target = e.get_target()
    if code == lv.EVENT.FOCUSED:
        if obj is None:
            bg = lv.layer_top()
            bg.add_flag(lv.obj.FLAG.CLICKABLE)
            obj = lv.calendar(bg)
            scr = target.get_screen()
            scr_height = scr.get_height()
            scr_width = scr.get_width()
            obj.set_size(int(scr_width * 0.8), int(scr_height * 0.8))
            datestring = target.get_text()
            year = int(datestring.split('/')[0])
            month = int(datestring.split('/')[1])
            day = int(datestring.split('/')[2])
            obj.set_showed_date(year, month)
            highlighted_days=[lv.calendar_date_t({'year':year, 'month':month, 'day':day})]
            obj.set_highlighted_dates(highlighted_days, 1)
            obj.align(lv.ALIGN.CENTER, 0, 0)
            lv.calendar_header_arrow(obj)
            obj.add_event_cb(lambda e: datetext_calendar_event_handler(e, target), lv.EVENT.ALL, None)
            scr.update_layout()

def datetext_calendar_event_handler(e, obj):
    code = e.get_code()
    target = e.get_current_target()
    if code == lv.EVENT.VALUE_CHANGED:
        date = lv.calendar_date_t()
        if target.get_pressed_date(date) == lv.RES.OK:
            obj.set_text(f"{date.year}/{date.month}/{date.day}")
            bg = lv.layer_top()
            bg.clear_flag(lv.obj.FLAG.CLICKABLE)
            bg.set_style_bg_opa(lv.OPA.TRANSP, 0)
            target.delete()

def menuDemo_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def home_screen_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def Yoga_selection_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def about_us_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def hastaa_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def padmasan_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def vrikshasan_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def qr_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def padma_intro_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def vriks_intro_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def has_intro_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def progress_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

# Create menuDemo
menuDemo = lv.obj()
menuDemo.set_size(1280, 720)
menuDemo.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_dashboard_menu
menuDemo_dashboard_menu = lv.menu(menuDemo)
menuDemo_dashboard_menu_sidebar_page = lv.menu_page(menuDemo_dashboard_menu, "Settings")
menuDemo_dashboard_menu.set_sidebar_page(menuDemo_dashboard_menu_sidebar_page)
menuDemo_dashboard_menu_subpage_0 = lv.menu_page(menuDemo_dashboard_menu, None)
menuDemo_dashboard_menu_cont_0 = lv.menu_cont(menuDemo_dashboard_menu_sidebar_page)
menuDemo_dashboard_menu_label_0 = lv.label(menuDemo_dashboard_menu_cont_0)
menuDemo_dashboard_menu_label_0.set_text("Battery")
menuDemo_dashboard_menu_label_0.set_size(lv.pct(100), lv.SIZE.CONTENT)
menuDemo_dashboard_menu.set_load_page_event(menuDemo_dashboard_menu_cont_0, menuDemo_dashboard_menu_subpage_0)
menuDemo_dashboard_menu_subpage_1 = lv.menu_page(menuDemo_dashboard_menu, None)
menuDemo_dashboard_menu_cont_1 = lv.menu_cont(menuDemo_dashboard_menu_sidebar_page)
menuDemo_dashboard_menu_label_1 = lv.label(menuDemo_dashboard_menu_cont_1)
menuDemo_dashboard_menu_label_1.set_text("Yoga suggestion")
menuDemo_dashboard_menu_label_1.set_size(lv.pct(100), lv.SIZE.CONTENT)
menuDemo_dashboard_menu.set_load_page_event(menuDemo_dashboard_menu_cont_1, menuDemo_dashboard_menu_subpage_1)
menuDemo_dashboard_menu_subpage_2 = lv.menu_page(menuDemo_dashboard_menu, None)
menuDemo_dashboard_menu_cont_2 = lv.menu_cont(menuDemo_dashboard_menu_sidebar_page)
menuDemo_dashboard_menu_label_2 = lv.label(menuDemo_dashboard_menu_cont_2)
menuDemo_dashboard_menu_label_2.set_text("Call Support")
menuDemo_dashboard_menu_label_2.set_size(lv.pct(100), lv.SIZE.CONTENT)
menuDemo_dashboard_menu.set_load_page_event(menuDemo_dashboard_menu_cont_2, menuDemo_dashboard_menu_subpage_2)
menuDemo_dashboard_menu_subpage_3 = lv.menu_page(menuDemo_dashboard_menu, None)
menuDemo_dashboard_menu_cont_3 = lv.menu_cont(menuDemo_dashboard_menu_sidebar_page)
menuDemo_dashboard_menu_label_3 = lv.label(menuDemo_dashboard_menu_cont_3)
menuDemo_dashboard_menu_label_3.set_text("")
menuDemo_dashboard_menu_label_3.set_size(lv.pct(100), lv.SIZE.CONTENT)
menuDemo_dashboard_menu.set_load_page_event(menuDemo_dashboard_menu_cont_3, menuDemo_dashboard_menu_subpage_3)
menuDemo_dashboard_menu.set_pos(0, 0)
menuDemo_dashboard_menu.set_size(1280, 720)
menuDemo_dashboard_menu.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_dashboard_menu, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_dashboard_menu.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_dashboard_menu.set_style_bg_color(lv.color_hex(0x082142), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_dashboard_menu.set_style_bg_grad_dir(lv.GRAD_DIR.HOR, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_dashboard_menu.set_style_bg_grad_color(lv.color_hex(0x2b1979), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_dashboard_menu.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_dashboard_menu.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for menuDemo_dashboard_menu, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_menuDemo_dashboard_menu_extra_sidebar_page_main_default = lv.style_t()
style_menuDemo_dashboard_menu_extra_sidebar_page_main_default.init()
style_menuDemo_dashboard_menu_extra_sidebar_page_main_default.set_bg_opa(0)
style_menuDemo_dashboard_menu_extra_sidebar_page_main_default.set_radius(0)
menuDemo_dashboard_menu_sidebar_page.add_style(style_menuDemo_dashboard_menu_extra_sidebar_page_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for menuDemo_dashboard_menu, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_menuDemo_dashboard_menu_extra_option_btns_main_default = lv.style_t()
style_menuDemo_dashboard_menu_extra_option_btns_main_default.init()
style_menuDemo_dashboard_menu_extra_option_btns_main_default.set_text_color(lv.color_hex(0xffffff))
style_menuDemo_dashboard_menu_extra_option_btns_main_default.set_text_font(test_font("montserratMedium", 42))
style_menuDemo_dashboard_menu_extra_option_btns_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_menuDemo_dashboard_menu_extra_option_btns_main_default.set_pad_top(10)
style_menuDemo_dashboard_menu_extra_option_btns_main_default.set_pad_bottom(10)
menuDemo_dashboard_menu_cont_0.add_style(style_menuDemo_dashboard_menu_extra_option_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_dashboard_menu_cont_1.add_style(style_menuDemo_dashboard_menu_extra_option_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_dashboard_menu_cont_2.add_style(style_menuDemo_dashboard_menu_extra_option_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_dashboard_menu_cont_3.add_style(style_menuDemo_dashboard_menu_extra_option_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for menuDemo_dashboard_menu, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
style_menuDemo_dashboard_menu_extra_option_btns_main_checked = lv.style_t()
style_menuDemo_dashboard_menu_extra_option_btns_main_checked.init()
style_menuDemo_dashboard_menu_extra_option_btns_main_checked.set_text_color(lv.color_hex(0xa5efff))
style_menuDemo_dashboard_menu_extra_option_btns_main_checked.set_text_font(test_font("montserratMedium", 42))
style_menuDemo_dashboard_menu_extra_option_btns_main_checked.set_text_align(lv.TEXT_ALIGN.CENTER)
style_menuDemo_dashboard_menu_extra_option_btns_main_checked.set_border_width(0)
style_menuDemo_dashboard_menu_extra_option_btns_main_checked.set_radius(0)
style_menuDemo_dashboard_menu_extra_option_btns_main_checked.set_bg_opa(255)
style_menuDemo_dashboard_menu_extra_option_btns_main_checked.set_bg_color(lv.color_hex(0x253853))
style_menuDemo_dashboard_menu_extra_option_btns_main_checked.set_bg_grad_dir(lv.GRAD_DIR.HOR)
style_menuDemo_dashboard_menu_extra_option_btns_main_checked.set_bg_grad_color(lv.color_hex(0x162d4d))
menuDemo_dashboard_menu_cont_0.add_style(style_menuDemo_dashboard_menu_extra_option_btns_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)
menuDemo_dashboard_menu_cont_1.add_style(style_menuDemo_dashboard_menu_extra_option_btns_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)
menuDemo_dashboard_menu_cont_2.add_style(style_menuDemo_dashboard_menu_extra_option_btns_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)
menuDemo_dashboard_menu_cont_3.add_style(style_menuDemo_dashboard_menu_extra_option_btns_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for menuDemo_dashboard_menu, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_menuDemo_dashboard_menu_extra_main_title_main_default = lv.style_t()
style_menuDemo_dashboard_menu_extra_main_title_main_default.init()
style_menuDemo_dashboard_menu_extra_main_title_main_default.set_text_color(lv.color_hex(0x6a94b6))
style_menuDemo_dashboard_menu_extra_main_title_main_default.set_text_font(test_font("Alatsi_Regular", 47))
style_menuDemo_dashboard_menu_extra_main_title_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_menuDemo_dashboard_menu_extra_main_title_main_default.set_bg_opa(0)
style_menuDemo_dashboard_menu_extra_main_title_main_default.set_pad_top(10)
style_menuDemo_dashboard_menu_extra_main_title_main_default.set_pad_bottom(10)
menuDemo_dashboard_menu_title = menuDemo_dashboard_menu.get_child(0)
menuDemo_dashboard_menu_title.set_size(lv.pct(100), lv.SIZE.CONTENT)
menuDemo_dashboard_menu.get_sidebar_header().add_style(style_menuDemo_dashboard_menu_extra_main_title_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_battery_label
menuDemo_battery_label = lv.label(menuDemo_dashboard_menu_subpage_0)
menuDemo_battery_label.set_text("The Battery Condition")
menuDemo_battery_label.set_long_mode(lv.label.LONG.WRAP)
menuDemo_battery_label.set_pos(240, 161)
menuDemo_battery_label.set_size(744, 248)
menuDemo_battery_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_battery_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_battery_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_text_font(test_font("montserratMedium", 52), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_pad_top(27, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_battery_img
menuDemo_battery_img = lv.img(menuDemo_dashboard_menu_subpage_0)
menuDemo_battery_img.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\battery_530_195.png"))
menuDemo_battery_img.add_flag(lv.obj.FLAG.CLICKABLE)
menuDemo_battery_img.set_pivot(50,50)
menuDemo_battery_img.set_angle(0)
menuDemo_battery_img.set_pos(293, 243)
menuDemo_battery_img.set_size(530, 195)
menuDemo_battery_img.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_battery_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_battery_img.set_style_img_recolor_opa(143, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_img.set_style_img_recolor(lv.color_hex(0x38fe49), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_img.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_battery_spangroup
menuDemo_battery_spangroup = lv.spangroup(menuDemo_dashboard_menu_subpage_0)
menuDemo_battery_spangroup.set_align(lv.TEXT_ALIGN.LEFT)
menuDemo_battery_spangroup.set_overflow(lv.SPAN_OVERFLOW.CLIP)
menuDemo_battery_spangroup.set_mode(lv.SPAN_MODE.BREAK)
# create spans
menuDemo_battery_spangroup_span = menuDemo_battery_spangroup.new_span()
menuDemo_battery_spangroup_span.set_text("Distance :    ")
menuDemo_battery_spangroup_span.style.set_text_color(lv.color_hex(0xd3e8ff))
menuDemo_battery_spangroup_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
menuDemo_battery_spangroup_span.style.set_text_font(test_font("Alatsi_Regular", 20))
menuDemo_battery_spangroup_span = menuDemo_battery_spangroup.new_span()
menuDemo_battery_spangroup_span.set_text("267 ")
menuDemo_battery_spangroup_span.style.set_text_color(lv.color_hex(0x5dfd44))
menuDemo_battery_spangroup_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
menuDemo_battery_spangroup_span.style.set_text_font(test_font("Alatsi_Regular", 45))
menuDemo_battery_spangroup_span = menuDemo_battery_spangroup.new_span()
menuDemo_battery_spangroup_span.set_text(" Km")
menuDemo_battery_spangroup_span.style.set_text_color(lv.color_hex(0xd3e8ff))
menuDemo_battery_spangroup_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
menuDemo_battery_spangroup_span.style.set_text_font(test_font("Alatsi_Regular", 20))
menuDemo_battery_spangroup.set_pos(410, 640)
menuDemo_battery_spangroup.set_size(640, 238)
menuDemo_battery_spangroup.refr_mode()
menuDemo_battery_spangroup.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_battery_spangroup, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_battery_spangroup.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_spangroup.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_spangroup.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_spangroup.set_style_pad_top(25, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_spangroup.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_spangroup.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_spangroup.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_battery_spangroup.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_radio_spangroup
menuDemo_radio_spangroup = lv.spangroup(menuDemo_dashboard_menu_subpage_1)
menuDemo_radio_spangroup.set_align(lv.TEXT_ALIGN.LEFT)
menuDemo_radio_spangroup.set_overflow(lv.SPAN_OVERFLOW.CLIP)
menuDemo_radio_spangroup.set_mode(lv.SPAN_MODE.BREAK)
# create spans
menuDemo_radio_spangroup_span = menuDemo_radio_spangroup.new_span()
menuDemo_radio_spangroup_span.set_text("104.0")
menuDemo_radio_spangroup_span.style.set_text_color(lv.color_hex(0xffffff))
menuDemo_radio_spangroup_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
menuDemo_radio_spangroup_span.style.set_text_font(test_font("Alatsi_Regular", 40))
menuDemo_radio_spangroup.set_pos(543, -4)
menuDemo_radio_spangroup.set_size(184, 266)
menuDemo_radio_spangroup.refr_mode()
menuDemo_radio_spangroup.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_radio_spangroup, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_radio_spangroup.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_spangroup.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_spangroup.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_spangroup.set_style_pad_top(37, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_spangroup.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_spangroup.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_spangroup.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_spangroup.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_radio_label
menuDemo_radio_label = lv.label(menuDemo_dashboard_menu_subpage_1)
menuDemo_radio_label.set_text("Yoga Poses")
menuDemo_radio_label.set_long_mode(lv.label.LONG.WRAP)
menuDemo_radio_label.set_pos(324, 264)
menuDemo_radio_label.set_size(245, 108)
menuDemo_radio_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_radio_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_radio_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_text_color(lv.color_hex(0xb8b8b8), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_text_font(test_font("Alatsi_Regular", 37), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_text_align(lv.TEXT_ALIGN.RIGHT, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_pad_right(30, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_radio_slider
menuDemo_radio_slider = lv.slider(menuDemo_dashboard_menu_subpage_1)
menuDemo_radio_slider.set_range(0,90)
menuDemo_radio_slider.set_value(40, False)
menuDemo_radio_slider.set_pos(48, 381)
menuDemo_radio_slider.set_size(800, 214)
menuDemo_radio_slider.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_radio_slider, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_radio_slider.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_slider.set_style_radius(133, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_slider.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_slider.set_style_bg_img_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\radio_bg_800_214.png"), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_slider.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_radio_slider.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for menuDemo_radio_slider, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
menuDemo_radio_slider.set_style_bg_opa(0, lv.PART.INDICATOR|lv.STATE.DEFAULT)
menuDemo_radio_slider.set_style_radius(133, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for menuDemo_radio_slider, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
menuDemo_radio_slider.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DEFAULT)
menuDemo_radio_slider.set_style_bg_img_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\radio_play_214_214.png"), lv.PART.KNOB|lv.STATE.DEFAULT)
menuDemo_radio_slider.set_style_bg_img_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
menuDemo_radio_slider.set_style_radius(133, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create menuDemo_phone_label
menuDemo_phone_label = lv.label(menuDemo_dashboard_menu_subpage_2)
menuDemo_phone_label.set_text("")
menuDemo_phone_label.set_long_mode(lv.label.LONG.WRAP)
menuDemo_phone_label.set_pos(150, 0)
menuDemo_phone_label.set_size(597, 135)
menuDemo_phone_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_phone_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_phone_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_text_font(test_font("Alatsi_Regular", 52), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_pad_top(15, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_phone_btnm
menuDemo_phone_btnm = lv.btnmatrix(menuDemo_dashboard_menu_subpage_2)
menuDemo_phone_btnm_text_map = ["1", "2", "3", "\n", "4", "5", "6", "\n", "7", "8", "9", "\n", "#", "+", "%", "",]
menuDemo_phone_btnm.set_map(menuDemo_phone_btnm_text_map)
menuDemo_phone_btnm.set_pos(230, 135)
menuDemo_phone_btnm.set_size(437, 468)
menuDemo_phone_btnm.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_phone_btnm, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_phone_btnm.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_pad_bottom(8, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_pad_row(4, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_pad_column(20, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_radius(88, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for menuDemo_phone_btnm, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
menuDemo_phone_btnm.set_style_border_width(0, lv.PART.ITEMS|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_text_color(lv.color_hex(0x9a9a9a), lv.PART.ITEMS|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_text_font(test_font("montserratMedium", 37), lv.PART.ITEMS|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_radius(90, lv.PART.ITEMS|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_bg_opa(255, lv.PART.ITEMS|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_bg_color(lv.color_hex(0x0e2537), lv.PART.ITEMS|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_bg_grad_dir(lv.GRAD_DIR.VER, lv.PART.ITEMS|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_bg_grad_color(lv.color_hex(0x52687b), lv.PART.ITEMS|lv.STATE.DEFAULT)
menuDemo_phone_btnm.set_style_shadow_width(0, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for menuDemo_phone_btnm, Part: lv.PART.ITEMS, State: lv.STATE.PRESSED.
menuDemo_phone_btnm.set_style_border_width(0, lv.PART.ITEMS|lv.STATE.PRESSED)
menuDemo_phone_btnm.set_style_text_color(lv.color_hex(0x6e6505), lv.PART.ITEMS|lv.STATE.PRESSED)
menuDemo_phone_btnm.set_style_text_font(test_font("Alatsi_Regular", 63), lv.PART.ITEMS|lv.STATE.PRESSED)
menuDemo_phone_btnm.set_style_radius(109, lv.PART.ITEMS|lv.STATE.PRESSED)
menuDemo_phone_btnm.set_style_bg_opa(255, lv.PART.ITEMS|lv.STATE.PRESSED)
menuDemo_phone_btnm.set_style_bg_color(lv.color_hex(0x536c80), lv.PART.ITEMS|lv.STATE.PRESSED)
menuDemo_phone_btnm.set_style_bg_grad_dir(lv.GRAD_DIR.VER, lv.PART.ITEMS|lv.STATE.PRESSED)
menuDemo_phone_btnm.set_style_bg_grad_color(lv.color_hex(0xd0d0d0), lv.PART.ITEMS|lv.STATE.PRESSED)
menuDemo_phone_btnm.set_style_shadow_width(0, lv.PART.ITEMS|lv.STATE.PRESSED)

# Create menuDemo_imgbtn_call
menuDemo_imgbtn_call = lv.imgbtn(menuDemo_dashboard_menu_subpage_2)
menuDemo_imgbtn_call.add_flag(lv.obj.FLAG.CHECKABLE)
menuDemo_imgbtn_call.set_src(lv.imgbtn.STATE.RELEASED, None, load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\phone_card_98_95.png"), None)
menuDemo_imgbtn_call.set_src(lv.imgbtn.STATE.PRESSED, None, load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\phone_card_98_95.png"), None)
menuDemo_imgbtn_call.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\end_call_98_95.png"), None)
menuDemo_imgbtn_call.set_src(lv.imgbtn.STATE.CHECKED_PRESSED, None, load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\end_call_98_95.png"), None)
menuDemo_imgbtn_call.add_flag(lv.obj.FLAG.CHECKABLE)
menuDemo_imgbtn_call_label = lv.label(menuDemo_imgbtn_call)
menuDemo_imgbtn_call_label.set_text("")
menuDemo_imgbtn_call_label.set_long_mode(lv.label.LONG.WRAP)
menuDemo_imgbtn_call_label.align(lv.ALIGN.CENTER, 0, 0)
menuDemo_imgbtn_call.set_style_pad_all(0, lv.STATE.DEFAULT)
menuDemo_imgbtn_call.set_pos(397, 603)
menuDemo_imgbtn_call.set_size(98, 95)
menuDemo_imgbtn_call.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_imgbtn_call, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_imgbtn_call.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_imgbtn_call.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_imgbtn_call.set_style_text_font(test_font("montserratMedium", 31), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_imgbtn_call.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_imgbtn_call.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for menuDemo_imgbtn_call, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
menuDemo_imgbtn_call.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
menuDemo_imgbtn_call.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
menuDemo_imgbtn_call.set_style_text_font(test_font("montserratMedium", 31), lv.PART.MAIN|lv.STATE.PRESSED)
menuDemo_imgbtn_call.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for menuDemo_imgbtn_call, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
menuDemo_imgbtn_call.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
menuDemo_imgbtn_call.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
menuDemo_imgbtn_call.set_style_text_font(test_font("montserratMedium", 31), lv.PART.MAIN|lv.STATE.CHECKED)
menuDemo_imgbtn_call.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)

# Create menuDemo_conditioner_label
menuDemo_conditioner_label = lv.label(menuDemo_dashboard_menu_subpage_3)
menuDemo_conditioner_label.set_text("Conditioner Mode")
menuDemo_conditioner_label.set_long_mode(lv.label.LONG.WRAP)
menuDemo_conditioner_label.set_pos(8, -2)
menuDemo_conditioner_label.set_size(880, 248)
menuDemo_conditioner_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_conditioner_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_conditioner_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_text_font(test_font("montserratMedium", 74), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_pad_top(36, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_conditioner_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_label_1
menuDemo_label_1 = lv.label(menuDemo_dashboard_menu_subpage_3)
menuDemo_label_1.set_text("")
menuDemo_label_1.set_long_mode(lv.label.LONG.WRAP)
menuDemo_label_1.set_pos(480, -283)
menuDemo_label_1.set_size(706, 161)
menuDemo_label_1.add_flag(lv.obj.FLAG.HIDDEN)
menuDemo_label_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_text_font(test_font("montserratMedium", 92), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_mode
menuDemo_mode = lv.carousel(menuDemo_dashboard_menu_subpage_3)
menuDemo_mode.set_element_width(120)
menuDemo_mode.set_size(621, 317)
menuDemo_mode_mode_1 = menuDemo_mode.add_element(0)
menuDemo_mode_mode_2 = menuDemo_mode.add_element(1)
menuDemo_mode_mode_3 = menuDemo_mode.add_element(2)
menuDemo_mode.set_pos(0, 0)
menuDemo_mode.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_mode, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_mode.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_mode.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_mode.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for menuDemo_mode, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
menuDemo_mode.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
menuDemo_mode.set_style_bg_color(lv.color_hex(0xcccccc), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
menuDemo_mode.set_style_radius(0, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
# Set style for menuDemo_mode, Part: lv.PART.ITEMS, State: lv.STATE.DEFAULT.
style_menuDemo_mode_extra_element_items_default = lv.style_t()
style_menuDemo_mode_extra_element_items_default.init()
style_menuDemo_mode_extra_element_items_default.set_bg_opa(0)
style_menuDemo_mode_extra_element_items_default.set_outline_width(0)
style_menuDemo_mode_extra_element_items_default.set_border_width(0)
style_menuDemo_mode_extra_element_items_default.set_radius(13)
style_menuDemo_mode_extra_element_items_default.set_shadow_width(0)
menuDemo_mode_mode_3.add_style(style_menuDemo_mode_extra_element_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
menuDemo_mode_mode_2.add_style(style_menuDemo_mode_extra_element_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
menuDemo_mode_mode_1.add_style(style_menuDemo_mode_extra_element_items_default, lv.PART.ITEMS|lv.STATE.DEFAULT)
# Set style for menuDemo_mode, Part: lv.PART.ITEMS, State: lv.STATE.FOCUSED.
style_menuDemo_mode_extra_element_items_focused = lv.style_t()
style_menuDemo_mode_extra_element_items_focused.init()
style_menuDemo_mode_extra_element_items_focused.set_bg_opa(0)
style_menuDemo_mode_extra_element_items_focused.set_outline_width(0)
style_menuDemo_mode_extra_element_items_focused.set_border_width(0)
style_menuDemo_mode_extra_element_items_focused.set_radius(53)
style_menuDemo_mode_extra_element_items_focused.set_shadow_width(50)
style_menuDemo_mode_extra_element_items_focused.set_shadow_color(lv.color_hex(0xfffea9))
style_menuDemo_mode_extra_element_items_focused.set_shadow_opa(255)
style_menuDemo_mode_extra_element_items_focused.set_shadow_spread(2)
style_menuDemo_mode_extra_element_items_focused.set_shadow_ofs_x(0)
style_menuDemo_mode_extra_element_items_focused.set_shadow_ofs_y(0)
menuDemo_mode_mode_3.add_style(style_menuDemo_mode_extra_element_items_focused, lv.PART.ITEMS|lv.STATE.FOCUSED)
menuDemo_mode_mode_2.add_style(style_menuDemo_mode_extra_element_items_focused, lv.PART.ITEMS|lv.STATE.FOCUSED)
menuDemo_mode_mode_1.add_style(style_menuDemo_mode_extra_element_items_focused, lv.PART.ITEMS|lv.STATE.FOCUSED)

# Create menuDemo_mode_img_1
menuDemo_mode_img_1 = lv.img(menuDemo_mode_mode_1)
menuDemo_mode_img_1.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\mode1_211_211.png"))
menuDemo_mode_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
menuDemo_mode_img_1.set_pivot(50,50)
menuDemo_mode_img_1.set_angle(0)
menuDemo_mode_img_1.set_pos(53, 52)
menuDemo_mode_img_1.set_size(211, 211)
menuDemo_mode_img_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_mode_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_mode_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_mode_img_2
menuDemo_mode_img_2 = lv.img(menuDemo_mode_mode_2)
menuDemo_mode_img_2.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\mode2_211_211.png"))
menuDemo_mode_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
menuDemo_mode_img_2.set_pivot(50,50)
menuDemo_mode_img_2.set_angle(0)
menuDemo_mode_img_2.set_pos(53, 52)
menuDemo_mode_img_2.set_size(211, 211)
menuDemo_mode_img_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_mode_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_mode_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_mode_img_3
menuDemo_mode_img_3 = lv.img(menuDemo_mode_mode_3)
menuDemo_mode_img_3.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\mode3_211_211.png"))
menuDemo_mode_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
menuDemo_mode_img_3.set_pivot(50,50)
menuDemo_mode_img_3.set_angle(0)
menuDemo_mode_img_3.set_pos(66, 66)
menuDemo_mode_img_3.set_size(211, 211)
menuDemo_mode_img_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_mode_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_mode_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_btn_del
menuDemo_btn_del = lv.btn(menuDemo)
menuDemo_btn_del_label = lv.label(menuDemo_btn_del)
menuDemo_btn_del_label.set_text("")
menuDemo_btn_del_label.set_long_mode(lv.label.LONG.WRAP)
menuDemo_btn_del_label.align(lv.ALIGN.CENTER, 0, 0)
menuDemo_btn_del.set_style_pad_all(0, lv.STATE.DEFAULT)
menuDemo_btn_del.set_pos(1104, 34)
menuDemo_btn_del.set_size(74, 68)
menuDemo_btn_del.add_flag(lv.obj.FLAG.HIDDEN)
menuDemo_btn_del.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_btn_del, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_btn_del.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_btn_del.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_btn_del.set_style_radius(13, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_btn_del.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_btn_del.set_style_bg_img_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\delete_74_68.png"), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_btn_del.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_btn_del.set_style_bg_img_recolor(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_btn_del.set_style_bg_img_recolor_opa(166, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_btn_del.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_btn_del.set_style_text_font(test_font("montserratMedium", 47), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_btn_del.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_phone_calling
menuDemo_phone_calling = lv.label(menuDemo)
menuDemo_phone_calling.set_text("Calling...")
menuDemo_phone_calling.set_long_mode(lv.label.LONG.WRAP)
menuDemo_phone_calling.set_pos(672, 262)
menuDemo_phone_calling.set_size(344, 145)
menuDemo_phone_calling.add_flag(lv.obj.FLAG.HIDDEN)
menuDemo_phone_calling.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_phone_calling, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_phone_calling.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_text_font(test_font("Alatsi_Regular", 60), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_calling.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_phone_callnum
menuDemo_phone_callnum = lv.label(menuDemo)
menuDemo_phone_callnum.set_text("")
menuDemo_phone_callnum.set_long_mode(lv.label.LONG.WRAP)
menuDemo_phone_callnum.set_pos(408, 132)
menuDemo_phone_callnum.set_size(826, 145)
menuDemo_phone_callnum.add_flag(lv.obj.FLAG.HIDDEN)
menuDemo_phone_callnum.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_phone_callnum, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_phone_callnum.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_text_font(test_font("Alatsi_Regular", 92), lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
menuDemo_phone_callnum.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create menuDemo_img_1
menuDemo_img_1 = lv.img(menuDemo)
menuDemo_img_1.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\BABA_323_308.png"))
menuDemo_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
menuDemo_img_1.set_pivot(50,50)
menuDemo_img_1.set_angle(0)
menuDemo_img_1.set_pos(27, 366)
menuDemo_img_1.set_size(323, 308)
menuDemo_img_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for menuDemo_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
menuDemo_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

menuDemo.update_layout()
# Create home_screen
home_screen = lv.obj()
home_screen.set_size(1280, 720)
home_screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for home_screen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
home_screen.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create home_screen_img_1
home_screen_img_1 = lv.img(home_screen)
home_screen_img_1.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\Yog_1282_721.png"))
home_screen_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
home_screen_img_1.set_pivot(50,50)
home_screen_img_1.set_angle(0)
home_screen_img_1.set_pos(-1, 0)
home_screen_img_1.set_size(1282, 721)
home_screen_img_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for home_screen_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
home_screen_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

home_screen.update_layout()
# Create Yoga_selection
Yoga_selection = lv.obj()
Yoga_selection.set_size(1280, 720)
Yoga_selection.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_img_1
Yoga_selection_img_1 = lv.img(Yoga_selection)
Yoga_selection_img_1.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\16_1280_721.png"))
Yoga_selection_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
Yoga_selection_img_1.set_pivot(50,50)
Yoga_selection_img_1.set_angle(0)
Yoga_selection_img_1.set_pos(0, 0)
Yoga_selection_img_1.set_size(1280, 721)
Yoga_selection_img_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_img_2
Yoga_selection_img_2 = lv.img(Yoga_selection)
Yoga_selection_img_2.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\408_129_76.png"))
Yoga_selection_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
Yoga_selection_img_2.set_pivot(50,50)
Yoga_selection_img_2.set_angle(0)
Yoga_selection_img_2.set_pos(-19, 448)
Yoga_selection_img_2.set_size(129, 76)
Yoga_selection_img_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_img_5
Yoga_selection_img_5 = lv.img(Yoga_selection)
Yoga_selection_img_5.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\405_86_57.png"))
Yoga_selection_img_5.add_flag(lv.obj.FLAG.CLICKABLE)
Yoga_selection_img_5.set_pivot(50,50)
Yoga_selection_img_5.set_angle(0)
Yoga_selection_img_5.set_pos(6, 102)
Yoga_selection_img_5.set_size(86, 57)
Yoga_selection_img_5.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_img_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_img_5.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_img_6
Yoga_selection_img_6 = lv.img(Yoga_selection)
Yoga_selection_img_6.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\400_97_65.png"))
Yoga_selection_img_6.add_flag(lv.obj.FLAG.CLICKABLE)
Yoga_selection_img_6.set_pivot(50,50)
Yoga_selection_img_6.set_angle(0)
Yoga_selection_img_6.set_pos(-6, 184)
Yoga_selection_img_6.set_size(97, 65)
Yoga_selection_img_6.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_img_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_img_6.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_img_7
Yoga_selection_img_7 = lv.img(Yoga_selection)
Yoga_selection_img_7.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\403_120_74.png"))
Yoga_selection_img_7.add_flag(lv.obj.FLAG.CLICKABLE)
Yoga_selection_img_7.set_pivot(50,50)
Yoga_selection_img_7.set_angle(0)
Yoga_selection_img_7.set_pos(-5, 358)
Yoga_selection_img_7.set_size(120, 74)
Yoga_selection_img_7.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_img_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_img_7.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_img_8
Yoga_selection_img_8 = lv.img(Yoga_selection)
Yoga_selection_img_8.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\410_121_74.png"))
Yoga_selection_img_8.add_flag(lv.obj.FLAG.CLICKABLE)
Yoga_selection_img_8.set_pivot(50,50)
Yoga_selection_img_8.set_angle(0)
Yoga_selection_img_8.set_pos(-23, 1)
Yoga_selection_img_8.set_size(121, 74)
Yoga_selection_img_8.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_img_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_img_8.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_img_9
Yoga_selection_img_9 = lv.img(Yoga_selection)
Yoga_selection_img_9.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\401_89_74.png"))
Yoga_selection_img_9.add_flag(lv.obj.FLAG.CLICKABLE)
Yoga_selection_img_9.set_pivot(50,50)
Yoga_selection_img_9.set_angle(0)
Yoga_selection_img_9.set_pos(-6, 647)
Yoga_selection_img_9.set_size(89, 74)
Yoga_selection_img_9.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_img_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_img_9.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_img_10
Yoga_selection_img_10 = lv.img(Yoga_selection)
Yoga_selection_img_10.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\asan3_291_463.png"))
Yoga_selection_img_10.add_flag(lv.obj.FLAG.CLICKABLE)
Yoga_selection_img_10.set_pivot(50,50)
Yoga_selection_img_10.set_angle(0)
Yoga_selection_img_10.set_pos(315, 134)
Yoga_selection_img_10.set_size(291, 463)
Yoga_selection_img_10.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_img_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_img_10.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_img_11
Yoga_selection_img_11 = lv.img(Yoga_selection)
Yoga_selection_img_11.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\asan2_280_458.png"))
Yoga_selection_img_11.add_flag(lv.obj.FLAG.CLICKABLE)
Yoga_selection_img_11.set_pivot(50,50)
Yoga_selection_img_11.set_angle(0)
Yoga_selection_img_11.set_pos(634, 135)
Yoga_selection_img_11.set_size(280, 458)
Yoga_selection_img_11.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_img_11, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_img_11.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_img_12
Yoga_selection_img_12 = lv.img(Yoga_selection)
Yoga_selection_img_12.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\asan1_282_458.png"))
Yoga_selection_img_12.add_flag(lv.obj.FLAG.CLICKABLE)
Yoga_selection_img_12.set_pivot(50,50)
Yoga_selection_img_12.set_angle(0)
Yoga_selection_img_12.set_pos(939, 135)
Yoga_selection_img_12.set_size(282, 458)
Yoga_selection_img_12.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_img_12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_img_12.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_label_2
Yoga_selection_label_2 = lv.label(Yoga_selection)
Yoga_selection_label_2.set_text("HASTA \nUTTANASANA")
Yoga_selection_label_2.set_long_mode(lv.label.LONG.WRAP)
Yoga_selection_label_2.set_pos(643, 545)
Yoga_selection_label_2.set_size(289, 63)
Yoga_selection_label_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_text_font(test_font("montserratMedium", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_label_1
Yoga_selection_label_1 = lv.label(Yoga_selection)
Yoga_selection_label_1.set_text("VRIKSHASANA")
Yoga_selection_label_1.set_long_mode(lv.label.LONG.WRAP)
Yoga_selection_label_1.set_pos(270, 558)
Yoga_selection_label_1.set_size(397, 95)
Yoga_selection_label_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_text_color(lv.color_hex(0xffcd00), lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_text_font(test_font("montserratMedium", 33), lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Yoga_selection_label_3
Yoga_selection_label_3 = lv.label(Yoga_selection)
Yoga_selection_label_3.set_text("PADMASANA")
Yoga_selection_label_3.set_long_mode(lv.label.LONG.WRAP)
Yoga_selection_label_3.set_pos(973, 558)
Yoga_selection_label_3.set_size(230, 36)
Yoga_selection_label_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Yoga_selection_label_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Yoga_selection_label_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_text_font(test_font("montserratMedium", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Yoga_selection_label_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

Yoga_selection.update_layout()
# Create about_us
about_us = lv.obj()
about_us.set_size(1280, 720)
about_us.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for about_us, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
about_us.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create about_us_about_us
about_us_about_us = lv.img(about_us)
about_us_about_us.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\42_1284_722.png"))
about_us_about_us.add_flag(lv.obj.FLAG.CLICKABLE)
about_us_about_us.set_pivot(50,50)
about_us_about_us.set_angle(0)
about_us_about_us.set_pos(0, 0)
about_us_about_us.set_size(1284, 722)
about_us_about_us.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for about_us_about_us, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
about_us_about_us.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

about_us.update_layout()
# Create hastaa
hastaa = lv.obj()
hastaa.set_size(1280, 720)
hastaa.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for hastaa, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
hastaa.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create hastaa_img_1
hastaa_img_1 = lv.img(hastaa)
hastaa_img_1.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\session_1280_720.png"))
hastaa_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
hastaa_img_1.set_pivot(50,50)
hastaa_img_1.set_angle(0)
hastaa_img_1.set_pos(0, 0)
hastaa_img_1.set_size(1280, 720)
hastaa_img_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for hastaa_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
hastaa_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create hastaa_animimg_1
hastaa_animimg_1 = lv.animimg(hastaa)
hastaa_animimg_1_imgs = [None]*29
hastaa_animimg_1_imgs[0] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\2_796_511.png")
hastaa_animimg_1_imgs[1] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\3_796_511.png")
hastaa_animimg_1_imgs[2] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\5_796_511.png")
hastaa_animimg_1_imgs[3] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\6_796_511.png")
hastaa_animimg_1_imgs[4] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\7_796_511.png")
hastaa_animimg_1_imgs[5] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\8_796_511.png")
hastaa_animimg_1_imgs[6] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\9_796_511.png")
hastaa_animimg_1_imgs[7] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\10_796_511.png")
hastaa_animimg_1_imgs[8] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\11_796_511.png")
hastaa_animimg_1_imgs[9] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\12_796_511.png")
hastaa_animimg_1_imgs[10] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\13_796_511.png")
hastaa_animimg_1_imgs[11] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\14_796_511.png")
hastaa_animimg_1_imgs[12] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\15_796_511.png")
hastaa_animimg_1_imgs[13] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\16_796_511.png")
hastaa_animimg_1_imgs[14] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\17_796_511.png")
hastaa_animimg_1_imgs[15] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\18_796_511.png")
hastaa_animimg_1_imgs[16] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\19_796_511.png")
hastaa_animimg_1_imgs[17] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\21_796_511.png")
hastaa_animimg_1_imgs[18] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\22_796_511.png")
hastaa_animimg_1_imgs[19] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\23_796_511.png")
hastaa_animimg_1_imgs[20] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\24_796_511.png")
hastaa_animimg_1_imgs[21] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\26_796_511.png")
hastaa_animimg_1_imgs[22] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\27_796_511.png")
hastaa_animimg_1_imgs[23] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\27_796_511.png")
hastaa_animimg_1_imgs[24] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\28_796_511.png")
hastaa_animimg_1_imgs[25] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\30_796_511.png")
hastaa_animimg_1_imgs[26] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\31_796_511.png")
hastaa_animimg_1_imgs[27] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\34_796_511.png")
hastaa_animimg_1_imgs[28] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\36_796_511.png")
hastaa_animimg_1.set_src(hastaa_animimg_1_imgs, 29, False)
hastaa_animimg_1.set_duration(289*29)
hastaa_animimg_1.set_repeat_count(lv.ANIM_REPEAT.INFINITE)
hastaa_animimg_1.start()
hastaa_animimg_1.set_pos(31, 122)
hastaa_animimg_1.set_size(796, 511)
hastaa_animimg_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

# Create hastaa_img_3
hastaa_img_3 = lv.img(hastaa)
hastaa_img_3.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\406_124_97.png"))
hastaa_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
hastaa_img_3.set_pivot(50,50)
hastaa_img_3.set_angle(0)
hastaa_img_3.set_pos(1124, 587)
hastaa_img_3.set_size(124, 97)
hastaa_img_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for hastaa_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
hastaa_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create hastaa_img_4
hastaa_img_4 = lv.img(hastaa)
hastaa_img_4.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\407_122_92.png"))
hastaa_img_4.add_flag(lv.obj.FLAG.CLICKABLE)
hastaa_img_4.set_pivot(50,50)
hastaa_img_4.set_angle(0)
hastaa_img_4.set_pos(906, 587)
hastaa_img_4.set_size(122, 92)
hastaa_img_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for hastaa_img_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
hastaa_img_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

hastaa.update_layout()
# Create padmasan
padmasan = lv.obj()
padmasan.set_size(1280, 720)
padmasan.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for padmasan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
padmasan.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create padmasan_img_2
padmasan_img_2 = lv.img(padmasan)
padmasan_img_2.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\407_122_88.png"))
padmasan_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
padmasan_img_2.set_pivot(50,50)
padmasan_img_2.set_angle(0)
padmasan_img_2.set_pos(905, 590)
padmasan_img_2.set_size(122, 88)
padmasan_img_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for padmasan_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
padmasan_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create padmasan_img_3
padmasan_img_3 = lv.img(padmasan)
padmasan_img_3.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\406_122_86.png"))
padmasan_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
padmasan_img_3.set_pivot(50,50)
padmasan_img_3.set_angle(0)
padmasan_img_3.set_pos(1126, 590)
padmasan_img_3.set_size(122, 86)
padmasan_img_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for padmasan_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
padmasan_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create padmasan_img_4
padmasan_img_4 = lv.img(padmasan)
padmasan_img_4.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\pad_1280_720.png"))
padmasan_img_4.add_flag(lv.obj.FLAG.CLICKABLE)
padmasan_img_4.set_pivot(50,50)
padmasan_img_4.set_angle(0)
padmasan_img_4.set_pos(0, 0)
padmasan_img_4.set_size(1280, 720)
padmasan_img_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for padmasan_img_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
padmasan_img_4.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create padmasan_img_5
padmasan_img_5 = lv.img(padmasan)
padmasan_img_5.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\407_120_93.png"))
padmasan_img_5.add_flag(lv.obj.FLAG.CLICKABLE)
padmasan_img_5.set_pivot(50,50)
padmasan_img_5.set_angle(0)
padmasan_img_5.set_pos(907, 590)
padmasan_img_5.set_size(120, 93)
padmasan_img_5.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for padmasan_img_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
padmasan_img_5.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

padmasan.update_layout()
# Create vrikshasan
vrikshasan = lv.obj()
vrikshasan.set_size(1280, 720)
vrikshasan.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for vrikshasan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
vrikshasan.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create vrikshasan_img_1
vrikshasan_img_1 = lv.img(vrikshasan)
vrikshasan_img_1.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\session_1280_720.png"))
vrikshasan_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
vrikshasan_img_1.set_pivot(50,50)
vrikshasan_img_1.set_angle(0)
vrikshasan_img_1.set_pos(0, 0)
vrikshasan_img_1.set_size(1280, 720)
vrikshasan_img_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for vrikshasan_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
vrikshasan_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create vrikshasan_img_2
vrikshasan_img_2 = lv.img(vrikshasan)
vrikshasan_img_2.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\406_128_100.png"))
vrikshasan_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
vrikshasan_img_2.set_pivot(50,50)
vrikshasan_img_2.set_angle(0)
vrikshasan_img_2.set_pos(1122, 584)
vrikshasan_img_2.set_size(128, 100)
vrikshasan_img_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for vrikshasan_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
vrikshasan_img_2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create vrikshasan_img_3
vrikshasan_img_3 = lv.img(vrikshasan)
vrikshasan_img_3.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\407_121_99.png"))
vrikshasan_img_3.add_flag(lv.obj.FLAG.CLICKABLE)
vrikshasan_img_3.set_pivot(50,50)
vrikshasan_img_3.set_angle(0)
vrikshasan_img_3.set_pos(906, 585)
vrikshasan_img_3.set_size(121, 99)
vrikshasan_img_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for vrikshasan_img_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
vrikshasan_img_3.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create vrikshasan_animimg_1
vrikshasan_animimg_1 = lv.animimg(vrikshasan)
vrikshasan_animimg_1_imgs = [None]*20
vrikshasan_animimg_1_imgs[0] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\700_796_511.png")
vrikshasan_animimg_1_imgs[1] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\701_796_511.png")
vrikshasan_animimg_1_imgs[2] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\702_796_511.png")
vrikshasan_animimg_1_imgs[3] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\703_796_511.png")
vrikshasan_animimg_1_imgs[4] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\704_796_511.png")
vrikshasan_animimg_1_imgs[5] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\705_796_511.png")
vrikshasan_animimg_1_imgs[6] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\706_796_511.png")
vrikshasan_animimg_1_imgs[7] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\707_796_511.png")
vrikshasan_animimg_1_imgs[8] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\708_796_511.png")
vrikshasan_animimg_1_imgs[9] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\709_796_511.png")
vrikshasan_animimg_1_imgs[10] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\710_796_511.png")
vrikshasan_animimg_1_imgs[11] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\711_796_511.png")
vrikshasan_animimg_1_imgs[12] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\712_796_511.png")
vrikshasan_animimg_1_imgs[13] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\713_796_511.png")
vrikshasan_animimg_1_imgs[14] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\714_796_511.png")
vrikshasan_animimg_1_imgs[15] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\715_796_511.png")
vrikshasan_animimg_1_imgs[16] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\716_796_511.png")
vrikshasan_animimg_1_imgs[17] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\717_796_511.png")
vrikshasan_animimg_1_imgs[18] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\718_796_511.png")
vrikshasan_animimg_1_imgs[19] = load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\719_796_511.png")
vrikshasan_animimg_1.set_src(vrikshasan_animimg_1_imgs, 20, False)
vrikshasan_animimg_1.set_duration(289*20)
vrikshasan_animimg_1.set_repeat_count(lv.ANIM_REPEAT.INFINITE)
vrikshasan_animimg_1.start()
vrikshasan_animimg_1.set_pos(25, 118)
vrikshasan_animimg_1.set_size(796, 511)
vrikshasan_animimg_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

vrikshasan.update_layout()
# Create qr
qr = lv.obj()
qr.set_size(1280, 720)
qr.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for qr, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
qr.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create qr_img_1
qr_img_1 = lv.img(qr)
qr_img_1.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\QR_1280_720.png"))
qr_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
qr_img_1.set_pivot(50,50)
qr_img_1.set_angle(0)
qr_img_1.set_pos(0, 0)
qr_img_1.set_size(1280, 720)
qr_img_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for qr_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
qr_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

qr.update_layout()
# Create padma_intro
padma_intro = lv.obj()
padma_intro.set_size(1280, 720)
padma_intro.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for padma_intro, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
padma_intro.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create padma_intro_padma
padma_intro_padma = lv.img(padma_intro)
padma_intro_padma.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\intro1_1280_720.png"))
padma_intro_padma.add_flag(lv.obj.FLAG.CLICKABLE)
padma_intro_padma.set_pivot(50,50)
padma_intro_padma.set_angle(0)
padma_intro_padma.set_pos(0, 0)
padma_intro_padma.set_size(1280, 720)
padma_intro_padma.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for padma_intro_padma, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
padma_intro_padma.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

padma_intro.update_layout()
# Create vriks_intro
vriks_intro = lv.obj()
vriks_intro.set_size(1280, 720)
vriks_intro.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for vriks_intro, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
vriks_intro.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create vriks_intro_img_1
vriks_intro_img_1 = lv.img(vriks_intro)
vriks_intro_img_1.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\intro2_1280_720.png"))
vriks_intro_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
vriks_intro_img_1.set_pivot(50,50)
vriks_intro_img_1.set_angle(0)
vriks_intro_img_1.set_pos(0, 0)
vriks_intro_img_1.set_size(1280, 720)
vriks_intro_img_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for vriks_intro_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
vriks_intro_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

vriks_intro.update_layout()
# Create has_intro
has_intro = lv.obj()
has_intro.set_size(1280, 720)
has_intro.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for has_intro, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
has_intro.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create has_intro_hasta_intro
has_intro_hasta_intro = lv.img(has_intro)
has_intro_hasta_intro.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\intro3_1280_720.png"))
has_intro_hasta_intro.add_flag(lv.obj.FLAG.CLICKABLE)
has_intro_hasta_intro.set_pivot(50,50)
has_intro_hasta_intro.set_angle(0)
has_intro_hasta_intro.set_pos(0, 0)
has_intro_hasta_intro.set_size(1280, 720)
has_intro_hasta_intro.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for has_intro_hasta_intro, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
has_intro_hasta_intro.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

has_intro.update_layout()
# Create progress
progress = lv.obj()
progress.set_size(1280, 720)
progress.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for progress, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
progress.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create progress_img_1
progress_img_1 = lv.img(progress)
progress_img_1.set_src(load_image(r"C:\Users\91800\Desktop\yog\generated\MicroPython\checklist_1280_720.png"))
progress_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
progress_img_1.set_pivot(50,50)
progress_img_1.set_angle(0)
progress_img_1.set_pos(0, 0)
progress_img_1.set_size(1280, 720)
progress_img_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for progress_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
progress_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create progress_cb_1
progress_cb_1 = lv.checkbox(progress)
progress_cb_1.set_text("")
progress_cb_1.set_pos(267, 624)
progress_cb_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for progress_cb_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
progress_cb_1.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_1.set_style_text_font(test_font("montserratMedium", 49), lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_1.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_1.set_style_radius(6, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for progress_cb_1, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
progress_cb_1.set_style_border_width(2, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_1.set_style_border_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_1.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_1.set_style_radius(6, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_1.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Create progress_cb_2
progress_cb_2 = lv.checkbox(progress)
progress_cb_2.set_text("")
progress_cb_2.set_pos(611, 624)
progress_cb_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for progress_cb_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
progress_cb_2.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_2.set_style_text_font(test_font("montserratMedium", 49), lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_2.set_style_radius(6, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_2.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for progress_cb_2, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
progress_cb_2.set_style_border_width(2, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_2.set_style_border_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_2.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_2.set_style_radius(6, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_2.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_2.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Create progress_cb_3
progress_cb_3 = lv.checkbox(progress)
progress_cb_3.set_text("")
progress_cb_3.set_pos(965, 624)
progress_cb_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for progress_cb_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
progress_cb_3.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_3.set_style_text_font(test_font("montserratMedium", 49), lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_3.set_style_radius(6, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_3.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
progress_cb_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for progress_cb_3, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
progress_cb_3.set_style_border_width(2, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_3.set_style_border_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_3.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_3.set_style_radius(6, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_3.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
progress_cb_3.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.INDICATOR|lv.STATE.DEFAULT)

progress.update_layout()

def menuDemo_event_handler(e):
    code = e.get_code()

menuDemo.add_event_cb(lambda e: menuDemo_event_handler(e), lv.EVENT.ALL, None)

def menuDemo_dashboard_menu_event_handler(e):
    code = e.get_code()

menuDemo_dashboard_menu.add_event_cb(lambda e: menuDemo_dashboard_menu_event_handler(e), lv.EVENT.ALL, None)

def menuDemo_radio_slider_event_handler(e):
    code = e.get_code()

menuDemo_radio_slider.add_event_cb(lambda e: menuDemo_radio_slider_event_handler(e), lv.EVENT.ALL, None)

def menuDemo_phone_btnm_event_handler(e):
    code = e.get_code()

menuDemo_phone_btnm.add_event_cb(lambda e: menuDemo_phone_btnm_event_handler(e), lv.EVENT.ALL, None)

def menuDemo_imgbtn_call_event_handler(e):
    code = e.get_code()

menuDemo_imgbtn_call.add_event_cb(lambda e: menuDemo_imgbtn_call_event_handler(e), lv.EVENT.ALL, None)

def menuDemo_mode_event_handler(e):
    code = e.get_code()

menuDemo_mode.add_event_cb(lambda e: menuDemo_mode_event_handler(e), lv.EVENT.ALL, None)

def menuDemo_btn_del_event_handler(e):
    code = e.get_code()

menuDemo_btn_del.add_event_cb(lambda e: menuDemo_btn_del_event_handler(e), lv.EVENT.ALL, None)

def menuDemo_img_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(Yoga_selection, lv.SCR_LOAD_ANIM.MOVE_BOTTOM, 200, 200, False)

menuDemo_img_1.add_event_cb(lambda e: menuDemo_img_1_event_handler(e), lv.EVENT.ALL, None)

def home_screen_img_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(Yoga_selection, lv.SCR_LOAD_ANIM.OVER_RIGHT, 200, 200, False)

home_screen_img_1.add_event_cb(lambda e: home_screen_img_1_event_handler(e), lv.EVENT.ALL, None)

def Yoga_selection_img_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(progress, lv.SCR_LOAD_ANIM.OVER_BOTTOM, 200, 200, False)

Yoga_selection_img_2.add_event_cb(lambda e: Yoga_selection_img_2_event_handler(e), lv.EVENT.ALL, None)

def Yoga_selection_img_5_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(menuDemo, lv.SCR_LOAD_ANIM.OVER_BOTTOM, 200, 200, False)

Yoga_selection_img_5.add_event_cb(lambda e: Yoga_selection_img_5_event_handler(e), lv.EVENT.ALL, None)

def Yoga_selection_img_6_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(menuDemo, lv.SCR_LOAD_ANIM.MOVE_RIGHT, 200, 200, False)

Yoga_selection_img_6.add_event_cb(lambda e: Yoga_selection_img_6_event_handler(e), lv.EVENT.ALL, None)

def Yoga_selection_img_7_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(qr, lv.SCR_LOAD_ANIM.MOVE_TOP, 200, 200, False)

Yoga_selection_img_7.add_event_cb(lambda e: Yoga_selection_img_7_event_handler(e), lv.EVENT.ALL, None)

def Yoga_selection_img_8_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(home_screen, lv.SCR_LOAD_ANIM.OVER_LEFT, 200, 200, False)

Yoga_selection_img_8.add_event_cb(lambda e: Yoga_selection_img_8_event_handler(e), lv.EVENT.ALL, None)

def Yoga_selection_img_9_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(about_us, lv.SCR_LOAD_ANIM.NONE, 200, 200, False)

Yoga_selection_img_9.add_event_cb(lambda e: Yoga_selection_img_9_event_handler(e), lv.EVENT.ALL, None)

def Yoga_selection_img_10_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(vriks_intro, lv.SCR_LOAD_ANIM.MOVE_LEFT, 200, 200, False)

Yoga_selection_img_10.add_event_cb(lambda e: Yoga_selection_img_10_event_handler(e), lv.EVENT.ALL, None)

def Yoga_selection_img_11_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(has_intro, lv.SCR_LOAD_ANIM.MOVE_RIGHT, 200, 200, False)

Yoga_selection_img_11.add_event_cb(lambda e: Yoga_selection_img_11_event_handler(e), lv.EVENT.ALL, None)

def Yoga_selection_img_12_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(padma_intro, lv.SCR_LOAD_ANIM.NONE, 200, 200, False)

Yoga_selection_img_12.add_event_cb(lambda e: Yoga_selection_img_12_event_handler(e), lv.EVENT.ALL, None)

def about_us_about_us_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(Yoga_selection, lv.SCR_LOAD_ANIM.NONE, 200, 200, False)

about_us_about_us.add_event_cb(lambda e: about_us_about_us_event_handler(e), lv.EVENT.ALL, None)

def hastaa_img_3_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(progress, lv.SCR_LOAD_ANIM.MOVE_LEFT, 200, 200, False)

hastaa_img_3.add_event_cb(lambda e: hastaa_img_3_event_handler(e), lv.EVENT.ALL, None)

def hastaa_img_4_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(Yoga_selection, lv.SCR_LOAD_ANIM.OVER_RIGHT, 200, 200, False)

hastaa_img_4.add_event_cb(lambda e: hastaa_img_4_event_handler(e), lv.EVENT.ALL, None)

def padmasan_img_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(Yoga_selection, lv.SCR_LOAD_ANIM.OVER_TOP, 200, 200, False)

padmasan_img_2.add_event_cb(lambda e: padmasan_img_2_event_handler(e), lv.EVENT.ALL, None)

def padmasan_img_4_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(progress, lv.SCR_LOAD_ANIM.MOVE_RIGHT, 200, 200, False)

padmasan_img_4.add_event_cb(lambda e: padmasan_img_4_event_handler(e), lv.EVENT.ALL, None)

def padmasan_img_5_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(Yoga_selection, lv.SCR_LOAD_ANIM.MOVE_RIGHT, 200, 200, False)

padmasan_img_5.add_event_cb(lambda e: padmasan_img_5_event_handler(e), lv.EVENT.ALL, None)

def vrikshasan_img_2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(progress, lv.SCR_LOAD_ANIM.OVER_RIGHT, 200, 200, False)

vrikshasan_img_2.add_event_cb(lambda e: vrikshasan_img_2_event_handler(e), lv.EVENT.ALL, None)

def vrikshasan_img_3_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(Yoga_selection, lv.SCR_LOAD_ANIM.MOVE_TOP, 200, 200, False)

vrikshasan_img_3.add_event_cb(lambda e: vrikshasan_img_3_event_handler(e), lv.EVENT.ALL, None)

def qr_img_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(Yoga_selection, lv.SCR_LOAD_ANIM.NONE, 200, 200, False)

qr_img_1.add_event_cb(lambda e: qr_img_1_event_handler(e), lv.EVENT.ALL, None)

def padma_intro_padma_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(padmasan, lv.SCR_LOAD_ANIM.MOVE_RIGHT, 200, 200, False)

padma_intro_padma.add_event_cb(lambda e: padma_intro_padma_event_handler(e), lv.EVENT.ALL, None)

def vriks_intro_img_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(vrikshasan, lv.SCR_LOAD_ANIM.MOVE_TOP, 200, 200, False)

vriks_intro_img_1.add_event_cb(lambda e: vriks_intro_img_1_event_handler(e), lv.EVENT.ALL, None)

def has_intro_hasta_intro_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(hastaa, lv.SCR_LOAD_ANIM.MOVE_LEFT, 200, 200, False)

has_intro_hasta_intro.add_event_cb(lambda e: has_intro_hasta_intro_event_handler(e), lv.EVENT.ALL, None)

def progress_img_1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(Yoga_selection, lv.SCR_LOAD_ANIM.MOVE_BOTTOM, 200, 200, False)

progress_img_1.add_event_cb(lambda e: progress_img_1_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(home_screen)

while SDL.check():
    time.sleep_ms(5)

