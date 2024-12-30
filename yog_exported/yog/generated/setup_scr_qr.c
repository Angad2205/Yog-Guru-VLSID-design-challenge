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


void setup_scr_qr(lv_ui *ui)
{
	//Write codes qr
	ui->qr = lv_obj_create(NULL);
	lv_obj_set_size(ui->qr, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->qr, LV_SCROLLBAR_MODE_OFF);

	//Write style for qr, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->qr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes qr_img_1
	ui->qr_img_1 = lv_img_create(ui->qr);
	lv_obj_add_flag(ui->qr_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->qr_img_1, &_QR_alpha_1280x720);
	lv_img_set_pivot(ui->qr_img_1, 50,50);
	lv_img_set_angle(ui->qr_img_1, 0);
	lv_obj_set_pos(ui->qr_img_1, 0, 0);
	lv_obj_set_size(ui->qr_img_1, 1280, 720);
	lv_obj_set_scrollbar_mode(ui->qr_img_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for qr_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->qr_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->qr);

	
	//Init events for screen.
	events_init_qr(ui);
}
