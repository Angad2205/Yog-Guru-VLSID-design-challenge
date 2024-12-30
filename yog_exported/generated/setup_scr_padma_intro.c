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


void setup_scr_padma_intro(lv_ui *ui)
{
	//Write codes padma_intro
	ui->padma_intro = lv_obj_create(NULL);
	lv_obj_set_size(ui->padma_intro, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->padma_intro, LV_SCROLLBAR_MODE_OFF);

	//Write style for padma_intro, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->padma_intro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes padma_intro_padma
	ui->padma_intro_padma = lv_img_create(ui->padma_intro);
	lv_obj_add_flag(ui->padma_intro_padma, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->padma_intro_padma, &_intro1_alpha_1280x720);
	lv_img_set_pivot(ui->padma_intro_padma, 50,50);
	lv_img_set_angle(ui->padma_intro_padma, 0);
	lv_obj_set_pos(ui->padma_intro_padma, 0, 0);
	lv_obj_set_size(ui->padma_intro_padma, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->padma_intro_padma, LV_SCROLLBAR_MODE_OFF);

	//Write style for padma_intro_padma, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->padma_intro_padma, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->padma_intro);

	
	//Init events for screen.
	events_init_padma_intro(ui);
}
