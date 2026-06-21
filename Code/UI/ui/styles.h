#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: spinner_style
lv_style_t *get_style_spinner_style_MAIN_DEFAULT();
lv_style_t *get_style_spinner_style_INDICATOR_DEFAULT();
void add_style_spinner_style(lv_obj_t *obj);
void remove_style_spinner_style(lv_obj_t *obj);

// Style: checkbox_style
lv_style_t *get_style_checkbox_style_INDICATOR_CHECKED();
lv_style_t *get_style_checkbox_style_MAIN_DEFAULT();
void add_style_checkbox_style(lv_obj_t *obj);
void remove_style_checkbox_style(lv_obj_t *obj);

// Style: waveform_line_style
lv_style_t *get_style_waveform_line_style_MAIN_DEFAULT();
void add_style_waveform_line_style(lv_obj_t *obj);
void remove_style_waveform_line_style(lv_obj_t *obj);

// Style: needle_style
void add_style_needle_style(lv_obj_t *obj);
void remove_style_needle_style(lv_obj_t *obj);

// Style: header_label_style
lv_style_t *get_style_header_label_style_MAIN_DEFAULT();
void add_style_header_label_style(lv_obj_t *obj);
void remove_style_header_label_style(lv_obj_t *obj);

// Style: detune_scale_style
void add_style_detune_scale_style(lv_obj_t *obj);
void remove_style_detune_scale_style(lv_obj_t *obj);

// Style: button_style
lv_style_t *get_style_button_style_MAIN_DEFAULT();
void add_style_button_style(lv_obj_t *obj);
void remove_style_button_style(lv_obj_t *obj);

// Style: button_label_style
lv_style_t *get_style_button_label_style_MAIN_DEFAULT();
void add_style_button_label_style(lv_obj_t *obj);
void remove_style_button_label_style(lv_obj_t *obj);

// Style: bar_style
lv_style_t *get_style_bar_style_INDICATOR_DEFAULT();
lv_style_t *get_style_bar_style_MAIN_DEFAULT();
void add_style_bar_style(lv_obj_t *obj);
void remove_style_bar_style(lv_obj_t *obj);

// Style: default_label_style
lv_style_t *get_style_default_label_style_MAIN_DEFAULT();
void add_style_default_label_style(lv_obj_t *obj);
void remove_style_default_label_style(lv_obj_t *obj);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/