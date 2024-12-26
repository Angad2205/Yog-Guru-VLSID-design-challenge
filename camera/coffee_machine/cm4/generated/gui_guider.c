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


void ui_init_style(lv_style_t * style)
{
  if (style->prop_cnt > 1)
    lv_style_reset(style);
  else
    lv_style_init(style);
}

void init_scr_del_flag(lv_ui *ui)
{
  
	ui->screen_del = true;
}


 lv_img_dsc_t _scan_example_alpha_666x450 = {
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 666,
  .header.h = 450,
  .data_size = 299700 * LV_IMG_PX_SIZE_ALPHA_BYTE,
};


void setup_imgs(unsigned char *base)
{
	lv_img_dsc_t _scan_example_alpha_666x450;
	_scan_example_alpha_666x450.data = (base + 0);

}

void setup_ui(lv_ui *ui)
{
  init_scr_del_flag(ui);
  setup_scr_screen(ui);
  lv_scr_load(ui->screen);
}
