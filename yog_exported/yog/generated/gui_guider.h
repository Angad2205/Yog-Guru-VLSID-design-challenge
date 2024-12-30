/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
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
  
	lv_obj_t *menuDemo;
	bool menuDemo_del;
	lv_obj_t *menuDemo_dashboard_menu;
	lv_obj_t *menuDemo_dashboard_menu_sidebar_page;
	lv_obj_t *menuDemo_dashboard_menu_subpage_1;
	lv_obj_t *menuDemo_dashboard_menu_cont_1;
	lv_obj_t *menuDemo_dashboard_menu_label_1;
	lv_obj_t *menuDemo_dashboard_menu_subpage_2;
	lv_obj_t *menuDemo_dashboard_menu_cont_2;
	lv_obj_t *menuDemo_dashboard_menu_label_2;
	lv_obj_t *menuDemo_dashboard_menu_subpage_3;
	lv_obj_t *menuDemo_dashboard_menu_cont_3;
	lv_obj_t *menuDemo_dashboard_menu_label_3;
	lv_obj_t *menuDemo_dashboard_menu_subpage_4;
	lv_obj_t *menuDemo_dashboard_menu_cont_4;
	lv_obj_t *menuDemo_dashboard_menu_label_4;
	lv_obj_t *menuDemo_battery_label;
	lv_obj_t *menuDemo_battery_img;
	lv_obj_t *menuDemo_battery_spangroup;
	lv_obj_t *menuDemo_radio_spangroup;
	lv_obj_t *menuDemo_radio_label;
	lv_obj_t *menuDemo_radio_slider;
	lv_obj_t *menuDemo_phone_label;
	lv_obj_t *menuDemo_phone_btnm;
	lv_obj_t *menuDemo_imgbtn_call;
	lv_obj_t *menuDemo_imgbtn_call_label;
	lv_obj_t *menuDemo_conditioner_label;
	lv_obj_t *menuDemo_label_1;
	lv_obj_t *menuDemo_mode;
	lv_obj_t *menuDemo_mode_mode_1;
	lv_obj_t *menuDemo_mode_mode_2;
	lv_obj_t *menuDemo_mode_mode_3;
	lv_obj_t *menuDemo_mode_img_1;
	lv_obj_t *menuDemo_mode_img_2;
	lv_obj_t *menuDemo_mode_img_3;
	lv_obj_t *menuDemo_btn_del;
	lv_obj_t *menuDemo_btn_del_label;
	lv_obj_t *menuDemo_phone_calling;
	lv_obj_t *menuDemo_phone_callnum;
	lv_obj_t *menuDemo_img_1;
	lv_obj_t *home_screen;
	bool home_screen_del;
	lv_obj_t *home_screen_img_1;
	lv_obj_t *Yoga_selection;
	bool Yoga_selection_del;
	lv_obj_t *Yoga_selection_img_1;
	lv_obj_t *Yoga_selection_img_2;
	lv_obj_t *Yoga_selection_img_5;
	lv_obj_t *Yoga_selection_img_6;
	lv_obj_t *Yoga_selection_img_7;
	lv_obj_t *Yoga_selection_img_8;
	lv_obj_t *Yoga_selection_img_9;
	lv_obj_t *Yoga_selection_img_10;
	lv_obj_t *Yoga_selection_img_11;
	lv_obj_t *Yoga_selection_img_12;
	lv_obj_t *Yoga_selection_label_2;
	lv_obj_t *Yoga_selection_label_1;
	lv_obj_t *Yoga_selection_label_3;
	lv_obj_t *about_us;
	bool about_us_del;
	lv_obj_t *about_us_about_us;
	lv_obj_t *hastaa;
	bool hastaa_del;
	lv_obj_t *hastaa_img_1;
	lv_obj_t *hastaa_animimg_1;
	lv_obj_t *hastaa_img_3;
	lv_obj_t *hastaa_img_4;
	lv_obj_t *padmasan;
	bool padmasan_del;
	lv_obj_t *padmasan_img_2;
	lv_obj_t *padmasan_img_3;
	lv_obj_t *padmasan_img_4;
	lv_obj_t *padmasan_img_5;
	lv_obj_t *vrikshasan;
	bool vrikshasan_del;
	lv_obj_t *vrikshasan_img_1;
	lv_obj_t *vrikshasan_img_2;
	lv_obj_t *vrikshasan_img_3;
	lv_obj_t *vrikshasan_animimg_1;
	lv_obj_t *qr;
	bool qr_del;
	lv_obj_t *qr_img_1;
	lv_obj_t *padma_intro;
	bool padma_intro_del;
	lv_obj_t *padma_intro_padma;
	lv_obj_t *vriks_intro;
	bool vriks_intro_del;
	lv_obj_t *vriks_intro_img_1;
	lv_obj_t *has_intro;
	bool has_intro_del;
	lv_obj_t *has_intro_hasta_intro;
	lv_obj_t *progress;
	bool progress_del;
	lv_obj_t *progress_img_1;
	lv_obj_t *progress_cb_1;
	lv_obj_t *progress_cb_2;
	lv_obj_t *progress_cb_3;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_menuDemo(lv_ui *ui);
