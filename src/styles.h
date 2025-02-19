#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: StatusLbl
void add_style_status_lbl(lv_obj_t *obj);
void remove_style_status_lbl(lv_obj_t *obj);

// Style: lightBlue
lv_style_t *get_style_light_blue_MAIN_DEFAULT();
lv_style_t *get_style_light_blue_MAIN_CHECKED();
void add_style_light_blue(lv_obj_t *obj);
void remove_style_light_blue(lv_obj_t *obj);

// Style: clicked
lv_style_t *get_style_clicked_MAIN_DEFAULT();
void add_style_clicked(lv_obj_t *obj);
void remove_style_clicked(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/