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


void setup_scr_screen(lv_ui *ui)
{
	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen, lv_color_hex(0xe8e8e8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_bird
	ui->screen_img_bird = lv_img_create(ui->screen);
	lv_obj_add_flag(ui->screen_img_bird, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_bird, &_scan_example_alpha_666x450);
	lv_img_set_pivot(ui->screen_img_bird, 0,0);
	lv_img_set_angle(ui->screen_img_bird, 0);
	lv_obj_set_pos(ui->screen_img_bird, 517, 135);
	lv_obj_set_size(ui->screen_img_bird, 666, 450);
	lv_obj_set_scrollbar_mode(ui->screen_img_bird, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_img_bird, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_bird, 125, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_slider
	ui->screen_slider = lv_slider_create(ui->screen);
	lv_slider_set_range(ui->screen_slider, 0,100);
	lv_slider_set_value(ui->screen_slider, 50, false);
	lv_obj_set_pos(ui->screen_slider, 48, 381);
	lv_obj_set_size(ui->screen_slider, 389, 18);
	lv_obj_set_scrollbar_mode(ui->screen_slider, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_slider, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_slider, lv_color_hex(0xc4cfcf), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_slider, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_slider, lv_color_hex(0xc1cccd), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_slider, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_slider, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_slider, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_slider, lv_color_hex(0x66b878), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_slider, 133, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_slider, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_slider, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_slider, lv_color_hex(0x66B878), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_slider, 133, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_tips
	ui->screen_tips = lv_label_create(ui->screen);
	lv_label_set_text(ui->screen_tips, "Please slide");
	lv_label_set_long_mode(ui->screen_tips, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_tips, 26, 518);
	lv_obj_set_size(ui->screen_tips, 432, 66);
	lv_obj_set_scrollbar_mode(ui->screen_tips, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_tips, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_tips, lv_color_hex(0x0058C3), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_tips, &lv_font_arial_47, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_tips, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_tips, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_progress
	ui->screen_progress = lv_label_create(ui->screen);
	lv_label_set_text(ui->screen_progress, "50");
	lv_label_set_long_mode(ui->screen_progress, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_progress, 72, 166);
	lv_obj_set_size(ui->screen_progress, 344, 135);
	lv_obj_set_scrollbar_mode(ui->screen_progress, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_progress, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_progress, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_progress, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_progress, lv_color_hex(0xeaca0c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_progress, &lv_font_montserratMedium_127, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_progress, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_progress, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_progress, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_progress, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_progress, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_progress, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_progress, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_progress, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_progress, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen);

	
	//Init events for screen.
	events_init_screen(ui);
}
