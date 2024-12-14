/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_7(lv_ui *ui)
{
    //Write codes screen_7
    ui->screen_7 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_7, 1280, 720);
    lv_obj_set_scrollbar_mode(ui->screen_7, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_7_img_1
    ui->screen_7_img_1 = lv_img_create(ui->screen_7);
    lv_obj_add_flag(ui->screen_7_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_pivot(ui->screen_7_img_1, 50,50);
    lv_img_set_angle(ui->screen_7_img_1, 0);
    lv_obj_set_pos(ui->screen_7_img_1, 590, 310);
    lv_obj_set_size(ui->screen_7_img_1, 100, 100);

    //Write style for screen_7_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_7_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_7_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_7_img_2
    ui->screen_7_img_2 = lv_img_create(ui->screen_7);
    lv_obj_add_flag(ui->screen_7_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_7_img_2, &_13_alpha_1286x721);
    lv_img_set_pivot(ui->screen_7_img_2, 50,50);
    lv_img_set_angle(ui->screen_7_img_2, 0);
    lv_obj_set_pos(ui->screen_7_img_2, 0, 0);
    lv_obj_set_size(ui->screen_7_img_2, 1286, 721);

    //Write style for screen_7_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_7_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_7_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_7_imgbtn_1
    ui->screen_7_imgbtn_1 = lv_imgbtn_create(ui->screen_7);
    lv_obj_add_flag(ui->screen_7_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->screen_7_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_baba1_alpha_609x526, NULL);
    lv_imgbtn_set_src(ui->screen_7_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_baba_alpha_609x526, NULL);
    ui->screen_7_imgbtn_1_label = lv_label_create(ui->screen_7_imgbtn_1);
    lv_label_set_text(ui->screen_7_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->screen_7_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_7_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_7_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->screen_7_imgbtn_1, 346, 47);
    lv_obj_set_size(ui->screen_7_imgbtn_1, 609, 526);

    //Write style for screen_7_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_7_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_7_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_7_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_7_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_7_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_7_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_7_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->screen_7_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen_7_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen_7_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen_7_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen_7_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen_7_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->screen_7_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen_7_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen_7_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen_7_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen_7_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for screen_7_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->screen_7_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes screen_7_img_6
    ui->screen_7_img_6 = lv_img_create(ui->screen_7);
    lv_obj_add_flag(ui->screen_7_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_7_img_6, &_2345_alpha_102x77);
    lv_img_set_pivot(ui->screen_7_img_6, 50,50);
    lv_img_set_angle(ui->screen_7_img_6, 0);
    lv_obj_set_pos(ui->screen_7_img_6, -6, 642);
    lv_obj_set_size(ui->screen_7_img_6, 102, 77);

    //Write style for screen_7_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_7_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_7_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_7_img_7
    ui->screen_7_img_7 = lv_img_create(ui->screen_7);
    lv_obj_add_flag(ui->screen_7_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_7_img_7, &_1112_alpha_111x76);
    lv_img_set_pivot(ui->screen_7_img_7, 50,50);
    lv_img_set_angle(ui->screen_7_img_7, 0);
    lv_obj_set_pos(ui->screen_7_img_7, -6, 446);
    lv_obj_set_size(ui->screen_7_img_7, 111, 76);

    //Write style for screen_7_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_7_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_7_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_7_img_8
    ui->screen_7_img_8 = lv_img_create(ui->screen_7);
    lv_obj_add_flag(ui->screen_7_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_7_img_8, &_12_alpha_125x82);
    lv_img_set_pivot(ui->screen_7_img_8, 50,50);
    lv_img_set_angle(ui->screen_7_img_8, 0);
    lv_obj_set_pos(ui->screen_7_img_8, -25, 3);
    lv_obj_set_size(ui->screen_7_img_8, 125, 82);

    //Write style for screen_7_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_7_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_7_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_7_img_9
    ui->screen_7_img_9 = lv_img_create(ui->screen_7);
    lv_obj_add_flag(ui->screen_7_img_9, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_7_img_9, &_567890_alpha_101x80);
    lv_img_set_pivot(ui->screen_7_img_9, 50,50);
    lv_img_set_angle(ui->screen_7_img_9, 0);
    lv_obj_set_pos(ui->screen_7_img_9, 0, 358);
    lv_obj_set_size(ui->screen_7_img_9, 101, 80);

    //Write style for screen_7_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_7_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_7_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_7_img_10
    ui->screen_7_img_10 = lv_img_create(ui->screen_7);
    lv_obj_add_flag(ui->screen_7_img_10, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_7_img_10, &_09876543_alpha_95x81);
    lv_img_set_pivot(ui->screen_7_img_10, 50,50);
    lv_img_set_angle(ui->screen_7_img_10, 0);
    lv_obj_set_pos(ui->screen_7_img_10, 0, 263);
    lv_obj_set_size(ui->screen_7_img_10, 95, 81);

    //Write style for screen_7_img_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_7_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_7_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_7_img_11
    ui->screen_7_img_11 = lv_img_create(ui->screen_7);
    lv_obj_add_flag(ui->screen_7_img_11, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_7_img_11, &_532234_alpha_94x89);
    lv_img_set_pivot(ui->screen_7_img_11, 50,50);
    lv_img_set_angle(ui->screen_7_img_11, 0);
    lv_obj_set_pos(ui->screen_7_img_11, 0, 169);
    lv_obj_set_size(ui->screen_7_img_11, 94, 89);

    //Write style for screen_7_img_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_7_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_7_img_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_7_img_12
    ui->screen_7_img_12 = lv_img_create(ui->screen_7);
    lv_obj_add_flag(ui->screen_7_img_12, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_7_img_12, &_21212_alpha_89x70);
    lv_img_set_pivot(ui->screen_7_img_12, 50,50);
    lv_img_set_angle(ui->screen_7_img_12, 0);
    lv_obj_set_pos(ui->screen_7_img_12, 4, 91);
    lv_obj_set_size(ui->screen_7_img_12, 89, 70);

    //Write style for screen_7_img_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_7_img_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_7_img_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_7.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_7);

    //Init events for screen.
    events_init_screen_7(ui);
}
