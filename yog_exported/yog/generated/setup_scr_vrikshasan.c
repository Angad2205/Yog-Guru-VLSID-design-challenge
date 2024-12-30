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


void setup_scr_vrikshasan(lv_ui *ui)
{
	//Write codes vrikshasan
	ui->vrikshasan = lv_obj_create(NULL);
	lv_obj_set_size(ui->vrikshasan, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->vrikshasan, LV_SCROLLBAR_MODE_OFF);

	//Write style for vrikshasan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vrikshasan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vrikshasan_img_1
	ui->vrikshasan_img_1 = lv_img_create(ui->vrikshasan);
	lv_obj_add_flag(ui->vrikshasan_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->vrikshasan_img_1, &_session_alpha_1280x720);
	lv_img_set_pivot(ui->vrikshasan_img_1, 50,50);
	lv_img_set_angle(ui->vrikshasan_img_1, 0);
	lv_obj_set_pos(ui->vrikshasan_img_1, 0, 0);
	lv_obj_set_size(ui->vrikshasan_img_1, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->vrikshasan_img_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for vrikshasan_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->vrikshasan_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vrikshasan_img_2
	ui->vrikshasan_img_2 = lv_img_create(ui->vrikshasan);
	lv_obj_add_flag(ui->vrikshasan_img_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->vrikshasan_img_2, &_406_alpha_128x100);
	lv_img_set_pivot(ui->vrikshasan_img_2, 50,50);
	lv_img_set_angle(ui->vrikshasan_img_2, 0);
	lv_obj_set_pos(ui->vrikshasan_img_2, 1122, 584);
	lv_obj_set_size(ui->vrikshasan_img_2, 128, 100);
	lv_obj_set_scrollbar_mode(ui->vrikshasan_img_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for vrikshasan_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->vrikshasan_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vrikshasan_img_3
	ui->vrikshasan_img_3 = lv_img_create(ui->vrikshasan);
	lv_obj_add_flag(ui->vrikshasan_img_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->vrikshasan_img_3, &_407_alpha_121x99);
	lv_img_set_pivot(ui->vrikshasan_img_3, 50,50);
	lv_img_set_angle(ui->vrikshasan_img_3, 0);
	lv_obj_set_pos(ui->vrikshasan_img_3, 906, 585);
	lv_obj_set_size(ui->vrikshasan_img_3, 121, 99);
	lv_obj_set_scrollbar_mode(ui->vrikshasan_img_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for vrikshasan_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->vrikshasan_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vrikshasan_animimg_1
	ui->vrikshasan_animimg_1 = lv_animimg_create(ui->vrikshasan);
	lv_animimg_set_src(ui->vrikshasan_animimg_1, (const void **) vrikshasan_animimg_1_imgs, 20, false);
	lv_animimg_set_duration(ui->vrikshasan_animimg_1, 289*20);
	lv_animimg_set_repeat_count(ui->vrikshasan_animimg_1, LV_ANIM_REPEAT_INFINITE);
	lv_animimg_start(ui->vrikshasan_animimg_1);
	lv_obj_set_pos(ui->vrikshasan_animimg_1, 25, 118);
	lv_obj_set_size(ui->vrikshasan_animimg_1, 796, 511);
	lv_obj_set_scrollbar_mode(ui->vrikshasan_animimg_1, LV_SCROLLBAR_MODE_OFF);

	//Update current screen layout.
	lv_obj_update_layout(ui->vrikshasan);

	
	//Init events for screen.
	events_init_vrikshasan(ui);
}
