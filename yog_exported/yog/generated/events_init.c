/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"


static char phone_number[20];
lv_obj_t * element_pre;
lv_obj_t * element_act;
static void menuDemo_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SCREEN_LOADED:
	{
		lv_spangroup_set_align(guider_ui.menuDemo_radio_spangroup, LV_TEXT_ALIGN_RIGHT);
	
	lv_obj_scroll_by(guider_ui.menuDemo_mode, -120, 0, LV_ANIM_OFF);
	
	lv_event_send(guider_ui.menuDemo_dashboard_menu_cont_1, LV_EVENT_CLICKED, NULL);
		break;
	}
	default:
		break;
	}
}
static void menuDemo_dashboard_menu_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		lv_obj_t * cur_page = lv_menu_get_cur_main_page(guider_ui.menuDemo_dashboard_menu);
	bool calling = lv_obj_has_state(guider_ui.menuDemo_imgbtn_call, LV_STATE_CHECKED);
	if(cur_page == guider_ui.menuDemo_dashboard_menu_subpage_3)
	{
	    lv_obj_clear_flag(guider_ui.menuDemo_btn_del, LV_OBJ_FLAG_HIDDEN);
	    if (calling)
	    {
	        lv_obj_clear_flag(guider_ui.menuDemo_phone_callnum, LV_OBJ_FLAG_HIDDEN);
	        lv_obj_clear_flag(guider_ui.menuDemo_phone_calling, LV_OBJ_FLAG_HIDDEN);
	    }
	}
	else
	{
	    lv_obj_add_flag(guider_ui.menuDemo_btn_del, LV_OBJ_FLAG_HIDDEN);
	    if (calling)
	    {
	        lv_obj_add_flag(guider_ui.menuDemo_phone_callnum, LV_OBJ_FLAG_HIDDEN);
	        lv_obj_add_flag(guider_ui.menuDemo_phone_calling, LV_OBJ_FLAG_HIDDEN);
	    }
	}
		break;
	}
	default:
		break;
	}
}
static void menuDemo_radio_slider_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		int32_t slider_value = lv_slider_get_value(guider_ui.menuDemo_radio_slider);
	lv_span_t * fre_span = lv_spangroup_get_child(guider_ui.menuDemo_radio_spangroup, 0);
	float radio_value = ((float)slider_value * 0.8) + 73.6;
	
	char textbuffer[6];
	lv_snprintf(textbuffer, sizeof(textbuffer), "%.1f", radio_value);
	lv_span_set_text(fre_span, textbuffer);
	
	switch(slider_value) {
	case 10:
	{
	    lv_label_set_text(guider_ui.menuDemo_radio_label, "Do Lotus Pose");
	}
	    break;
	case 20:
	{
	    lv_label_set_text(guider_ui.menuDemo_radio_label, "Do Mountain Pose");
	}
	    break;
	case 40:
	{
	    lv_label_set_text(guider_ui.menuDemo_radio_label, "Do Mountain Pose");
	}
	    break;
	case 60:
	{
	    lv_label_set_text(guider_ui.menuDemo_radio_label, "Do Hasta Tadasana");
	}
	    break;
	case 80:
	{
	    lv_label_set_text(guider_ui.menuDemo_radio_label, "Do Hasta Tadasana");
	}
	    break;
	}
		break;
	}
	default:
		break;
	}
}
static void menuDemo_phone_btnm_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
	int len = strlen(phone_number);
	if (len <= 10)
	{
	    uint16_t sel_id = lv_btnmatrix_get_selected_btn(guider_ui.menuDemo_phone_btnm);
	    strcat(phone_number, lv_btnmatrix_get_btn_text(guider_ui.menuDemo_phone_btnm, sel_id));
	    lv_label_set_text(guider_ui.menuDemo_phone_label, phone_number);
	}
		break;
	}
	default:
		break;
	}
}
static void menuDemo_imgbtn_call_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		bool feedback = lv_obj_has_state(guider_ui.menuDemo_imgbtn_call, LV_STATE_CHECKED);
	if (feedback)
	{
	    lv_obj_set_style_opa(guider_ui.menuDemo_phone_btnm, 0, 0);
	    lv_obj_set_style_opa(guider_ui.menuDemo_btn_del, 0, 0);
	    lv_obj_set_style_opa(guider_ui.menuDemo_phone_label, 0, 0);
	    
	    lv_label_set_text(guider_ui.menuDemo_phone_callnum, phone_number);
	    lv_obj_clear_flag(guider_ui.menuDemo_phone_callnum, LV_OBJ_FLAG_HIDDEN);
	    lv_obj_clear_flag(guider_ui.menuDemo_phone_calling, LV_OBJ_FLAG_HIDDEN);
	}
	else
	{
	    lv_obj_set_style_opa(guider_ui.menuDemo_phone_btnm, 255, 0);
	    lv_obj_set_style_opa(guider_ui.menuDemo_btn_del, 255, 0);
	    lv_obj_set_style_opa(guider_ui.menuDemo_phone_label, 255, 0);
	
	    lv_obj_add_flag(guider_ui.menuDemo_phone_callnum, LV_OBJ_FLAG_HIDDEN);
	    lv_obj_add_flag(guider_ui.menuDemo_phone_calling, LV_OBJ_FLAG_HIDDEN);
	}
		break;
	}
	default:
		break;
	}
}
static void menuDemo_mode_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SCROLL_END:
	{
		element_act = lv_carousel_get_element_act(guider_ui.menuDemo_mode);
	if(element_act != element_pre) {
	    lv_obj_t * img_mode;
	    img_mode = lv_obj_get_child(element_act, 0);
	    lv_img_set_zoom(img_mode, 350);
	    lv_obj_set_style_img_recolor(img_mode, lv_color_hex(0xfff770), 0);
	    lv_obj_set_style_img_recolor_opa(img_mode, 255, 0);
	    
	    img_mode = lv_obj_get_child(element_pre, 0);
	    lv_img_set_zoom(img_mode, 256);
	    lv_obj_set_style_img_recolor_opa(img_mode, 0, 0);
	}
		break;
	}
	case LV_EVENT_SCROLL_BEGIN:
	{
		element_pre = lv_carousel_get_element_act(guider_ui.menuDemo_mode);
		break;
	}
	default:
		break;
	}
}
static void menuDemo_btn_del_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
	int p_len = strlen(phone_number);
	if (p_len > 0)
	{
	    phone_number[p_len-1] = '\0';
	    lv_label_set_text(guider_ui.menuDemo_phone_label, phone_number);
	}
		break;
	}
	default:
		break;
	}
}
static void menuDemo_img_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.Yoga_selection_del == true) {
	          setup_scr_Yoga_selection(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.Yoga_selection, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, true);
	        guider_ui.Yoga_selection_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_menuDemo(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->menuDemo, menuDemo_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->menuDemo_dashboard_menu, menuDemo_dashboard_menu_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->menuDemo_radio_slider, menuDemo_radio_slider_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->menuDemo_phone_btnm, menuDemo_phone_btnm_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->menuDemo_imgbtn_call, menuDemo_imgbtn_call_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->menuDemo_mode, menuDemo_mode_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->menuDemo_btn_del, menuDemo_btn_del_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->menuDemo_img_1, menuDemo_img_1_event_handler, LV_EVENT_ALL, NULL);
}
static void home_screen_img_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.Yoga_selection_del == true) {
	          setup_scr_Yoga_selection(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.Yoga_selection, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 200, true);
	        guider_ui.Yoga_selection_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_home_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->home_screen_img_1, home_screen_img_1_event_handler, LV_EVENT_ALL, NULL);
}
static void Yoga_selection_img_2_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.progress_del == true) {
	          setup_scr_progress(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.progress, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 200, 200, true);
	        guider_ui.progress_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void Yoga_selection_img_5_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.menuDemo_del == true) {
	          setup_scr_menuDemo(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.menuDemo, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 200, 200, true);
	        guider_ui.menuDemo_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void Yoga_selection_img_6_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.menuDemo_del == true) {
	          setup_scr_menuDemo(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.menuDemo, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true);
	        guider_ui.menuDemo_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void Yoga_selection_img_7_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.qr_del == true) {
	          setup_scr_qr(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.qr, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, true);
	        guider_ui.qr_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void Yoga_selection_img_8_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.home_screen_del == true) {
	          setup_scr_home_screen(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.home_screen, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 200, true);
	        guider_ui.home_screen_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void Yoga_selection_img_9_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.about_us_del == true) {
	          setup_scr_about_us(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.about_us, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
	        guider_ui.about_us_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void Yoga_selection_img_10_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.vriks_intro_del == true) {
	          setup_scr_vriks_intro(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.vriks_intro, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, true);
	        guider_ui.vriks_intro_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void Yoga_selection_img_11_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.has_intro_del == true) {
	          setup_scr_has_intro(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.has_intro, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true);
	        guider_ui.has_intro_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void Yoga_selection_img_12_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.padma_intro_del == true) {
	          setup_scr_padma_intro(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.padma_intro, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
	        guider_ui.padma_intro_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_Yoga_selection(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->Yoga_selection_img_2, Yoga_selection_img_2_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->Yoga_selection_img_5, Yoga_selection_img_5_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->Yoga_selection_img_6, Yoga_selection_img_6_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->Yoga_selection_img_7, Yoga_selection_img_7_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->Yoga_selection_img_8, Yoga_selection_img_8_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->Yoga_selection_img_9, Yoga_selection_img_9_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->Yoga_selection_img_10, Yoga_selection_img_10_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->Yoga_selection_img_11, Yoga_selection_img_11_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->Yoga_selection_img_12, Yoga_selection_img_12_event_handler, LV_EVENT_ALL, NULL);
}
static void about_us_about_us_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.Yoga_selection_del == true) {
	          setup_scr_Yoga_selection(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.Yoga_selection, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
	        guider_ui.Yoga_selection_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_about_us(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->about_us_about_us, about_us_about_us_event_handler, LV_EVENT_ALL, NULL);
}
static void hastaa_img_3_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.progress_del == true) {
	          setup_scr_progress(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.progress, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, true);
	        guider_ui.progress_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void hastaa_img_4_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.Yoga_selection_del == true) {
	          setup_scr_Yoga_selection(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.Yoga_selection, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 200, true);
	        guider_ui.Yoga_selection_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_hastaa(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->hastaa_img_3, hastaa_img_3_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->hastaa_img_4, hastaa_img_4_event_handler, LV_EVENT_ALL, NULL);
}
static void padmasan_img_2_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
			lv_obj_clean(act_scr);
	        if (guider_ui.Yoga_selection_del == true) {
	          setup_scr_Yoga_selection(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.Yoga_selection, LV_SCR_LOAD_ANIM_OVER_TOP, 200, 200, true);
	        guider_ui.Yoga_selection_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void padmasan_img_4_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.progress_del == true) {
	          setup_scr_progress(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.progress, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true);
	        guider_ui.progress_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void padmasan_img_5_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.Yoga_selection_del == true) {
	          setup_scr_Yoga_selection(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.Yoga_selection, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true);
	        guider_ui.Yoga_selection_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_padmasan(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->padmasan_img_2, padmasan_img_2_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->padmasan_img_4, padmasan_img_4_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->padmasan_img_5, padmasan_img_5_event_handler, LV_EVENT_ALL, NULL);
}
static void vrikshasan_img_2_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.progress_del == true) {
	          setup_scr_progress(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.progress, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 200, true);
	        guider_ui.progress_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void vrikshasan_img_3_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.Yoga_selection_del == true) {
	          setup_scr_Yoga_selection(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.Yoga_selection, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, true);
	        guider_ui.Yoga_selection_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_vrikshasan(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->vrikshasan_img_2, vrikshasan_img_2_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->vrikshasan_img_3, vrikshasan_img_3_event_handler, LV_EVENT_ALL, NULL);
}
static void qr_img_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.Yoga_selection_del == true) {
	          setup_scr_Yoga_selection(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.Yoga_selection, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
	        guider_ui.Yoga_selection_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_qr(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->qr_img_1, qr_img_1_event_handler, LV_EVENT_ALL, NULL);
}
static void padma_intro_padma_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.padmasan_del == true) {
	          setup_scr_padmasan(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.padmasan, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true);
	        guider_ui.padmasan_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_padma_intro(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->padma_intro_padma, padma_intro_padma_event_handler, LV_EVENT_ALL, NULL);
}
static void vriks_intro_img_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.vrikshasan_del == true) {
	          setup_scr_vrikshasan(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.vrikshasan, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, true);
	        guider_ui.vrikshasan_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_vriks_intro(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->vriks_intro_img_1, vriks_intro_img_1_event_handler, LV_EVENT_ALL, NULL);
}
static void has_intro_hasta_intro_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.hastaa_del == true) {
	          setup_scr_hastaa(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.hastaa, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, true);
	        guider_ui.hastaa_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_has_intro(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->has_intro_hasta_intro, has_intro_hasta_intro_event_handler, LV_EVENT_ALL, NULL);
}
static void progress_img_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.Yoga_selection_del == true) {
	          setup_scr_Yoga_selection(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.Yoga_selection, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, false);
	        guider_ui.Yoga_selection_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_progress(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->progress_img_1, progress_img_1_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{

}
