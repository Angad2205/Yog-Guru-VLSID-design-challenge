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


void setup_scr_padmasan(lv_ui *ui)
{
	//Write codes padmasan
	ui->padmasan = lv_obj_create(NULL);
	lv_obj_set_size(ui->padmasan, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->padmasan, LV_SCROLLBAR_MODE_OFF);

	//Write style for padmasan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->padmasan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes padmasan_img_2
	ui->padmasan_img_2 = lv_img_create(ui->padmasan);
	lv_obj_add_flag(ui->padmasan_img_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->padmasan_img_2, &_407_alpha_122x88);
	lv_img_set_pivot(ui->padmasan_img_2, 50,50);
	lv_img_set_angle(ui->padmasan_img_2, 0);
	lv_obj_set_pos(ui->padmasan_img_2, 905, 590);
	lv_obj_set_size(ui->padmasan_img_2, 122, 88);
	lv_obj_set_scrollbar_mode(ui->padmasan_img_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for padmasan_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->padmasan_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes padmasan_img_3
	ui->padmasan_img_3 = lv_img_create(ui->padmasan);
	lv_obj_add_flag(ui->padmasan_img_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->padmasan_img_3, &_406_alpha_122x86);
	lv_img_set_pivot(ui->padmasan_img_3, 50,50);
	lv_img_set_angle(ui->padmasan_img_3, 0);
	lv_obj_set_pos(ui->padmasan_img_3, 1126, 590);
	lv_obj_set_size(ui->padmasan_img_3, 122, 86);
	lv_obj_set_scrollbar_mode(ui->padmasan_img_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for padmasan_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->padmasan_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes padmasan_img_4
	ui->padmasan_img_4 = lv_img_create(ui->padmasan);
	lv_obj_add_flag(ui->padmasan_img_4, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->padmasan_img_4, &_pad_alpha_1280x720);
	lv_img_set_pivot(ui->padmasan_img_4, 50,50);
	lv_img_set_angle(ui->padmasan_img_4, 0);
	lv_obj_set_pos(ui->padmasan_img_4, 0, 0);
	lv_obj_set_size(ui->padmasan_img_4, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->padmasan_img_4, LV_SCROLLBAR_MODE_OFF);

	//Write style for padmasan_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->padmasan_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes padmasan_img_5
	ui->padmasan_img_5 = lv_img_create(ui->padmasan);
	lv_obj_add_flag(ui->padmasan_img_5, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->padmasan_img_5, &_407_alpha_120x93);
	lv_img_set_pivot(ui->padmasan_img_5, 50,50);
	lv_img_set_angle(ui->padmasan_img_5, 0);
	lv_obj_set_pos(ui->padmasan_img_5, 907, 590);
	lv_obj_set_size(ui->padmasan_img_5, 120, 93);
	lv_obj_set_scrollbar_mode(ui->padmasan_img_5, LV_SCROLLBAR_MODE_OFF);

	//Write style for padmasan_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->padmasan_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->padmasan);

	
	//Init events for screen.
	events_init_padmasan(ui);
}
