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
    FLOW_GLOBAL_VARIABLE_START_CLICKED = 7
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


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/