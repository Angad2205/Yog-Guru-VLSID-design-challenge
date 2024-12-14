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



void setup_scr_screen_2(lv_ui *ui)
{
    //Write codes screen_2
    ui->screen_2 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_2, 1280, 720);
    lv_obj_set_scrollbar_mode(ui->screen_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_2_img_1
    ui->screen_2_img_1 = lv_img_create(ui->screen_2);
    lv_obj_add_flag(ui->screen_2_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_2_img_1, &_5_alpha_1310x746);
    lv_img_set_pivot(ui->screen_2_img_1, 50,50);
    lv_img_set_angle(ui->screen_2_img_1, 0);
    lv_obj_set_pos(ui->screen_2_img_1, 0, 0);
    lv_obj_set_size(ui->screen_2_img_1, 1310, 746);

    //Write style for screen_2_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_2_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_2_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_2_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_2_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_2_img_2
    ui->screen_2_img_2 = lv_img_create(ui->screen_2);
    lv_obj_add_flag(ui->screen_2_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_2_img_2, &_2_alpha_296x480);
    lv_img_set_pivot(ui->screen_2_img_2, 50,50);
    lv_img_set_angle(ui->screen_2_img_2, 0);
    lv_obj_set_pos(ui->screen_2_img_2, 290, 86);
    lv_obj_set_size(ui->screen_2_img_2, 296, 480);

    //Write style for screen_2_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_2_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_2_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_2_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_2_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_2_img_3
    ui->screen_2_img_3 = lv_img_create(ui->screen_2);
    lv_obj_add_flag(ui->screen_2_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_2_img_3, &_3_alpha_295x484);
    lv_img_set_pivot(ui->screen_2_img_3, 50,50);
    lv_img_set_angle(ui->screen_2_img_3, 0);
    lv_obj_set_pos(ui->screen_2_img_3, 641, 86);
    lv_obj_set_size(ui->screen_2_img_3, 295, 484);

    //Write style for screen_2_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_2_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_2_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_2_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_2_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_2_img_4
    ui->screen_2_img_4 = lv_img_create(ui->screen_2);
    lv_obj_add_flag(ui->screen_2_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_2_img_4, &_1_alpha_290x482);
    lv_img_set_pivot(ui->screen_2_img_4, 50,50);
    lv_img_set_angle(ui->screen_2_img_4, 0);
    lv_obj_set_pos(ui->screen_2_img_4, 998, 86);
    lv_obj_set_size(ui->screen_2_img_4, 290, 482);

    //Write style for screen_2_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_2_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_2_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_2_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_2_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_2_img_5
    ui->screen_2_img_5 = lv_img_create(ui->screen_2);
    lv_obj_add_flag(ui->screen_2_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_2_img_5, &_7_alpha_124x79);
    lv_img_set_pivot(ui->screen_2_img_5, 50,50);
    lv_img_set_angle(ui->screen_2_img_5, 0);
    lv_obj_set_pos(ui->screen_2_img_5, -4, 370);
    lv_obj_set_size(ui->screen_2_img_5, 124, 79);

    //Write style for screen_2_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_2_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_2_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_2_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_2_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_2_img_6
    ui->screen_2_img_6 = lv_img_create(ui->screen_2);
    lv_obj_add_flag(ui->screen_2_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_2_img_6, &_09876543_alpha_95x73);
    lv_img_set_pivot(ui->screen_2_img_6, 50,50);
    lv_img_set_angle(ui->screen_2_img_6, 0);
    lv_obj_set_pos(ui->screen_2_img_6, 0, 280);
    lv_obj_set_size(ui->screen_2_img_6, 95, 73);

    //Write style for screen_2_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_2_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_2_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_2_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_2_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_2_img_7
    ui->screen_2_img_7 = lv_img_create(ui->screen_2);
    lv_obj_add_flag(ui->screen_2_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_2_img_7, &_532234_alpha_99x87);
    lv_img_set_pivot(ui->screen_2_img_7, 50,50);
    lv_img_set_angle(ui->screen_2_img_7, 0);
    lv_obj_set_pos(ui->screen_2_img_7, -4, 181);
    lv_obj_set_size(ui->screen_2_img_7, 99, 87);

    //Write style for screen_2_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_2_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_2_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_2_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_2_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_2_img_8
    ui->screen_2_img_8 = lv_img_create(ui->screen_2);
    lv_obj_add_flag(ui->screen_2_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_2_img_8, &_21212_alpha_81x62);
    lv_img_set_pivot(ui->screen_2_img_8, 50,50);
    lv_img_set_angle(ui->screen_2_img_8, 0);
    lv_obj_set_pos(ui->screen_2_img_8, 7, 107);
    lv_obj_set_size(ui->screen_2_img_8, 81, 62);

    //Write style for screen_2_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_2_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_2_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_2_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_2_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_2_img_9
    ui->screen_2_img_9 = lv_img_create(ui->screen_2);
    lv_obj_add_flag(ui->screen_2_img_9, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_2_img_9, &_12_alpha_130x88);
    lv_img_set_pivot(ui->screen_2_img_9, 50,50);
    lv_img_set_angle(ui->screen_2_img_9, 0);
    lv_obj_set_pos(ui->screen_2_img_9, -31, -5);
    lv_obj_set_size(ui->screen_2_img_9, 130, 88);

    //Write style for screen_2_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_2_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_2_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_2_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_2_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_2_img_10
    ui->screen_2_img_10 = lv_img_create(ui->screen_2);
    lv_obj_add_flag(ui->screen_2_img_10, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_2_img_10, &_1112_alpha_134x87);
    lv_img_set_pivot(ui->screen_2_img_10, 50,50);
    lv_img_set_angle(ui->screen_2_img_10, 0);
    lv_obj_set_pos(ui->screen_2_img_10, -18, 460);
    lv_obj_set_size(ui->screen_2_img_10, 134, 87);

    //Write style for screen_2_img_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_2_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_2_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_2_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_2_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_2_img_11
    ui->screen_2_img_11 = lv_img_create(ui->screen_2);
    lv_obj_add_flag(ui->screen_2_img_11, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_2_img_11, &_2345_alpha_99x81);
    lv_img_set_pivot(ui->screen_2_img_11, 50,50);
    lv_img_set_angle(ui->screen_2_img_11, 0);
    lv_obj_set_pos(ui->screen_2_img_11, 1, 668);
    lv_obj_set_size(ui->screen_2_img_11, 99, 81);

    //Write style for screen_2_img_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_2_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_2_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_2_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_2_img_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_2.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_2);

    //Init events for screen.
    events_init_screen_2(ui);
}
