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


static void screen_slider_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		static char buf[4];
	int slider_value = lv_slider_get_value(guider_ui.screen_slider);
	lv_obj_set_style_img_opa(guider_ui.screen_img_bird, slider_value * 2.5, LV_STATE_DEFAULT);
	snprintf(buf, 4, "%u" , slider_value);
	lv_label_set_text(guider_ui.screen_progress, buf);
		break;
	}
	default:
		break;
	}
}
void events_init_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_slider, screen_slider_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{

}
