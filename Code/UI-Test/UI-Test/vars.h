#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

typedef enum {
    Waveform_SQUARE = 0,
    Waveform_TRIANGLE = 1,
    Waveform_SINE = 2,
    Waveform_SAW = 3
} Waveform;

typedef enum {
    BootscreenPicture_Distorted = 0,
    BootscreenPicture_Normal = 1
} BootscreenPicture;

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_VERSION = 0,
    FLOW_GLOBAL_VARIABLE_DCO_NUMBER = 1,
    FLOW_GLOBAL_VARIABLE_DCO_1_WAVEFORM = 2,
    FLOW_GLOBAL_VARIABLE_DCO_1_DETUNE = 3,
    FLOW_GLOBAL_VARIABLE_DCO_1_VOLUME = 4,
    FLOW_GLOBAL_VARIABLE_ENVELOP_ATTACK = 5,
    FLOW_GLOBAL_VARIABLE_ENVELOPE_DECAY = 6,
    FLOW_GLOBAL_VARIABLE_ENVELOPE_SUSTAIN = 7,
    FLOW_GLOBAL_VARIABLE_ENVELOPE_RELEASE = 8,
    FLOW_GLOBAL_VARIABLE_BOOTSCREEN_TYPE = 9,
    FLOW_GLOBAL_VARIABLE_MIDICHANNEL = 10,
    FLOW_GLOBAL_VARIABLE_SHOW_BOOTSCREEN = 11
};

// Native global variables

extern const char *get_var_version();
extern void set_var_version(const char *value);
extern const char *get_var_dco_number();
extern void set_var_dco_number(int32_t value);
extern Waveform get_var_dco_1_waveform();
extern void set_var_dco_1_waveform(Waveform value);
extern int32_t get_var_dco_1_detune();
extern void set_var_dco_1_detune(int32_t value);
extern int32_t get_var_dco_1_volume();
extern void set_var_dco_1_volume(int32_t value);
extern int32_t get_var_envelop_attack();
extern void set_var_envelop_attack(int32_t value);
extern int32_t get_var_envelope_decay();
extern void set_var_envelope_decay(int32_t value);
extern int32_t get_var_envelope_sustain();
extern void set_var_envelope_sustain(int32_t value);
extern int32_t get_var_envelope_release();
extern void set_var_envelope_release(int32_t value);
extern BootscreenPicture get_var_bootscreen_type();
extern void set_var_bootscreen_type(BootscreenPicture value);
extern int32_t get_var_midichannel();
extern void set_var_midichannel(int32_t value);
extern bool get_var_show_bootscreen();
extern void set_var_show_bootscreen(bool value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/