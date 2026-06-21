#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

typedef enum {

} Waveform;

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_VERSION = 0,
    FLOW_GLOBAL_VARIABLE_DCO_1_WAVEFORM = 1
};

// Native global variables

extern const char *get_var_version();
extern void set_var_version(const char *value);
extern Waveform get_var_dco_1_waveform();
extern void set_var_dco_1_waveform(Waveform value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/