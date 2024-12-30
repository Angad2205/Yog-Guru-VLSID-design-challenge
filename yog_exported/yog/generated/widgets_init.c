/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include "gui_guider.h"
#include "widgets_init.h"


__attribute__((unused)) void kb_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL){
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

__attribute__((unused)) void ta_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
#if LV_USE_KEYBOARD || LV_USE_ZH_KEYBOARD
    lv_obj_t *ta = lv_event_get_target(e);
#endif
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
    {
#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED)
    {

#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_background(kb);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

#if LV_USE_ANALOGCLOCK != 0
void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if(*sec == 60)
    {
        *sec = 0;
        (*min)++;
    }
    if(*min == 60)
    {
        *min = 0;
        if(*hour < 12)
        {
            (*hour)++;
        } else {
            (*hour)++;
            *hour = *hour %12;
        }
    }
}
#endif


const lv_img_dsc_t * hastaa_animimg_1_imgs[29] = { 
	&hastaa_animimg_12,
	&hastaa_animimg_13,
	&hastaa_animimg_15,
	&hastaa_animimg_16,
	&hastaa_animimg_17,
	&hastaa_animimg_18,
	&hastaa_animimg_19,
	&hastaa_animimg_110,
	&hastaa_animimg_111,
	&hastaa_animimg_112,
	&hastaa_animimg_113,
	&hastaa_animimg_114,
	&hastaa_animimg_115,
	&hastaa_animimg_116,
	&hastaa_animimg_117,
	&hastaa_animimg_118,
	&hastaa_animimg_119,
	&hastaa_animimg_121,
	&hastaa_animimg_122,
	&hastaa_animimg_123,
	&hastaa_animimg_124,
	&hastaa_animimg_126,
	&hastaa_animimg_127,
	&hastaa_animimg_127,
	&hastaa_animimg_128,
	&hastaa_animimg_130,
	&hastaa_animimg_131,
	&hastaa_animimg_134,
	&hastaa_animimg_136, 
};
const lv_img_dsc_t * vrikshasan_animimg_1_imgs[20] = { 
	&vrikshasan_animimg_1700,
	&vrikshasan_animimg_1701,
	&vrikshasan_animimg_1702,
	&vrikshasan_animimg_1703,
	&vrikshasan_animimg_1704,
	&vrikshasan_animimg_1705,
	&vrikshasan_animimg_1706,
	&vrikshasan_animimg_1707,
	&vrikshasan_animimg_1708,
	&vrikshasan_animimg_1709,
	&vrikshasan_animimg_1710,
	&vrikshasan_animimg_1711,
	&vrikshasan_animimg_1712,
	&vrikshasan_animimg_1713,
	&vrikshasan_animimg_1714,
	&vrikshasan_animimg_1715,
	&vrikshasan_animimg_1716,
	&vrikshasan_animimg_1717,
	&vrikshasan_animimg_1718,
	&vrikshasan_animimg_1719, 
};
