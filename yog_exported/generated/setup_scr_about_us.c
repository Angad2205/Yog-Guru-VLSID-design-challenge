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


void setup_scr_about_us(lv_ui *ui)
{
	//Write codes about_us
	ui->about_us = lv_obj_create(NULL);
	lv_obj_set_size(ui->about_us, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->about_us, LV_SCROLLBAR_MODE_OFF);

	//Write style for about_us, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->about_us, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes about_us_about_us
	ui->about_us_about_us = lv_img_create(ui->about_us);
	lv_obj_add_flag(ui->about_us_about_us, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->about_us_about_us, &_42_alpha_1284x722);
	lv_img_set_pivot(ui->about_us_about_us, 50,50);
	lv_img_set_angle(ui->about_us_about_us, 0);
	lv_obj_set_pos(ui->about_us_about_us, 0, 0);
	lv_obj_set_size(ui->about_us_about_us, 1284, 722);
	lv_obj_set_scrollbar_mode(ui->about_us_about_us, LV_SCROLLBAR_MODE_OFF);

	//Write style for about_us_about_us, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->about_us_about_us, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->about_us);

	
	//Init events for screen.
	events_init_about_us(ui);
}
