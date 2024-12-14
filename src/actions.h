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


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/