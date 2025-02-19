#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_DATE_TIME = 0,
    FLOW_GLOBAL_VARIABLE_TEMP_SET_POINT = 1,
    FLOW_GLOBAL_VARIABLE_MIN_TEMP_SET_POINT = 2,
    FLOW_GLOBAL_VARIABLE_MAX_TEMP_SET_POINT = 3,
    FLOW_GLOBAL_VARIABLE_STEP_TEMP_SET_POINT = 4,
    FLOW_GLOBAL_VARIABLE_TIMER_SET_MIN = 5,
    FLOW_GLOBAL_VARIABLE_TIMER_REMAIN_MIN = 6,
    FLOW_GLOBAL_VARIABLE_START_CLICKED = 7,
    FLOW_GLOBAL_VARIABLE_LIGHT_BTN_CLICKED = 8,
    FLOW_GLOBAL_VARIABLE_LIGHT_STATE = 9,
    FLOW_GLOBAL_VARIABLE_FAN_BTN_CLICKED = 10,
    FLOW_GLOBAL_VARIABLE_FAN_STATE = 11,
    FLOW_GLOBAL_VARIABLE_DOOR_MOTOR_BTN_CLICKED = 12,
    FLOW_GLOBAL_VARIABLE_DOOR_MOTOR_STATE = 13,
    FLOW_GLOBAL_VARIABLE_BOT_RES_BTN_CLICKED = 14,
    FLOW_GLOBAL_VARIABLE_BOT_RES_STATE = 15,
    FLOW_GLOBAL_VARIABLE_TOP_RES_BTN_CLICKED = 16,
    FLOW_GLOBAL_VARIABLE_TOP_RES_STATE = 17,
    FLOW_GLOBAL_VARIABLE_HEATING_MODE = 18
};

// Native global variables

extern int32_t get_var_date_time();
extern void set_var_date_time(int32_t value);
extern int32_t get_var_temp_set_point();
extern void set_var_temp_set_point(int32_t value);
extern int32_t get_var_min_temp_set_point();
extern void set_var_min_temp_set_point(int32_t value);
extern int32_t get_var_max_temp_set_point();
extern void set_var_max_temp_set_point(int32_t value);
extern int32_t get_var_step_temp_set_point();
extern void set_var_step_temp_set_point(int32_t value);
extern int32_t get_var_timer_set_min();
extern void set_var_timer_set_min(int32_t value);
extern int32_t get_var_timer_remain_min();
extern void set_var_timer_remain_min(int32_t value);
extern bool get_var_start_clicked();
extern void set_var_start_clicked(bool value);
extern bool get_var_light_btn_clicked();
extern void set_var_light_btn_clicked(bool value);
extern bool get_var_light_state();
extern void set_var_light_state(bool value);
extern bool get_var_fan_btn_clicked();
extern void set_var_fan_btn_clicked(bool value);
extern bool get_var_fan_state();
extern void set_var_fan_state(bool value);
extern bool get_var_door_motor_btn_clicked();
extern void set_var_door_motor_btn_clicked(bool value);
extern bool get_var_door_motor_state();
extern void set_var_door_motor_state(bool value);
extern bool get_var_bot_res_btn_clicked();
extern void set_var_bot_res_btn_clicked(bool value);
extern bool get_var_bot_res_state();
extern void set_var_bot_res_state(bool value);
extern bool get_var_top_res_btn_clicked();
extern void set_var_top_res_btn_clicked(bool value);
extern bool get_var_top_res_state();
extern void set_var_top_res_state(bool value);
extern int32_t get_var_heating_mode();
extern void set_var_heating_mode(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/