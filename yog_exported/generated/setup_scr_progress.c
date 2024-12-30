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


void setup_scr_progress(lv_ui *ui)
{
	//Write codes progress
	ui->progress = lv_obj_create(NULL);
	lv_obj_set_size(ui->progress, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->progress, LV_SCROLLBAR_MODE_OFF);

	//Write style for progress, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->progress, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes progress_img_1
	ui->progress_img_1 = lv_img_create(ui->progress);
	lv_obj_add_flag(ui->progress_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->progress_img_1, &_checklist_alpha_1280x720);
	lv_img_set_pivot(ui->progress_img_1, 50,50);
	lv_img_set_angle(ui->progress_img_1, 0);
	lv_obj_set_pos(ui->progress_img_1, 0, 0);
	lv_obj_set_size(ui->progress_img_1, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->progress_img_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for progress_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->progress_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes progress_cb_1
	ui->progress_cb_1 = lv_checkbox_create(ui->progress);
	lv_checkbox_set_text(ui->progress_cb_1, "");
	lv_obj_set_pos(ui->progress_cb_1, 267, 624);
	lv_obj_set_scrollbar_mode(ui->progress_cb_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for progress_cb_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->progress_cb_1, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->progress_cb_1, &lv_font_montserratMedium_49, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->progress_cb_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->progress_cb_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->progress_cb_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->progress_cb_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->progress_cb_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->progress_cb_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for progress_cb_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->progress_cb_1, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->progress_cb_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->progress_cb_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->progress_cb_1, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->progress_cb_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->progress_cb_1, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes progress_cb_2
	ui->progress_cb_2 = lv_checkbox_create(ui->progress);
	lv_checkbox_set_text(ui->progress_cb_2, "");
	lv_obj_set_pos(ui->progress_cb_2, 611, 624);
	lv_obj_set_scrollbar_mode(ui->progress_cb_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for progress_cb_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->progress_cb_2, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->progress_cb_2, &lv_font_montserratMedium_49, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->progress_cb_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->progress_cb_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->progress_cb_2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->progress_cb_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->progress_cb_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->progress_cb_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for progress_cb_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->progress_cb_2, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->progress_cb_2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->progress_cb_2, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->progress_cb_2, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->progress_cb_2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->progress_cb_2, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes progress_cb_3
	ui->progress_cb_3 = lv_checkbox_create(ui->progress);
	lv_checkbox_set_text(ui->progress_cb_3, "");
	lv_obj_set_pos(ui->progress_cb_3, 965, 624);
	lv_obj_set_scrollbar_mode(ui->progress_cb_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for progress_cb_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->progress_cb_3, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->progress_cb_3, &lv_font_montserratMedium_49, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->progress_cb_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->progress_cb_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->progress_cb_3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->progress_cb_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->progress_cb_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->progress_cb_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for progress_cb_3, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->progress_cb_3, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->progress_cb_3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->progress_cb_3, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->progress_cb_3, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->progress_cb_3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->progress_cb_3, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->progress);

	
	//Init events for screen.
	events_init_progress(ui);
}
