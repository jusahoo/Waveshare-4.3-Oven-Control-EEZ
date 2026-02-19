#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_action_increase_temp(lv_event_t * e);
extern void action_action_decrease_temp(lv_event_t * e);
extern void action_timer_increase_act(lv_event_t * e);
extern void action_timer_decrease_act(lv_event_t * e);
extern void action_goto_main(lv_event_t * e);
extern void action_goto_status_page_act(lv_event_t * e);
extern void action_start_clicked_act(lv_event_t * e);
extern void action_goto_test_page(lv_event_t * e);
extern void action_light_control_act(lv_event_t * e);
extern void action_fan_control_act(lv_event_t * e);
extern void action_door_motor_control_act(lv_event_t * e);
extern void action_bot_res_control_act(lv_event_t * e);
extern void action_top_res_control_act(lv_event_t * e);
extern void action_bake_ctl_act(lv_event_t * e);
extern void action_broil_ctl_act(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/