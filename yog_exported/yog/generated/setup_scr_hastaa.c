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


void setup_scr_hastaa(lv_ui *ui)
{
	//Write codes hastaa
	ui->hastaa = lv_obj_create(NULL);
	lv_obj_set_size(ui->hastaa, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->hastaa, LV_SCROLLBAR_MODE_OFF);

	//Write style for hastaa, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->hastaa, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes hastaa_img_1
	ui->hastaa_img_1 = lv_img_create(ui->hastaa);
	lv_obj_add_flag(ui->hastaa_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->hastaa_img_1, &_session_alpha_1280x720);
	lv_img_set_pivot(ui->hastaa_img_1, 50,50);
	lv_img_set_angle(ui->hastaa_img_1, 0);
	lv_obj_set_pos(ui->hastaa_img_1, 0, 0);
	lv_obj_set_size(ui->hastaa_img_1, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->hastaa_img_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for hastaa_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->hastaa_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes hastaa_animimg_1
	ui->hastaa_animimg_1 = lv_animimg_create(ui->hastaa);
	lv_animimg_set_src(ui->hastaa_animimg_1, (const void **) hastaa_animimg_1_imgs, 29, false);
	lv_animimg_set_duration(ui->hastaa_animimg_1, 289*29);
	lv_animimg_set_repeat_count(ui->hastaa_animimg_1, LV_ANIM_REPEAT_INFINITE);
	lv_animimg_start(ui->hastaa_animimg_1);
	lv_obj_set_pos(ui->hastaa_animimg_1, 31, 122);
	lv_obj_set_size(ui->hastaa_animimg_1, 796, 511);
	lv_obj_set_scrollbar_mode(ui->hastaa_animimg_1, LV_SCROLLBAR_MODE_OFF);

	//Write codes hastaa_img_3
	ui->hastaa_img_3 = lv_img_create(ui->hastaa);
	lv_obj_add_flag(ui->hastaa_img_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->hastaa_img_3, &_406_alpha_124x97);
	lv_img_set_pivot(ui->hastaa_img_3, 50,50);
	lv_img_set_angle(ui->hastaa_img_3, 0);
	lv_obj_set_pos(ui->hastaa_img_3, 1124, 587);
	lv_obj_set_size(ui->hastaa_img_3, 124, 97);
	lv_obj_set_scrollbar_mode(ui->hastaa_img_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for hastaa_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->hastaa_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes hastaa_img_4
	ui->hastaa_img_4 = lv_img_create(ui->hastaa);
	lv_obj_add_flag(ui->hastaa_img_4, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->hastaa_img_4, &_407_alpha_122x92);
	lv_img_set_pivot(ui->hastaa_img_4, 50,50);
	lv_img_set_angle(ui->hastaa_img_4, 0);
	lv_obj_set_pos(ui->hastaa_img_4, 906, 587);
	lv_obj_set_size(ui->hastaa_img_4, 122, 92);
	lv_obj_set_scrollbar_mode(ui->hastaa_img_4, LV_SCROLLBAR_MODE_OFF);

	//Write style for hastaa_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->hastaa_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->hastaa);

	
	//Init events for screen.
	events_init_hastaa(ui);
}
