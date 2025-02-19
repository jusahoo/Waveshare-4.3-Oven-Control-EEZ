#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "screens.h"

//
// Style: StatusLbl
//

void add_style_status_lbl(lv_obj_t *obj) {
};

void remove_style_status_lbl(lv_obj_t *obj) {
};

//
// Style: lightBlue
//

void init_style_light_blue_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_font(style, &lv_font_montserrat_40);
};

lv_style_t *get_style_light_blue_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_light_blue_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_light_blue_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff21f35d));
};

lv_style_t *get_style_light_blue_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_light_blue_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_light_blue(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_light_blue_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_light_blue_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_light_blue(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_light_blue_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_light_blue_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
// Style: clicked
//

void init_style_clicked_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff21f395));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
};

lv_style_t *get_style_clicked_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_clicked_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_clicked(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_clicked_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_clicked(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_clicked_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_status_lbl,
        add_style_light_blue,
        add_style_clicked,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_status_lbl,
        remove_style_light_blue,
        remove_style_clicked,
    };
    remove_style_funcs[styleIndex](obj);
}

