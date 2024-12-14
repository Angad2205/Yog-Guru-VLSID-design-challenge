/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen_1;
	bool screen_1_del;
	lv_obj_t *screen_1_img_1;
	lv_obj_t *screen_7;
	bool screen_7_del;
	lv_obj_t *screen_7_img_1;
	lv_obj_t *screen_7_img_2;
	lv_obj_t *screen_7_imgbtn_1;
	lv_obj_t *screen_7_imgbtn_1_label;
	lv_obj_t *screen_7_img_6;
	lv_obj_t *screen_7_img_7;
	lv_obj_t *screen_7_img_8;
	lv_obj_t *screen_7_img_9;
	lv_obj_t *screen_7_img_10;
	lv_obj_t *screen_7_img_11;
	lv_obj_t *screen_7_img_12;
	lv_obj_t *screen_2;
	bool screen_2_del;
	lv_obj_t *screen_2_img_1;
	lv_obj_t *screen_2_img_2;
	lv_obj_t *screen_2_img_3;
	lv_obj_t *screen_2_img_4;
	lv_obj_t *screen_2_img_5;
	lv_obj_t *screen_2_img_6;
	lv_obj_t *screen_2_img_7;
	lv_obj_t *screen_2_img_8;
	lv_obj_t *screen_2_img_9;
	lv_obj_t *screen_2_img_10;
	lv_obj_t *screen_2_img_11;
	lv_obj_t *screen_3;
	bool screen_3_del;
	lv_obj_t *screen_3_img_1;
	lv_obj_t *screen_3_img_2;
	lv_obj_t *screen_3_img_3;
	lv_obj_t *screen_3_img_4;
	lv_obj_t *screen_3_img_5;
	lv_obj_t *screen_3_img_6;
	lv_obj_t *screen_3_img_7;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;


void setup_scr_screen_1(lv_ui *ui);
void setup_scr_screen_7(lv_ui *ui);
void setup_scr_screen_2(lv_ui *ui);
void setup_scr_screen_3(lv_ui *ui);
LV_IMG_DECLARE(_18_alpha_1281x721);
LV_IMG_DECLARE(_13_alpha_1286x721);
LV_IMG_DECLARE(_baba1_alpha_609x526);
LV_IMG_DECLARE(_baba_alpha_609x526);
LV_IMG_DECLARE(_2345_alpha_102x77);
LV_IMG_DECLARE(_1112_alpha_111x76);
LV_IMG_DECLARE(_12_alpha_125x82);
LV_IMG_DECLARE(_567890_alpha_101x80);
LV_IMG_DECLARE(_09876543_alpha_95x81);
LV_IMG_DECLARE(_532234_alpha_94x89);
LV_IMG_DECLARE(_21212_alpha_89x70);
LV_IMG_DECLARE(_5_alpha_1310x746);
LV_IMG_DECLARE(_2_alpha_296x480);
LV_IMG_DECLARE(_3_alpha_295x484);
LV_IMG_DECLARE(_1_alpha_290x482);
LV_IMG_DECLARE(_7_alpha_124x79);
LV_IMG_DECLARE(_09876543_alpha_95x73);
LV_IMG_DECLARE(_532234_alpha_99x87);
LV_IMG_DECLARE(_21212_alpha_81x62);
LV_IMG_DECLARE(_12_alpha_130x88);
LV_IMG_DECLARE(_1112_alpha_134x87);
LV_IMG_DECLARE(_2345_alpha_99x81);
LV_IMG_DECLARE(_42_alpha_1279x722);
LV_IMG_DECLARE(_1112_alpha_119x78);
LV_IMG_DECLARE(_7_alpha_108x75);
LV_IMG_DECLARE(_09876543_alpha_96x73);
LV_IMG_DECLARE(_532234_alpha_97x77);
LV_IMG_DECLARE(_21212_alpha_94x70);
LV_IMG_DECLARE(_12_alpha_130x82);

LV_FONT_DECLARE(lv_font_montserratMedium_12)


#ifdef __cplusplus
}
#endif
#endif
