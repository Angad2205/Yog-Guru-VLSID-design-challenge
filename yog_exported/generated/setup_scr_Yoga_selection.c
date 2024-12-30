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


void setup_scr_Yoga_selection(lv_ui *ui)
{
	//Write codes Yoga_selection
	ui->Yoga_selection = lv_obj_create(NULL);
	lv_obj_set_size(ui->Yoga_selection, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->Yoga_selection, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_img_1
	ui->Yoga_selection_img_1 = lv_img_create(ui->Yoga_selection);
	lv_obj_add_flag(ui->Yoga_selection_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Yoga_selection_img_1, &_16_alpha_1280x721);
	lv_img_set_pivot(ui->Yoga_selection_img_1, 50,50);
	lv_img_set_angle(ui->Yoga_selection_img_1, 0);
	lv_obj_set_pos(ui->Yoga_selection_img_1, 0, 0);
	lv_obj_set_size(ui->Yoga_selection_img_1, 1280, 721);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_img_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->Yoga_selection_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_img_2
	ui->Yoga_selection_img_2 = lv_img_create(ui->Yoga_selection);
	lv_obj_add_flag(ui->Yoga_selection_img_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Yoga_selection_img_2, &_408_alpha_129x76);
	lv_img_set_pivot(ui->Yoga_selection_img_2, 50,50);
	lv_img_set_angle(ui->Yoga_selection_img_2, 0);
	lv_obj_set_pos(ui->Yoga_selection_img_2, -19, 448);
	lv_obj_set_size(ui->Yoga_selection_img_2, 129, 76);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_img_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->Yoga_selection_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_img_5
	ui->Yoga_selection_img_5 = lv_img_create(ui->Yoga_selection);
	lv_obj_add_flag(ui->Yoga_selection_img_5, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Yoga_selection_img_5, &_405_alpha_86x57);
	lv_img_set_pivot(ui->Yoga_selection_img_5, 50,50);
	lv_img_set_angle(ui->Yoga_selection_img_5, 0);
	lv_obj_set_pos(ui->Yoga_selection_img_5, 6, 102);
	lv_obj_set_size(ui->Yoga_selection_img_5, 86, 57);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_img_5, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->Yoga_selection_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_img_6
	ui->Yoga_selection_img_6 = lv_img_create(ui->Yoga_selection);
	lv_obj_add_flag(ui->Yoga_selection_img_6, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Yoga_selection_img_6, &_400_alpha_97x65);
	lv_img_set_pivot(ui->Yoga_selection_img_6, 50,50);
	lv_img_set_angle(ui->Yoga_selection_img_6, 0);
	lv_obj_set_pos(ui->Yoga_selection_img_6, -6, 184);
	lv_obj_set_size(ui->Yoga_selection_img_6, 97, 65);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_img_6, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->Yoga_selection_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_img_7
	ui->Yoga_selection_img_7 = lv_img_create(ui->Yoga_selection);
	lv_obj_add_flag(ui->Yoga_selection_img_7, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Yoga_selection_img_7, &_403_alpha_120x74);
	lv_img_set_pivot(ui->Yoga_selection_img_7, 50,50);
	lv_img_set_angle(ui->Yoga_selection_img_7, 0);
	lv_obj_set_pos(ui->Yoga_selection_img_7, -5, 358);
	lv_obj_set_size(ui->Yoga_selection_img_7, 120, 74);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_img_7, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->Yoga_selection_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_img_8
	ui->Yoga_selection_img_8 = lv_img_create(ui->Yoga_selection);
	lv_obj_add_flag(ui->Yoga_selection_img_8, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Yoga_selection_img_8, &_410_alpha_121x74);
	lv_img_set_pivot(ui->Yoga_selection_img_8, 50,50);
	lv_img_set_angle(ui->Yoga_selection_img_8, 0);
	lv_obj_set_pos(ui->Yoga_selection_img_8, -23, 1);
	lv_obj_set_size(ui->Yoga_selection_img_8, 121, 74);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_img_8, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->Yoga_selection_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_img_9
	ui->Yoga_selection_img_9 = lv_img_create(ui->Yoga_selection);
	lv_obj_add_flag(ui->Yoga_selection_img_9, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Yoga_selection_img_9, &_401_alpha_89x74);
	lv_img_set_pivot(ui->Yoga_selection_img_9, 50,50);
	lv_img_set_angle(ui->Yoga_selection_img_9, 0);
	lv_obj_set_pos(ui->Yoga_selection_img_9, -6, 647);
	lv_obj_set_size(ui->Yoga_selection_img_9, 89, 74);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_img_9, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->Yoga_selection_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_img_10
	ui->Yoga_selection_img_10 = lv_img_create(ui->Yoga_selection);
	lv_obj_add_flag(ui->Yoga_selection_img_10, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Yoga_selection_img_10, &_asan3_alpha_291x463);
	lv_img_set_pivot(ui->Yoga_selection_img_10, 50,50);
	lv_img_set_angle(ui->Yoga_selection_img_10, 0);
	lv_obj_set_pos(ui->Yoga_selection_img_10, 315, 134);
	lv_obj_set_size(ui->Yoga_selection_img_10, 291, 463);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_img_10, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_img_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->Yoga_selection_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_img_11
	ui->Yoga_selection_img_11 = lv_img_create(ui->Yoga_selection);
	lv_obj_add_flag(ui->Yoga_selection_img_11, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Yoga_selection_img_11, &_asan2_alpha_280x458);
	lv_img_set_pivot(ui->Yoga_selection_img_11, 50,50);
	lv_img_set_angle(ui->Yoga_selection_img_11, 0);
	lv_obj_set_pos(ui->Yoga_selection_img_11, 634, 135);
	lv_obj_set_size(ui->Yoga_selection_img_11, 280, 458);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_img_11, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_img_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->Yoga_selection_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_img_12
	ui->Yoga_selection_img_12 = lv_img_create(ui->Yoga_selection);
	lv_obj_add_flag(ui->Yoga_selection_img_12, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Yoga_selection_img_12, &_asan1_alpha_282x458);
	lv_img_set_pivot(ui->Yoga_selection_img_12, 50,50);
	lv_img_set_angle(ui->Yoga_selection_img_12, 0);
	lv_obj_set_pos(ui->Yoga_selection_img_12, 939, 135);
	lv_obj_set_size(ui->Yoga_selection_img_12, 282, 458);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_img_12, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_img_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->Yoga_selection_img_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_label_2
	ui->Yoga_selection_label_2 = lv_label_create(ui->Yoga_selection);
	lv_label_set_text(ui->Yoga_selection_label_2, "HASTA \nUTTANASANA");
	lv_label_set_long_mode(ui->Yoga_selection_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->Yoga_selection_label_2, 643, 545);
	lv_obj_set_size(ui->Yoga_selection_label_2, 289, 63);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_label_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->Yoga_selection_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->Yoga_selection_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->Yoga_selection_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Yoga_selection_label_2, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->Yoga_selection_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->Yoga_selection_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->Yoga_selection_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->Yoga_selection_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->Yoga_selection_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->Yoga_selection_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->Yoga_selection_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->Yoga_selection_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->Yoga_selection_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_label_1
	ui->Yoga_selection_label_1 = lv_label_create(ui->Yoga_selection);
	lv_label_set_text(ui->Yoga_selection_label_1, "VRIKSHASANA");
	lv_label_set_long_mode(ui->Yoga_selection_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->Yoga_selection_label_1, 270, 558);
	lv_obj_set_size(ui->Yoga_selection_label_1, 397, 95);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_label_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->Yoga_selection_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->Yoga_selection_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->Yoga_selection_label_1, lv_color_hex(0xffcd00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Yoga_selection_label_1, &lv_font_montserratMedium_33, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->Yoga_selection_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->Yoga_selection_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->Yoga_selection_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->Yoga_selection_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->Yoga_selection_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->Yoga_selection_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->Yoga_selection_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->Yoga_selection_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->Yoga_selection_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Yoga_selection_label_3
	ui->Yoga_selection_label_3 = lv_label_create(ui->Yoga_selection);
	lv_label_set_text(ui->Yoga_selection_label_3, "PADMASANA");
	lv_label_set_long_mode(ui->Yoga_selection_label_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->Yoga_selection_label_3, 973, 558);
	lv_obj_set_size(ui->Yoga_selection_label_3, 230, 36);
	lv_obj_set_scrollbar_mode(ui->Yoga_selection_label_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for Yoga_selection_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->Yoga_selection_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->Yoga_selection_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->Yoga_selection_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Yoga_selection_label_3, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->Yoga_selection_label_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->Yoga_selection_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->Yoga_selection_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->Yoga_selection_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->Yoga_selection_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->Yoga_selection_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->Yoga_selection_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->Yoga_selection_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->Yoga_selection_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->Yoga_selection);

	
	//Init events for screen.
	events_init_Yoga_selection(ui);
}
