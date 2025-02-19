#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_temp_set_point_spin(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_spinbox_get_value(ta);
            set_var_temp_set_point(value);
        }
    }
}

static void event_handler_cb_main_timer_set_spn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_spinbox_get_value(ta);
            set_var_timer_set_min(value);
        }
    }
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            // StatusBarContain
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.status_bar_contain = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(100), 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // DateLbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.date_lbl = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 250, LV_PCT(100));
                    lv_label_set_text(obj, "DATE");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe7ceae), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // TimeLbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_lbl = obj;
                    lv_obj_set_pos(obj, 250, 0);
                    lv_obj_set_size(obj, 200, LV_PCT(100));
                    lv_label_set_text(obj, "TIME");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe7ceae), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // TemperatureContainer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.temperature_container = obj;
            lv_obj_set_pos(obj, 0, 50);
            lv_obj_set_size(obj, LV_PCT(100), 100);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_44, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xfff4adad), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // tempActualLbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.temp_actual_lbl = obj;
                    lv_obj_set_pos(obj, 425, 20);
                    lv_obj_set_size(obj, 120, 60);
                    lv_label_set_text(obj, "___");
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // tempSetPointSpin
                    lv_obj_t *obj = lv_spinbox_create(parent_obj);
                    objects.temp_set_point_spin = obj;
                    lv_obj_set_pos(obj, 215, 20);
                    lv_obj_set_size(obj, 120, 60);
                    lv_spinbox_set_digit_format(obj, 3, 0);
                    lv_spinbox_set_range(obj, 60, 500);
                    lv_spinbox_set_rollover(obj, false);
                    lv_spinbox_set_step(obj, 10);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_temp_set_point_spin, LV_EVENT_ALL, 0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_AUTO);
                    lv_obj_set_scroll_snap_x(obj, LV_DIR_TOP);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 20);
                    lv_obj_set_size(obj, 150, 60);
                    lv_label_set_text(obj, "Temp.");
                }
                {
                    // TempDescreaseBtn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.temp_descrease_btn = obj;
                    lv_obj_set_pos(obj, 151, 20);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_add_event_cb(obj, action_action_decrease_temp, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                    lv_obj_add_event_cb(obj, action_action_decrease_temp, LV_EVENT_PRESSED, (void *)0);
                    add_style_light_blue(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "-");
                            lv_obj_add_event_cb(obj, action_action_decrease_temp, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                            lv_obj_add_event_cb(obj, action_action_decrease_temp, LV_EVENT_PRESSED, (void *)0);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // TempIncreaseBtn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.temp_increase_btn = obj;
                    lv_obj_set_pos(obj, 339, 20);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_add_event_cb(obj, action_action_increase_temp, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                    lv_obj_add_event_cb(obj, action_action_increase_temp, LV_EVENT_PRESSED, (void *)0);
                    add_style_light_blue(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "+");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // TimerCtn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.timer_ctn = obj;
            lv_obj_set_pos(obj, 0, 151);
            lv_obj_set_size(obj, LV_PCT(100), 100);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_44, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xfff4adad), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_CURSOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_stop(obj, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xffebdcdc), LV_PART_CURSOR | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // timerRemLbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.timer_rem_lbl = obj;
                    lv_obj_set_pos(obj, 425, 20);
                    lv_obj_set_size(obj, 120, 60);
                    lv_label_set_text(obj, "___");
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc3ef24), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // timerSetSpn
                    lv_obj_t *obj = lv_spinbox_create(parent_obj);
                    objects.timer_set_spn = obj;
                    lv_obj_set_pos(obj, 215, 20);
                    lv_obj_set_size(obj, 120, 60);
                    lv_spinbox_set_digit_format(obj, 3, 0);
                    lv_spinbox_set_range(obj, 0, 900);
                    lv_spinbox_set_rollover(obj, false);
                    lv_spinbox_set_step(obj, 1);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_timer_set_spn, LV_EVENT_ALL, 0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_AUTO);
                    lv_obj_set_scroll_snap_x(obj, LV_DIR_TOP);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_CURSOR | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 20);
                    lv_obj_set_size(obj, 150, 60);
                    lv_label_set_text(obj, "Timer");
                }
                {
                    // TimerDecreaseBtn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.timer_decrease_btn = obj;
                    lv_obj_set_pos(obj, 151, 20);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_add_event_cb(obj, action_timer_decrease_act, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                    lv_obj_add_event_cb(obj, action_timer_decrease_act, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    add_style_light_blue(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "-");
                            lv_obj_add_event_cb(obj, action_action_decrease_temp, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                            lv_obj_add_event_cb(obj, action_action_decrease_temp, LV_EVENT_PRESSED, (void *)0);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // TimerIncreaseBtn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.timer_increase_btn = obj;
                    lv_obj_set_pos(obj, 339, 20);
                    lv_obj_set_size(obj, 60, 60);
                    lv_obj_add_event_cb(obj, action_timer_increase_act, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_add_event_cb(obj, action_timer_increase_act, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                    add_style_light_blue(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "+");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // StartBtn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.start_btn = obj;
            lv_obj_set_pos(obj, 650, 380);
            lv_obj_set_size(obj, 150, 100);
            lv_obj_add_event_cb(obj, action_start_clicked_act, LV_EVENT_PRESSED, (void *)0);
            add_style_light_blue(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // startBtnLbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.start_btn_lbl = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Start");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_44, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // GotoStatusPage
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.goto_status_page = obj;
            lv_obj_set_pos(obj, 1, 380);
            lv_obj_set_size(obj, 150, 100);
            lv_obj_add_event_cb(obj, action_goto_status_page_act, LV_EVENT_PRESSED, (void *)0);
            add_style_light_blue(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // GotoStatusPageLbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.goto_status_page_lbl = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Status");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // Goto Test Page
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.goto_test_page = obj;
            lv_obj_set_pos(obj, 155, 380);
            lv_obj_set_size(obj, 150, 100);
            lv_obj_add_event_cb(obj, action_goto_test_page, LV_EVENT_PRESSED, (void *)0);
            add_style_light_blue(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // GotoStatusPageLbl_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.goto_status_page_lbl_1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Test");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // BakeBtn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.bake_btn = obj;
            lv_obj_set_pos(obj, 0, 266);
            lv_obj_set_size(obj, 150, 100);
            add_style_light_blue(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // BakeLbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.bake_lbl = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Bake");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // BroilBtn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.broil_btn = obj;
            lv_obj_set_pos(obj, 219, 266);
            lv_obj_set_size(obj, 150, 100);
            add_style_light_blue(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // BroilLbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.broil_lbl = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Broil");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_main() {
    {
        int32_t new_val = get_var_temp_set_point();
        int32_t cur_val = lv_spinbox_get_value(objects.temp_set_point_spin);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.temp_set_point_spin;
            lv_spinbox_set_value(objects.temp_set_point_spin, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_timer_set_min();
        int32_t cur_val = lv_spinbox_get_value(objects.timer_set_spn);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.timer_set_spn;
            lv_spinbox_set_value(objects.timer_set_spn, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_status_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.status_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 350, LV_PCT(80));
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_goto_main, LV_EVENT_PRESSED, (void *)0);
            add_style_light_blue(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Goto Main");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // ipAddrLbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ip_addr_lbl = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 150, 30);
            lv_label_set_text(obj, "ip address");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_status_page() {
}

void create_screen_test_components_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.test_components_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 0, LV_PCT(90));
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_goto_main, LV_EVENT_PRESSED, (void *)0);
            add_style_light_blue(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Goto Main");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 150, 100);
            lv_obj_add_event_cb(obj, action_light_control_act, LV_EVENT_PRESSED, (void *)0);
            add_style_light_blue(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Light");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_44, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 155, 0);
            lv_obj_set_size(obj, 150, 100);
            lv_obj_add_event_cb(obj, action_fan_control_act, LV_EVENT_PRESSED, (void *)0);
            add_style_light_blue(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Fan");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_44, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 310, 0);
            lv_obj_set_size(obj, 150, 100);
            lv_obj_add_event_cb(obj, action_door_motor_control_act, LV_EVENT_PRESSED, (void *)0);
            add_style_light_blue(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Door");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_44, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 620, 0);
            lv_obj_set_size(obj, 150, 100);
            lv_obj_add_event_cb(obj, action_bot_res_control_act, LV_EVENT_PRESSED, (void *)0);
            add_style_light_blue(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Bot R");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_44, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 465, 0);
            lv_obj_set_size(obj, 150, 100);
            lv_obj_add_event_cb(obj, action_top_res_control_act, LV_EVENT_PRESSED, (void *)0);
            add_style_light_blue(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Top R");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_44, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_test_components_page() {
}


void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_status_page();
    create_screen_test_components_page();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_status_page,
    tick_screen_test_components_page,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
