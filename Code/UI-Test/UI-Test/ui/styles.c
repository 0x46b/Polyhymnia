#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: spinner_style
//

void init_style_spinner_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_color(style, lv_color_darken(lv_color_hex(0xc6c2b3), 15));
};

lv_style_t *get_style_spinner_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_spinner_style_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_spinner_style_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_color(style, lv_color_lighten(lv_color_hex(0x7f5c42), 79));
};

lv_style_t *get_style_spinner_style_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_spinner_style_INDICATOR_DEFAULT(style);
    }
    return style;
};

void add_style_spinner_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_spinner_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_spinner_style_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

void remove_style_spinner_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_spinner_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_spinner_style_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

//
// Style: checkbox_style
//

void init_style_checkbox_style_INDICATOR_CHECKED(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(0xb7bdc1));
    lv_style_set_bg_color(style, lv_color_darken(lv_color_hex(0xc4c2be), 64));
    lv_style_set_text_color(style, lv_color_hex(0x000000));
};

lv_style_t *get_style_checkbox_style_INDICATOR_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_checkbox_style_INDICATOR_CHECKED(style);
    }
    return style;
};

void init_style_checkbox_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0x989790));
};

lv_style_t *get_style_checkbox_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_checkbox_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_checkbox_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_checkbox_style_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_checkbox_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_checkbox_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_checkbox_style_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_checkbox_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: waveform_line_style
//

void init_style_waveform_line_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_line_width(style, 2);
    lv_style_set_line_color(style, lv_color_darken(lv_color_hex(0x989790), 150));
};

lv_style_t *get_style_waveform_line_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_waveform_line_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_waveform_line_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_waveform_line_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_waveform_line_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_waveform_line_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: needle_style
//

void add_style_needle_style(lv_obj_t *obj) {
    (void)obj;
};

void remove_style_needle_style(lv_obj_t *obj) {
    (void)obj;
};

//
// Style: header_label_style
//

void init_style_header_label_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_font(style, &ui_font_rubik_glitch_20);
    lv_style_set_text_color(style, lv_color_hex(0x999790));
};

lv_style_t *get_style_header_label_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_header_label_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_header_label_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_header_label_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_header_label_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_header_label_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: detune_scale_style
//

void add_style_detune_scale_style(lv_obj_t *obj) {
    (void)obj;
};

void remove_style_detune_scale_style(lv_obj_t *obj) {
    (void)obj;
};

//
// Style: button_style
//

void init_style_button_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x989790));
};

lv_style_t *get_style_button_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_button_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_button_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: button_label_style
//

void init_style_button_label_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0x000000));
};

lv_style_t *get_style_button_label_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_label_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_label_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_button_label_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_label_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_button_label_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: bar_style
//

void init_style_bar_style_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x96958f));
    lv_style_set_bg_grad_color(style, lv_color_darken(lv_color_hex(0x989790), 46));
    lv_style_set_bg_grad_dir(style, LV_GRAD_DIR_VER);
};

lv_style_t *get_style_bar_style_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bar_style_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_bar_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_darken(lv_color_hex(0x898882), 64));
};

lv_style_t *get_style_bar_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bar_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_bar_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_bar_style_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_bar_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_bar_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_bar_style_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_bar_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: default_label_style
//

void init_style_default_label_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0x989790));
};

lv_style_t *get_style_default_label_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_default_label_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_default_label_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_default_label_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_default_label_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_default_label_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_spinner_style,
        add_style_checkbox_style,
        add_style_waveform_line_style,
        add_style_needle_style,
        add_style_header_label_style,
        add_style_detune_scale_style,
        add_style_button_style,
        add_style_button_label_style,
        add_style_bar_style,
        add_style_default_label_style,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_spinner_style,
        remove_style_checkbox_style,
        remove_style_waveform_line_style,
        remove_style_needle_style,
        remove_style_header_label_style,
        remove_style_detune_scale_style,
        remove_style_button_style,
        remove_style_button_label_style,
        remove_style_bar_style,
        remove_style_default_label_style,
    };
    remove_style_funcs[styleIndex](obj);
}