void setup_scr_home_screen(lv_ui *ui);
void setup_scr_Yoga_selection(lv_ui *ui);
void setup_scr_about_us(lv_ui *ui);
void setup_scr_hastaa(lv_ui *ui);
void setup_scr_padmasan(lv_ui *ui);
void setup_scr_vrikshasan(lv_ui *ui);
void setup_scr_qr(lv_ui *ui);
void setup_scr_padma_intro(lv_ui *ui);
void setup_scr_vriks_intro(lv_ui *ui);
void setup_scr_has_intro(lv_ui *ui);
void setup_scr_progress(lv_ui *ui);
LV_IMG_DECLARE(_battery_alpha_530x195);

LV_IMG_DECLARE(_radio_bg_800x214);

LV_IMG_DECLARE(_radio_play_214x214);
LV_IMG_DECLARE(_phone_card_alpha_98x95);
LV_IMG_DECLARE(_phone_card_alpha_98x95);
LV_IMG_DECLARE(_end_call_alpha_98x95);
LV_IMG_DECLARE(_end_call_alpha_98x95);
LV_IMG_DECLARE(_mode1_alpha_211x211);
LV_IMG_DECLARE(_mode2_alpha_211x211);
LV_IMG_DECLARE(_mode3_alpha_211x211);

LV_IMG_DECLARE(_delete_74x68);
LV_IMG_DECLARE(_BABA_alpha_323x308);
LV_IMG_DECLARE(_Yog_alpha_1282x721);
LV_IMG_DECLARE(_16_alpha_1280x721);
LV_IMG_DECLARE(_408_alpha_129x76);
LV_IMG_DECLARE(_405_alpha_86x57);
LV_IMG_DECLARE(_400_alpha_97x65);
LV_IMG_DECLARE(_403_alpha_120x74);
LV_IMG_DECLARE(_410_alpha_121x74);
LV_IMG_DECLARE(_401_alpha_89x74);
LV_IMG_DECLARE(_asan3_alpha_291x463);
LV_IMG_DECLARE(_asan2_alpha_280x458);
LV_IMG_DECLARE(_asan1_alpha_282x458);
LV_IMG_DECLARE(_42_alpha_1284x722);
LV_IMG_DECLARE(_session_alpha_1280x720);
#include "extra/widgets/animimg/lv_animimg.h"
LV_IMG_DECLARE(hastaa_animimg_12);
LV_IMG_DECLARE(hastaa_animimg_13);
LV_IMG_DECLARE(hastaa_animimg_15);
LV_IMG_DECLARE(hastaa_animimg_16);
LV_IMG_DECLARE(hastaa_animimg_17);
LV_IMG_DECLARE(hastaa_animimg_18);
LV_IMG_DECLARE(hastaa_animimg_19);
LV_IMG_DECLARE(hastaa_animimg_110);
LV_IMG_DECLARE(hastaa_animimg_111);
LV_IMG_DECLARE(hastaa_animimg_112);
LV_IMG_DECLARE(hastaa_animimg_113);
LV_IMG_DECLARE(hastaa_animimg_114);
LV_IMG_DECLARE(hastaa_animimg_115);
LV_IMG_DECLARE(hastaa_animimg_116);
LV_IMG_DECLARE(hastaa_animimg_117);
LV_IMG_DECLARE(hastaa_animimg_118);
LV_IMG_DECLARE(hastaa_animimg_119);
LV_IMG_DECLARE(hastaa_animimg_121);
LV_IMG_DECLARE(hastaa_animimg_122);
LV_IMG_DECLARE(hastaa_animimg_123);
LV_IMG_DECLARE(hastaa_animimg_124);
LV_IMG_DECLARE(hastaa_animimg_126);
LV_IMG_DECLARE(hastaa_animimg_127);
LV_IMG_DECLARE(hastaa_animimg_127);
LV_IMG_DECLARE(hastaa_animimg_128);
LV_IMG_DECLARE(hastaa_animimg_130);
LV_IMG_DECLARE(hastaa_animimg_131);
LV_IMG_DECLARE(hastaa_animimg_134);
LV_IMG_DECLARE(hastaa_animimg_136);
LV_IMG_DECLARE(_406_alpha_124x97);
LV_IMG_DECLARE(_407_alpha_122x92);
LV_IMG_DECLARE(_407_alpha_122x88);
LV_IMG_DECLARE(_406_alpha_122x86);
LV_IMG_DECLARE(_pad_alpha_1280x720);
LV_IMG_DECLARE(_407_alpha_120x93);
LV_IMG_DECLARE(_session_alpha_1280x720);
LV_IMG_DECLARE(_406_alpha_128x100);
LV_IMG_DECLARE(_407_alpha_121x99);
#include "extra/widgets/animimg/lv_animimg.h"
LV_IMG_DECLARE(vrikshasan_animimg_1700);
LV_IMG_DECLARE(vrikshasan_animimg_1701);
LV_IMG_DECLARE(vrikshasan_animimg_1702);
LV_IMG_DECLARE(vrikshasan_animimg_1703);
LV_IMG_DECLARE(vrikshasan_animimg_1704);
LV_IMG_DECLARE(vrikshasan_animimg_1705);
LV_IMG_DECLARE(vrikshasan_animimg_1706);
LV_IMG_DECLARE(vrikshasan_animimg_1707);
LV_IMG_DECLARE(vrikshasan_animimg_1708);
LV_IMG_DECLARE(vrikshasan_animimg_1709);
LV_IMG_DECLARE(vrikshasan_animimg_1710);
LV_IMG_DECLARE(vrikshasan_animimg_1711);
LV_IMG_DECLARE(vrikshasan_animimg_1712);
LV_IMG_DECLARE(vrikshasan_animimg_1713);
LV_IMG_DECLARE(vrikshasan_animimg_1714);
LV_IMG_DECLARE(vrikshasan_animimg_1715);
LV_IMG_DECLARE(vrikshasan_animimg_1716);
LV_IMG_DECLARE(vrikshasan_animimg_1717);
LV_IMG_DECLARE(vrikshasan_animimg_1718);
LV_IMG_DECLARE(vrikshasan_animimg_1719);
LV_IMG_DECLARE(_QR_alpha_1280x720);
LV_IMG_DECLARE(_intro1_alpha_1280x720);
LV_IMG_DECLARE(_intro2_alpha_1280x720);
LV_IMG_DECLARE(_intro3_alpha_1280x720);
LV_IMG_DECLARE(_checklist_alpha_1280x720);

LV_FONT_DECLARE(lv_font_montserratMedium_42)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_47)
LV_FONT_DECLARE(lv_font_montserratMedium_52)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_20)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_45)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_40)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_37)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_52)
LV_FONT_DECLARE(lv_font_montserratMedium_37)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_63)
LV_FONT_DECLARE(lv_font_montserratMedium_31)
LV_FONT_DECLARE(lv_font_montserratMedium_74)
LV_FONT_DECLARE(lv_font_montserratMedium_92)
LV_FONT_DECLARE(lv_font_montserratMedium_47)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_60)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_92)
LV_FONT_DECLARE(lv_font_montserratMedium_24)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_33)
LV_FONT_DECLARE(lv_font_montserratMedium_26)
LV_FONT_DECLARE(lv_font_montserratMedium_49)


#ifdef __cplusplus
}
#endif
#endif
