#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_BOOTUP = 1,
    SCREEN_ID_DASHBOARD = 2,
    SCREEN_ID_PATCHES = 3,
    SCREEN_ID_VISUALIZATION = 4,
    SCREEN_ID_SETTINGS = 5,
    SCREEN_ID_GIF_VISUALIZATION = 6,
    SCREEN_ID_FFT_VISUALIZATION = 7,
    SCREEN_ID_PATCH_EDIT = 8,
    _SCREEN_ID_LAST = 8
};

typedef struct _objects_t {
    lv_obj_t *bootup;
    lv_obj_t *dashboard;
    lv_obj_t *patches;
    lv_obj_t *visualization;
    lv_obj_t *settings;
    lv_obj_t *gif_visualization;
    lv_obj_t *fft_visualization;
    lv_obj_t *patch_edit;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj2__dco_number;
    lv_obj_t *obj2__waveform_sine;
    lv_obj_t *obj2__waveform_saw;
    lv_obj_t *obj2__waveform_triangle;
    lv_obj_t *obj2__waveform_square;
    lv_obj_t *obj2__obj0;
    lv_obj_t *obj2__obj1;
    lv_obj_t *obj3;
    lv_obj_t *obj3__dco_number;
    lv_obj_t *obj3__waveform_sine;
    lv_obj_t *obj3__waveform_saw;
    lv_obj_t *obj3__waveform_triangle;
    lv_obj_t *obj3__waveform_square;
    lv_obj_t *obj3__obj0;
    lv_obj_t *obj3__obj1;
    lv_obj_t *obj4;
    lv_obj_t *obj4__dco_number;
    lv_obj_t *obj4__waveform_sine;
    lv_obj_t *obj4__waveform_saw;
    lv_obj_t *obj4__waveform_triangle;
    lv_obj_t *obj4__waveform_square;
    lv_obj_t *obj4__obj0;
    lv_obj_t *obj4__obj1;
    lv_obj_t *obj5;
    lv_obj_t *obj5__obj2;
    lv_obj_t *obj5__obj3;
    lv_obj_t *obj5__obj4;
    lv_obj_t *obj5__obj5;
    lv_obj_t *chck_show_bootscreen;
    lv_obj_t *drp_bootscreen_mode;
    lv_obj_t *drp_midichannel;
    lv_obj_t *save_button;
    lv_obj_t *abort_button;
    lv_obj_t *patch_name;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
} objects_t;

extern objects_t objects;

void create_screen_bootup();
void tick_screen_bootup();

void create_screen_dashboard();
void tick_screen_dashboard();

void create_screen_patches();
void tick_screen_patches();

void create_screen_visualization();
void tick_screen_visualization();

void create_screen_settings();
void tick_screen_settings();

void create_screen_gif_visualization();
void tick_screen_gif_visualization();

void create_screen_fft_visualization();
void tick_screen_fft_visualization();

void create_screen_patch_edit();
void tick_screen_patch_edit();

void create_user_widget_oscillator(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_oscillator(int startWidgetIndex);

void create_user_widget_adsr(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_adsr(int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

// Groups

typedef struct _groups_t {
    lv_group_t *MainGroup;
} groups_t;

extern groups_t groups;

void ui_create_groups();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/