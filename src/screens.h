#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *status_page;
    lv_obj_t *test_components_page;
    lv_obj_t *status_bar_contain;
    lv_obj_t *date_lbl;
    lv_obj_t *time_lbl;
    lv_obj_t *temperature_container;
    lv_obj_t *temp_actual_lbl;
    lv_obj_t *temp_set_point_spin;
    lv_obj_t *temp_descrease_btn;
    lv_obj_t *temp_increase_btn;
    lv_obj_t *timer_ctn;
    lv_obj_t *timer_rem_lbl;
    lv_obj_t *timer_set_spn;
    lv_obj_t *timer_decrease_btn;
    lv_obj_t *timer_increase_btn;
    lv_obj_t *start_btn;
    lv_obj_t *start_btn_lbl;
    lv_obj_t *goto_status_page;
    lv_obj_t *goto_status_page_lbl;
    lv_obj_t *goto_test_page;
    lv_obj_t *goto_status_page_lbl_1;
    lv_obj_t *bake_btn;
    lv_obj_t *bake_lbl;
    lv_obj_t *broil_btn;
    lv_obj_t *broil_lbl;
    lv_obj_t *ip_addr_lbl;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_STATUS_PAGE = 2,
    SCREEN_ID_TEST_COMPONENTS_PAGE = 3,
};

void create_screen_main();
void tick_screen_main();

void create_screen_status_page();
void tick_screen_status_page();

void create_screen_test_components_page();
void tick_screen_test_components_page();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/