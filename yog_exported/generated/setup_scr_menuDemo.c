/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
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


void setup_scr_menuDemo(lv_ui *ui)
{
	//Write codes menuDemo
	ui->menuDemo = lv_obj_create(NULL);
	lv_obj_set_size(ui->menuDemo, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->menuDemo, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->menuDemo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menuDemo_dashboard_menu
	ui->menuDemo_dashboard_menu = lv_menu_create(ui->menuDemo);

	//Create sidebar page for menu menuDemo_dashboard_menu
	ui->menuDemo_dashboard_menu_sidebar_page = lv_menu_page_create(ui->menuDemo_dashboard_menu, "Settings");
	lv_menu_set_sidebar_page(ui->menuDemo_dashboard_menu, ui->menuDemo_dashboard_menu_sidebar_page);

	//Create subpage for menuDemo_dashboard_menu
	ui->menuDemo_dashboard_menu_subpage_1 = lv_menu_page_create(ui->menuDemo_dashboard_menu, NULL);
	ui->menuDemo_dashboard_menu_cont_1 = lv_menu_cont_create(ui->menuDemo_dashboard_menu_sidebar_page);
	ui->menuDemo_dashboard_menu_label_1 = lv_label_create(ui->menuDemo_dashboard_menu_cont_1);
	lv_label_set_text(ui->menuDemo_dashboard_menu_label_1, "Battery");
	lv_obj_set_size(ui->menuDemo_dashboard_menu_label_1, LV_PCT(100), LV_SIZE_CONTENT);
	lv_menu_set_load_page_event(ui->menuDemo_dashboard_menu, ui->menuDemo_dashboard_menu_cont_1, ui->menuDemo_dashboard_menu_subpage_1);

	//Create subpage for menuDemo_dashboard_menu
	ui->menuDemo_dashboard_menu_subpage_2 = lv_menu_page_create(ui->menuDemo_dashboard_menu, NULL);
	ui->menuDemo_dashboard_menu_cont_2 = lv_menu_cont_create(ui->menuDemo_dashboard_menu_sidebar_page);
	ui->menuDemo_dashboard_menu_label_2 = lv_label_create(ui->menuDemo_dashboard_menu_cont_2);
	lv_label_set_text(ui->menuDemo_dashboard_menu_label_2, "Yoga suggestion");
	lv_obj_set_size(ui->menuDemo_dashboard_menu_label_2, LV_PCT(100), LV_SIZE_CONTENT);
	lv_menu_set_load_page_event(ui->menuDemo_dashboard_menu, ui->menuDemo_dashboard_menu_cont_2, ui->menuDemo_dashboard_menu_subpage_2);

	//Create subpage for menuDemo_dashboard_menu
	ui->menuDemo_dashboard_menu_subpage_3 = lv_menu_page_create(ui->menuDemo_dashboard_menu, NULL);
	ui->menuDemo_dashboard_menu_cont_3 = lv_menu_cont_create(ui->menuDemo_dashboard_menu_sidebar_page);
	ui->menuDemo_dashboard_menu_label_3 = lv_label_create(ui->menuDemo_dashboard_menu_cont_3);
	lv_label_set_text(ui->menuDemo_dashboard_menu_label_3, "Call Support");
	lv_obj_set_size(ui->menuDemo_dashboard_menu_label_3, LV_PCT(100), LV_SIZE_CONTENT);
	lv_menu_set_load_page_event(ui->menuDemo_dashboard_menu, ui->menuDemo_dashboard_menu_cont_3, ui->menuDemo_dashboard_menu_subpage_3);

	//Create subpage for menuDemo_dashboard_menu
	ui->menuDemo_dashboard_menu_subpage_4 = lv_menu_page_create(ui->menuDemo_dashboard_menu, NULL);
	ui->menuDemo_dashboard_menu_cont_4 = lv_menu_cont_create(ui->menuDemo_dashboard_menu_sidebar_page);
	ui->menuDemo_dashboard_menu_label_4 = lv_label_create(ui->menuDemo_dashboard_menu_cont_4);
	lv_label_set_text(ui->menuDemo_dashboard_menu_label_4, "");
	lv_obj_set_size(ui->menuDemo_dashboard_menu_label_4, LV_PCT(100), LV_SIZE_CONTENT);
	lv_menu_set_load_page_event(ui->menuDemo_dashboard_menu, ui->menuDemo_dashboard_menu_cont_4, ui->menuDemo_dashboard_menu_subpage_4);
	lv_obj_set_pos(ui->menuDemo_dashboard_menu, 0, 0);
	lv_obj_set_size(ui->menuDemo_dashboard_menu, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->menuDemo_dashboard_menu, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_dashboard_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->menuDemo_dashboard_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->menuDemo_dashboard_menu, lv_color_hex(0x082142), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->menuDemo_dashboard_menu, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->menuDemo_dashboard_menu, lv_color_hex(0x2b1979), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_dashboard_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_dashboard_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_menuDemo_dashboard_menu_extra_sidebar_page_main_default
	static lv_style_t style_menuDemo_dashboard_menu_extra_sidebar_page_main_default;
	ui_init_style(&style_menuDemo_dashboard_menu_extra_sidebar_page_main_default);
	
	lv_style_set_bg_opa(&style_menuDemo_dashboard_menu_extra_sidebar_page_main_default, 0);
	lv_style_set_radius(&style_menuDemo_dashboard_menu_extra_sidebar_page_main_default, 0);
	lv_obj_add_style(ui->menuDemo_dashboard_menu_sidebar_page, &style_menuDemo_dashboard_menu_extra_sidebar_page_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_menuDemo_dashboard_menu_extra_option_btns_main_default
	static lv_style_t style_menuDemo_dashboard_menu_extra_option_btns_main_default;
	ui_init_style(&style_menuDemo_dashboard_menu_extra_option_btns_main_default);
	
	lv_style_set_text_color(&style_menuDemo_dashboard_menu_extra_option_btns_main_default, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_menuDemo_dashboard_menu_extra_option_btns_main_default, &lv_font_montserratMedium_42);
	lv_style_set_text_align(&style_menuDemo_dashboard_menu_extra_option_btns_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_top(&style_menuDemo_dashboard_menu_extra_option_btns_main_default, 10);
	lv_style_set_pad_bottom(&style_menuDemo_dashboard_menu_extra_option_btns_main_default, 10);
	lv_obj_add_style(ui->menuDemo_dashboard_menu_cont_4, &style_menuDemo_dashboard_menu_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->menuDemo_dashboard_menu_cont_3, &style_menuDemo_dashboard_menu_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->menuDemo_dashboard_menu_cont_2, &style_menuDemo_dashboard_menu_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->menuDemo_dashboard_menu_cont_1, &style_menuDemo_dashboard_menu_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for &style_menuDemo_dashboard_menu_extra_option_btns_main_checked
	static lv_style_t style_menuDemo_dashboard_menu_extra_option_btns_main_checked;
	ui_init_style(&style_menuDemo_dashboard_menu_extra_option_btns_main_checked);
	
	lv_style_set_text_color(&style_menuDemo_dashboard_menu_extra_option_btns_main_checked, lv_color_hex(0xa5efff));
	lv_style_set_text_font(&style_menuDemo_dashboard_menu_extra_option_btns_main_checked, &lv_font_montserratMedium_42);
	lv_style_set_text_align(&style_menuDemo_dashboard_menu_extra_option_btns_main_checked, LV_TEXT_ALIGN_CENTER);
	lv_style_set_border_width(&style_menuDemo_dashboard_menu_extra_option_btns_main_checked, 0);
	lv_style_set_radius(&style_menuDemo_dashboard_menu_extra_option_btns_main_checked, 0);
	lv_style_set_bg_opa(&style_menuDemo_dashboard_menu_extra_option_btns_main_checked, 255);
	lv_style_set_bg_color(&style_menuDemo_dashboard_menu_extra_option_btns_main_checked, lv_color_hex(0x253853));
	lv_style_set_bg_grad_dir(&style_menuDemo_dashboard_menu_extra_option_btns_main_checked, LV_GRAD_DIR_HOR);
	lv_style_set_bg_grad_color(&style_menuDemo_dashboard_menu_extra_option_btns_main_checked, lv_color_hex(0x162d4d));
	lv_obj_add_style(ui->menuDemo_dashboard_menu_cont_4, &style_menuDemo_dashboard_menu_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_add_style(ui->menuDemo_dashboard_menu_cont_3, &style_menuDemo_dashboard_menu_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_add_style(ui->menuDemo_dashboard_menu_cont_2, &style_menuDemo_dashboard_menu_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_add_style(ui->menuDemo_dashboard_menu_cont_1, &style_menuDemo_dashboard_menu_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for &style_menuDemo_dashboard_menu_extra_main_title_main_default
	static lv_style_t style_menuDemo_dashboard_menu_extra_main_title_main_default;
	ui_init_style(&style_menuDemo_dashboard_menu_extra_main_title_main_default);
	
	lv_style_set_text_color(&style_menuDemo_dashboard_menu_extra_main_title_main_default, lv_color_hex(0x6a94b6));
	lv_style_set_text_font(&style_menuDemo_dashboard_menu_extra_main_title_main_default, &lv_font_Alatsi_Regular_47);
	lv_style_set_text_align(&style_menuDemo_dashboard_menu_extra_main_title_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_bg_opa(&style_menuDemo_dashboard_menu_extra_main_title_main_default, 0);
	lv_style_set_pad_top(&style_menuDemo_dashboard_menu_extra_main_title_main_default, 10);
	lv_style_set_pad_bottom(&style_menuDemo_dashboard_menu_extra_main_title_main_default, 10);
	lv_menu_t * menuDemo_dashboard_menu_menu= (lv_menu_t *)ui->menuDemo_dashboard_menu;
	lv_obj_t * menuDemo_dashboard_menu_title = menuDemo_dashboard_menu_menu->sidebar_header_title;
	lv_obj_set_size(menuDemo_dashboard_menu_title, LV_PCT(100), LV_SIZE_CONTENT);
	lv_obj_add_style(lv_menu_get_sidebar_header(ui->menuDemo_dashboard_menu), &style_menuDemo_dashboard_menu_extra_main_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes menuDemo_battery_label
	ui->menuDemo_battery_label = lv_label_create(ui->menuDemo_dashboard_menu_subpage_1);
	lv_label_set_text(ui->menuDemo_battery_label, "The Battery Condition");
	lv_label_set_long_mode(ui->menuDemo_battery_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->menuDemo_battery_label, 240, 161);
	lv_obj_set_size(ui->menuDemo_battery_label, 744, 248);
	lv_obj_set_scrollbar_mode(ui->menuDemo_battery_label, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_battery_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->menuDemo_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->menuDemo_battery_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->menuDemo_battery_label, &lv_font_montserratMedium_52, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->menuDemo_battery_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->menuDemo_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->menuDemo_battery_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->menuDemo_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->menuDemo_battery_label, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->menuDemo_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->menuDemo_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->menuDemo_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menuDemo_battery_img
	ui->menuDemo_battery_img = lv_img_create(ui->menuDemo_dashboard_menu_subpage_1);
	lv_obj_add_flag(ui->menuDemo_battery_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->menuDemo_battery_img, &_battery_alpha_530x195);
	lv_img_set_pivot(ui->menuDemo_battery_img, 50,50);
	lv_img_set_angle(ui->menuDemo_battery_img, 0);
	lv_obj_set_pos(ui->menuDemo_battery_img, 293, 243);
	lv_obj_set_size(ui->menuDemo_battery_img, 530, 195);
	lv_obj_set_scrollbar_mode(ui->menuDemo_battery_img, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_battery_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->menuDemo_battery_img, 143, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->menuDemo_battery_img, lv_color_hex(0x38fe49), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->menuDemo_battery_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menuDemo_battery_spangroup
	ui->menuDemo_battery_spangroup = lv_spangroup_create(ui->menuDemo_dashboard_menu_subpage_1);
	lv_spangroup_set_align(ui->menuDemo_battery_spangroup, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->menuDemo_battery_spangroup, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->menuDemo_battery_spangroup, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *menuDemo_battery_spangroup_span;
	menuDemo_battery_spangroup_span = lv_spangroup_new_span(ui->menuDemo_battery_spangroup);
	lv_span_set_text(menuDemo_battery_spangroup_span, "Distance :    ");
	lv_style_set_text_color(&menuDemo_battery_spangroup_span->style, lv_color_hex(0xd3e8ff));
	lv_style_set_text_decor(&menuDemo_battery_spangroup_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&menuDemo_battery_spangroup_span->style, &lv_font_Alatsi_Regular_20);
	menuDemo_battery_spangroup_span = lv_spangroup_new_span(ui->menuDemo_battery_spangroup);
	lv_span_set_text(menuDemo_battery_spangroup_span, "267 ");
	lv_style_set_text_color(&menuDemo_battery_spangroup_span->style, lv_color_hex(0x5dfd44));
	lv_style_set_text_decor(&menuDemo_battery_spangroup_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&menuDemo_battery_spangroup_span->style, &lv_font_Alatsi_Regular_45);
	menuDemo_battery_spangroup_span = lv_spangroup_new_span(ui->menuDemo_battery_spangroup);
	lv_span_set_text(menuDemo_battery_spangroup_span, " Km");
	lv_style_set_text_color(&menuDemo_battery_spangroup_span->style, lv_color_hex(0xd3e8ff));
	lv_style_set_text_decor(&menuDemo_battery_spangroup_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&menuDemo_battery_spangroup_span->style, &lv_font_Alatsi_Regular_20);
	lv_obj_set_pos(ui->menuDemo_battery_spangroup, 410, 640);
	lv_obj_set_size(ui->menuDemo_battery_spangroup, 640, 238);
	lv_obj_set_scrollbar_mode(ui->menuDemo_battery_spangroup, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for &style_menuDemo_battery_spangroup_main_main_default
	static lv_style_t style_menuDemo_battery_spangroup_main_main_default;
	ui_init_style(&style_menuDemo_battery_spangroup_main_main_default);
	
	lv_style_set_border_width(&style_menuDemo_battery_spangroup_main_main_default, 0);
	lv_style_set_radius(&style_menuDemo_battery_spangroup_main_main_default, 0);
	lv_style_set_bg_opa(&style_menuDemo_battery_spangroup_main_main_default, 0);
	lv_style_set_pad_top(&style_menuDemo_battery_spangroup_main_main_default, 25);
	lv_style_set_pad_right(&style_menuDemo_battery_spangroup_main_main_default, 0);
	lv_style_set_pad_bottom(&style_menuDemo_battery_spangroup_main_main_default, 0);
	lv_style_set_pad_left(&style_menuDemo_battery_spangroup_main_main_default, 0);
	lv_style_set_shadow_width(&style_menuDemo_battery_spangroup_main_main_default, 0);
	lv_obj_add_style(ui->menuDemo_battery_spangroup, &style_menuDemo_battery_spangroup_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->menuDemo_battery_spangroup);



	//Write codes menuDemo_radio_spangroup
	ui->menuDemo_radio_spangroup = lv_spangroup_create(ui->menuDemo_dashboard_menu_subpage_2);
	lv_spangroup_set_align(ui->menuDemo_radio_spangroup, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->menuDemo_radio_spangroup, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->menuDemo_radio_spangroup, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *menuDemo_radio_spangroup_span;
	menuDemo_radio_spangroup_span = lv_spangroup_new_span(ui->menuDemo_radio_spangroup);
	lv_span_set_text(menuDemo_radio_spangroup_span, "104.0");
	lv_style_set_text_color(&menuDemo_radio_spangroup_span->style, lv_color_hex(0xffffff));
	lv_style_set_text_decor(&menuDemo_radio_spangroup_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&menuDemo_radio_spangroup_span->style, &lv_font_Alatsi_Regular_40);
	lv_obj_set_pos(ui->menuDemo_radio_spangroup, 543, -4);
	lv_obj_set_size(ui->menuDemo_radio_spangroup, 184, 266);
	lv_obj_set_scrollbar_mode(ui->menuDemo_radio_spangroup, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for &style_menuDemo_radio_spangroup_main_main_default
	static lv_style_t style_menuDemo_radio_spangroup_main_main_default;
	ui_init_style(&style_menuDemo_radio_spangroup_main_main_default);
	
	lv_style_set_border_width(&style_menuDemo_radio_spangroup_main_main_default, 0);
	lv_style_set_radius(&style_menuDemo_radio_spangroup_main_main_default, 0);
	lv_style_set_bg_opa(&style_menuDemo_radio_spangroup_main_main_default, 0);
	lv_style_set_pad_top(&style_menuDemo_radio_spangroup_main_main_default, 37);
	lv_style_set_pad_right(&style_menuDemo_radio_spangroup_main_main_default, 0);
	lv_style_set_pad_bottom(&style_menuDemo_radio_spangroup_main_main_default, 0);
	lv_style_set_pad_left(&style_menuDemo_radio_spangroup_main_main_default, 0);
	lv_style_set_shadow_width(&style_menuDemo_radio_spangroup_main_main_default, 0);
	lv_obj_add_style(ui->menuDemo_radio_spangroup, &style_menuDemo_radio_spangroup_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->menuDemo_radio_spangroup);

	//Write codes menuDemo_radio_label
	ui->menuDemo_radio_label = lv_label_create(ui->menuDemo_dashboard_menu_subpage_2);
	lv_label_set_text(ui->menuDemo_radio_label, "Yoga Poses");
	lv_label_set_long_mode(ui->menuDemo_radio_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->menuDemo_radio_label, 324, 264);
	lv_obj_set_size(ui->menuDemo_radio_label, 245, 108);
	lv_obj_set_scrollbar_mode(ui->menuDemo_radio_label, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_radio_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->menuDemo_radio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_radio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->menuDemo_radio_label, lv_color_hex(0xb8b8b8), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->menuDemo_radio_label, &lv_font_Alatsi_Regular_37, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->menuDemo_radio_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->menuDemo_radio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->menuDemo_radio_label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->menuDemo_radio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->menuDemo_radio_label, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->menuDemo_radio_label, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->menuDemo_radio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->menuDemo_radio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_radio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menuDemo_radio_slider
	ui->menuDemo_radio_slider = lv_slider_create(ui->menuDemo_dashboard_menu_subpage_2);
	lv_slider_set_range(ui->menuDemo_radio_slider, 0,90);
	lv_slider_set_value(ui->menuDemo_radio_slider, 40, false);
	lv_obj_set_pos(ui->menuDemo_radio_slider, 48, 381);
	lv_obj_set_size(ui->menuDemo_radio_slider, 800, 214);
	lv_obj_set_scrollbar_mode(ui->menuDemo_radio_slider, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_radio_slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->menuDemo_radio_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_radio_slider, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->menuDemo_radio_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->menuDemo_radio_slider, &_radio_bg_800x214, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->menuDemo_radio_slider, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_radio_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for menuDemo_radio_slider, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->menuDemo_radio_slider, 0, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_radio_slider, 133, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for menuDemo_radio_slider, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->menuDemo_radio_slider, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->menuDemo_radio_slider, &_radio_play_214x214, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->menuDemo_radio_slider, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_radio_slider, 133, LV_PART_KNOB|LV_STATE_DEFAULT);



	//Write codes menuDemo_phone_label
	ui->menuDemo_phone_label = lv_label_create(ui->menuDemo_dashboard_menu_subpage_3);
	lv_label_set_text(ui->menuDemo_phone_label, "");
	lv_label_set_long_mode(ui->menuDemo_phone_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->menuDemo_phone_label, 150, 0);
	lv_obj_set_size(ui->menuDemo_phone_label, 597, 135);
	lv_obj_set_scrollbar_mode(ui->menuDemo_phone_label, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_phone_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->menuDemo_phone_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_phone_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->menuDemo_phone_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->menuDemo_phone_label, &lv_font_Alatsi_Regular_52, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->menuDemo_phone_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->menuDemo_phone_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->menuDemo_phone_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->menuDemo_phone_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->menuDemo_phone_label, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->menuDemo_phone_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->menuDemo_phone_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->menuDemo_phone_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_phone_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menuDemo_phone_btnm
	ui->menuDemo_phone_btnm = lv_btnmatrix_create(ui->menuDemo_dashboard_menu_subpage_3);
	static const char *menuDemo_phone_btnm_text_map[] = {"1", "2", "3", "\n", "4", "5", "6", "\n", "7", "8", "9", "\n", "#", "+", "%", "",};
	lv_btnmatrix_set_map(ui->menuDemo_phone_btnm, menuDemo_phone_btnm_text_map);
	lv_obj_set_pos(ui->menuDemo_phone_btnm, 230, 135);
	lv_obj_set_size(ui->menuDemo_phone_btnm, 437, 468);
	lv_obj_set_scrollbar_mode(ui->menuDemo_phone_btnm, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_phone_btnm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->menuDemo_phone_btnm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->menuDemo_phone_btnm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->menuDemo_phone_btnm, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->menuDemo_phone_btnm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->menuDemo_phone_btnm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui->menuDemo_phone_btnm, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui->menuDemo_phone_btnm, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_phone_btnm, 88, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->menuDemo_phone_btnm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for menuDemo_phone_btnm, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->menuDemo_phone_btnm, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->menuDemo_phone_btnm, lv_color_hex(0x9a9a9a), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->menuDemo_phone_btnm, &lv_font_montserratMedium_37, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_phone_btnm, 90, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->menuDemo_phone_btnm, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->menuDemo_phone_btnm, lv_color_hex(0x0e2537), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->menuDemo_phone_btnm, LV_GRAD_DIR_VER, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->menuDemo_phone_btnm, lv_color_hex(0x52687b), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_phone_btnm, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write style for menuDemo_phone_btnm, Part: LV_PART_ITEMS, State: LV_STATE_PRESSED.
	lv_obj_set_style_border_width(ui->menuDemo_phone_btnm, 0, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->menuDemo_phone_btnm, lv_color_hex(0x6e6505), LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->menuDemo_phone_btnm, &lv_font_Alatsi_Regular_63, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_radius(ui->menuDemo_phone_btnm, 109, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(ui->menuDemo_phone_btnm, 255, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->menuDemo_phone_btnm, lv_color_hex(0x536c80), LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_bg_grad_dir(ui->menuDemo_phone_btnm, LV_GRAD_DIR_VER, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_bg_grad_color(ui->menuDemo_phone_btnm, lv_color_hex(0xd0d0d0), LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->menuDemo_phone_btnm, 0, LV_PART_ITEMS|LV_STATE_PRESSED);

	//Write codes menuDemo_imgbtn_call
	ui->menuDemo_imgbtn_call = lv_imgbtn_create(ui->menuDemo_dashboard_menu_subpage_3);
	lv_obj_add_flag(ui->menuDemo_imgbtn_call, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->menuDemo_imgbtn_call, LV_IMGBTN_STATE_RELEASED, NULL, &_phone_card_alpha_98x95, NULL);
	lv_imgbtn_set_src(ui->menuDemo_imgbtn_call, LV_IMGBTN_STATE_PRESSED, NULL, &_phone_card_alpha_98x95, NULL);
	lv_imgbtn_set_src(ui->menuDemo_imgbtn_call, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_end_call_alpha_98x95, NULL);
	lv_imgbtn_set_src(ui->menuDemo_imgbtn_call, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_end_call_alpha_98x95, NULL);
	lv_obj_add_flag(ui->menuDemo_imgbtn_call, LV_OBJ_FLAG_CHECKABLE);
	ui->menuDemo_imgbtn_call_label = lv_label_create(ui->menuDemo_imgbtn_call);
	lv_label_set_text(ui->menuDemo_imgbtn_call_label, "");
	lv_label_set_long_mode(ui->menuDemo_imgbtn_call_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->menuDemo_imgbtn_call_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->menuDemo_imgbtn_call, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->menuDemo_imgbtn_call, 397, 603);
	lv_obj_set_size(ui->menuDemo_imgbtn_call, 98, 95);
	lv_obj_set_scrollbar_mode(ui->menuDemo_imgbtn_call, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_imgbtn_call, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->menuDemo_imgbtn_call, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->menuDemo_imgbtn_call, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->menuDemo_imgbtn_call, &lv_font_montserratMedium_31, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->menuDemo_imgbtn_call, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_imgbtn_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for menuDemo_imgbtn_call, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->menuDemo_imgbtn_call, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->menuDemo_imgbtn_call, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->menuDemo_imgbtn_call, &lv_font_montserratMedium_31, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->menuDemo_imgbtn_call, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for menuDemo_imgbtn_call, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->menuDemo_imgbtn_call, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->menuDemo_imgbtn_call, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->menuDemo_imgbtn_call, &lv_font_montserratMedium_31, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->menuDemo_imgbtn_call, 0, LV_PART_MAIN|LV_STATE_CHECKED);



	//Write codes menuDemo_conditioner_label
	ui->menuDemo_conditioner_label = lv_label_create(ui->menuDemo_dashboard_menu_subpage_4);
	lv_label_set_text(ui->menuDemo_conditioner_label, "Conditioner Mode");
	lv_label_set_long_mode(ui->menuDemo_conditioner_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->menuDemo_conditioner_label, 8, -2);
	lv_obj_set_size(ui->menuDemo_conditioner_label, 880, 248);
	lv_obj_set_scrollbar_mode(ui->menuDemo_conditioner_label, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_conditioner_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->menuDemo_conditioner_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_conditioner_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->menuDemo_conditioner_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->menuDemo_conditioner_label, &lv_font_montserratMedium_74, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->menuDemo_conditioner_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->menuDemo_conditioner_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->menuDemo_conditioner_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->menuDemo_conditioner_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->menuDemo_conditioner_label, 36, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->menuDemo_conditioner_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->menuDemo_conditioner_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->menuDemo_conditioner_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_conditioner_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menuDemo_label_1
	ui->menuDemo_label_1 = lv_label_create(ui->menuDemo_dashboard_menu_subpage_4);
	lv_label_set_text(ui->menuDemo_label_1, "");
	lv_label_set_long_mode(ui->menuDemo_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->menuDemo_label_1, 480, -283);
	lv_obj_set_size(ui->menuDemo_label_1, 706, 161);
	lv_obj_set_scrollbar_mode(ui->menuDemo_label_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->menuDemo_label_1, LV_OBJ_FLAG_HIDDEN);

	//Write style for menuDemo_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->menuDemo_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->menuDemo_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->menuDemo_label_1, &lv_font_montserratMedium_92, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->menuDemo_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->menuDemo_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->menuDemo_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->menuDemo_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->menuDemo_label_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->menuDemo_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->menuDemo_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->menuDemo_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menuDemo_mode
	ui->menuDemo_mode = lv_carousel_create(ui->menuDemo_dashboard_menu_subpage_4);
	lv_carousel_set_element_width(ui->menuDemo_mode, 120);
	lv_obj_set_size(ui->menuDemo_mode, 621, 317);
	ui->menuDemo_mode_mode_1 = lv_carousel_add_element(ui->menuDemo_mode, 0);
	ui->menuDemo_mode_mode_2 = lv_carousel_add_element(ui->menuDemo_mode, 1);
	ui->menuDemo_mode_mode_3 = lv_carousel_add_element(ui->menuDemo_mode, 2);
	lv_obj_set_pos(ui->menuDemo_mode, 0, 0);
	lv_obj_set_size(ui->menuDemo_mode, 621, 317);
	lv_obj_set_scrollbar_mode(ui->menuDemo_mode, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->menuDemo_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for menuDemo_mode, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->menuDemo_mode, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->menuDemo_mode, lv_color_hex(0xcccccc), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_mode, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_menuDemo_mode_extra_element_items_default
	static lv_style_t style_menuDemo_mode_extra_element_items_default;
	ui_init_style(&style_menuDemo_mode_extra_element_items_default);
	
	lv_style_set_bg_opa(&style_menuDemo_mode_extra_element_items_default, 0);
	lv_style_set_outline_width(&style_menuDemo_mode_extra_element_items_default, 0);
	lv_style_set_border_width(&style_menuDemo_mode_extra_element_items_default, 0);
	lv_style_set_radius(&style_menuDemo_mode_extra_element_items_default, 13);
	lv_style_set_shadow_width(&style_menuDemo_mode_extra_element_items_default, 0);
	lv_obj_add_style(ui->menuDemo_mode_mode_3, &style_menuDemo_mode_extra_element_items_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->menuDemo_mode_mode_2, &style_menuDemo_mode_extra_element_items_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->menuDemo_mode_mode_1, &style_menuDemo_mode_extra_element_items_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_FOCUSED for &style_menuDemo_mode_extra_element_items_focused
	static lv_style_t style_menuDemo_mode_extra_element_items_focused;
	ui_init_style(&style_menuDemo_mode_extra_element_items_focused);
	
	lv_style_set_bg_opa(&style_menuDemo_mode_extra_element_items_focused, 0);
	lv_style_set_outline_width(&style_menuDemo_mode_extra_element_items_focused, 0);
	lv_style_set_border_width(&style_menuDemo_mode_extra_element_items_focused, 0);
	lv_style_set_radius(&style_menuDemo_mode_extra_element_items_focused, 53);
	lv_style_set_shadow_width(&style_menuDemo_mode_extra_element_items_focused, 50);
	lv_style_set_shadow_color(&style_menuDemo_mode_extra_element_items_focused, lv_color_hex(0xfffea9));
	lv_style_set_shadow_opa(&style_menuDemo_mode_extra_element_items_focused, 255);
	lv_style_set_shadow_spread(&style_menuDemo_mode_extra_element_items_focused, 2);
	lv_style_set_shadow_ofs_x(&style_menuDemo_mode_extra_element_items_focused, 0);
	lv_style_set_shadow_ofs_y(&style_menuDemo_mode_extra_element_items_focused, 0);
	lv_obj_add_style(ui->menuDemo_mode_mode_3, &style_menuDemo_mode_extra_element_items_focused, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_add_style(ui->menuDemo_mode_mode_2, &style_menuDemo_mode_extra_element_items_focused, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_add_style(ui->menuDemo_mode_mode_1, &style_menuDemo_mode_extra_element_items_focused, LV_PART_MAIN|LV_STATE_FOCUSED);



	//Write codes menuDemo_mode_img_1
	ui->menuDemo_mode_img_1 = lv_img_create(ui->menuDemo_mode_mode_1);
	lv_obj_add_flag(ui->menuDemo_mode_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->menuDemo_mode_img_1, &_mode1_alpha_211x211);
	lv_img_set_pivot(ui->menuDemo_mode_img_1, 50,50);
	lv_img_set_angle(ui->menuDemo_mode_img_1, 0);
	lv_obj_set_pos(ui->menuDemo_mode_img_1, 53, 52);
	lv_obj_set_size(ui->menuDemo_mode_img_1, 211, 211);
	lv_obj_set_scrollbar_mode(ui->menuDemo_mode_img_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_mode_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->menuDemo_mode_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes menuDemo_mode_img_2
	ui->menuDemo_mode_img_2 = lv_img_create(ui->menuDemo_mode_mode_2);
	lv_obj_add_flag(ui->menuDemo_mode_img_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->menuDemo_mode_img_2, &_mode2_alpha_211x211);
	lv_img_set_pivot(ui->menuDemo_mode_img_2, 50,50);
	lv_img_set_angle(ui->menuDemo_mode_img_2, 0);
	lv_obj_set_pos(ui->menuDemo_mode_img_2, 53, 52);
	lv_obj_set_size(ui->menuDemo_mode_img_2, 211, 211);
	lv_obj_set_scrollbar_mode(ui->menuDemo_mode_img_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_mode_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->menuDemo_mode_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes menuDemo_mode_img_3
	ui->menuDemo_mode_img_3 = lv_img_create(ui->menuDemo_mode_mode_3);
	lv_obj_add_flag(ui->menuDemo_mode_img_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->menuDemo_mode_img_3, &_mode3_alpha_211x211);
	lv_img_set_pivot(ui->menuDemo_mode_img_3, 50,50);
	lv_img_set_angle(ui->menuDemo_mode_img_3, 0);
	lv_obj_set_pos(ui->menuDemo_mode_img_3, 66, 66);
	lv_obj_set_size(ui->menuDemo_mode_img_3, 211, 211);
	lv_obj_set_scrollbar_mode(ui->menuDemo_mode_img_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_mode_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->menuDemo_mode_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menuDemo_btn_del
	ui->menuDemo_btn_del = lv_btn_create(ui->menuDemo);
	ui->menuDemo_btn_del_label = lv_label_create(ui->menuDemo_btn_del);
	lv_label_set_text(ui->menuDemo_btn_del_label, "");
	lv_label_set_long_mode(ui->menuDemo_btn_del_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->menuDemo_btn_del_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->menuDemo_btn_del, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->menuDemo_btn_del, 1104, 34);
	lv_obj_set_size(ui->menuDemo_btn_del, 74, 68);
	lv_obj_set_scrollbar_mode(ui->menuDemo_btn_del, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->menuDemo_btn_del, LV_OBJ_FLAG_HIDDEN);

	//Write style for menuDemo_btn_del, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->menuDemo_btn_del, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->menuDemo_btn_del, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_btn_del, 13, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_btn_del, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->menuDemo_btn_del, &_delete_74x68, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->menuDemo_btn_del, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_recolor(ui->menuDemo_btn_del, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_recolor_opa(ui->menuDemo_btn_del, 166, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->menuDemo_btn_del, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->menuDemo_btn_del, &lv_font_montserratMedium_47, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->menuDemo_btn_del, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menuDemo_phone_calling
	ui->menuDemo_phone_calling = lv_label_create(ui->menuDemo);
	lv_label_set_text(ui->menuDemo_phone_calling, "Calling...");
	lv_label_set_long_mode(ui->menuDemo_phone_calling, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->menuDemo_phone_calling, 672, 262);
	lv_obj_set_size(ui->menuDemo_phone_calling, 344, 145);
	lv_obj_set_scrollbar_mode(ui->menuDemo_phone_calling, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->menuDemo_phone_calling, LV_OBJ_FLAG_HIDDEN);

	//Write style for menuDemo_phone_calling, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->menuDemo_phone_calling, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_phone_calling, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->menuDemo_phone_calling, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->menuDemo_phone_calling, &lv_font_Alatsi_Regular_60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->menuDemo_phone_calling, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->menuDemo_phone_calling, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->menuDemo_phone_calling, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->menuDemo_phone_calling, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->menuDemo_phone_calling, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->menuDemo_phone_calling, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->menuDemo_phone_calling, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->menuDemo_phone_calling, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_phone_calling, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menuDemo_phone_callnum
	ui->menuDemo_phone_callnum = lv_label_create(ui->menuDemo);
	lv_label_set_text(ui->menuDemo_phone_callnum, "");
	lv_label_set_long_mode(ui->menuDemo_phone_callnum, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->menuDemo_phone_callnum, 408, 132);
	lv_obj_set_size(ui->menuDemo_phone_callnum, 826, 145);
	lv_obj_set_scrollbar_mode(ui->menuDemo_phone_callnum, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->menuDemo_phone_callnum, LV_OBJ_FLAG_HIDDEN);

	//Write style for menuDemo_phone_callnum, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->menuDemo_phone_callnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menuDemo_phone_callnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->menuDemo_phone_callnum, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->menuDemo_phone_callnum, &lv_font_Alatsi_Regular_92, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->menuDemo_phone_callnum, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->menuDemo_phone_callnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->menuDemo_phone_callnum, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->menuDemo_phone_callnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->menuDemo_phone_callnum, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->menuDemo_phone_callnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->menuDemo_phone_callnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->menuDemo_phone_callnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menuDemo_phone_callnum, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menuDemo_img_1
	ui->menuDemo_img_1 = lv_img_create(ui->menuDemo);
	lv_obj_add_flag(ui->menuDemo_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->menuDemo_img_1, &_BABA_alpha_323x308);
	lv_img_set_pivot(ui->menuDemo_img_1, 50,50);
	lv_img_set_angle(ui->menuDemo_img_1, 0);
	lv_obj_set_pos(ui->menuDemo_img_1, 27, 366);
	lv_obj_set_size(ui->menuDemo_img_1, 323, 308);
	lv_obj_set_scrollbar_mode(ui->menuDemo_img_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for menuDemo_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->menuDemo_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->menuDemo);

	
	//Init events for screen.
	events_init_menuDemo(ui);
}
