/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
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



void setup_scr_screen_3(lv_ui *ui)
{
    //Write codes screen_3
    ui->screen_3 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_3, 1280, 720);
    lv_obj_set_scrollbar_mode(ui->screen_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_3_img_1
    ui->screen_3_img_1 = lv_img_create(ui->screen_3);
    lv_obj_add_flag(ui->screen_3_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_3_img_1, &_42_alpha_1279x722);
    lv_img_set_pivot(ui->screen_3_img_1, 50,50);
    lv_img_set_angle(ui->screen_3_img_1, 0);
    lv_obj_set_pos(ui->screen_3_img_1, -3, 0);
    lv_obj_set_size(ui->screen_3_img_1, 1279, 722);

    //Write style for screen_3_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_3_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_3_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_3_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_3_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_3_img_2
    ui->screen_3_img_2 = lv_img_create(ui->screen_3);
    lv_obj_add_flag(ui->screen_3_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_3_img_2, &_1112_alpha_119x78);
    lv_img_set_pivot(ui->screen_3_img_2, 50,50);
    lv_img_set_angle(ui->screen_3_img_2, 0);
    lv_obj_set_pos(ui->screen_3_img_2, -3, 484);
    lv_obj_set_size(ui->screen_3_img_2, 119, 78);

    //Write style for screen_3_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_3_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_3_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_3_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_3_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_3_img_3
    ui->screen_3_img_3 = lv_img_create(ui->screen_3);
    lv_obj_add_flag(ui->screen_3_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_3_img_3, &_7_alpha_108x75);
    lv_img_set_pivot(ui->screen_3_img_3, 50,50);
    lv_img_set_angle(ui->screen_3_img_3, 0);
    lv_obj_set_pos(ui->screen_3_img_3, 7, 397);
    lv_obj_set_size(ui->screen_3_img_3, 108, 75);

    //Write style for screen_3_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_3_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_3_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_3_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_3_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_3_img_4
    ui->screen_3_img_4 = lv_img_create(ui->screen_3);
    lv_obj_add_flag(ui->screen_3_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_3_img_4, &_09876543_alpha_96x73);
    lv_img_set_pivot(ui->screen_3_img_4, 50,50);
    lv_img_set_angle(ui->screen_3_img_4, 0);
    lv_obj_set_pos(ui->screen_3_img_4, 12, 295);
    lv_obj_set_size(ui->screen_3_img_4, 96, 73);

    //Write style for screen_3_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_3_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_3_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_3_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_3_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_3_img_5
    ui->screen_3_img_5 = lv_img_create(ui->screen_3);
    lv_obj_add_flag(ui->screen_3_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_3_img_5, &_532234_alpha_97x77);
    lv_img_set_pivot(ui->screen_3_img_5, 50,50);
    lv_img_set_angle(ui->screen_3_img_5, 0);
    lv_obj_set_pos(ui->screen_3_img_5, 2, 205);
    lv_obj_set_size(ui->screen_3_img_5, 97, 77);

    //Write style for screen_3_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_3_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_3_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_3_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_3_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_3_img_6
    ui->screen_3_img_6 = lv_img_create(ui->screen_3);
    lv_obj_add_flag(ui->screen_3_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_3_img_6, &_21212_alpha_94x70);
    lv_img_set_pivot(ui->screen_3_img_6, 50,50);
    lv_img_set_angle(ui->screen_3_img_6, 0);
    lv_obj_set_pos(ui->screen_3_img_6, 7, 121);
    lv_obj_set_size(ui->screen_3_img_6, 94, 70);

    //Write style for screen_3_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_3_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_3_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_3_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_3_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_3_img_7
    ui->screen_3_img_7 = lv_img_create(ui->screen_3);
    lv_obj_add_flag(ui->screen_3_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_3_img_7, &_12_alpha_130x82);
    lv_img_set_pivot(ui->screen_3_img_7, 50,50);
    lv_img_set_angle(ui->screen_3_img_7, 0);
    lv_obj_set_pos(ui->screen_3_img_7, -21, 12);
    lv_obj_set_size(ui->screen_3_img_7, 130, 82);

    //Write style for screen_3_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_3_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_3_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_3_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_3_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_3.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_3);

    //Init events for screen.
    events_init_screen_3(ui);
}
