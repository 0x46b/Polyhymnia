#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_switch_to_main(lv_event_t * e);
extern void action_save_settings(lv_event_t * e);
extern void action_exit_settings(lv_event_t * e);
extern void action_open_settings(lv_event_t * e);
extern void action_start_visualization(lv_event_t * e);
extern void action_set_waveform_graphic(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/