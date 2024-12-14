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
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_status_lbl,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_status_lbl,
    };
    remove_style_funcs[styleIndex](obj);
}

