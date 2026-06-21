#include "vars.h"
#include "version.h"
#include "SynthManager.h"

const char *get_var_version() {
  return VERSION;
}
// Not allowed
void set_var_version(const char *value) {}

const char *get_var_dco_number() {
  return "1";
}

void set_var_dco_number(const char *value) {}
Waveform get_var_dco_1_waveform() {
  return Waveform_SAW;
}
void set_var_dco_1_waveform(Waveform value) {}
int32_t get_var_dco_1_detune() {
  return 0;
}
void set_var_dco_1_detune(int32_t value) {}
int32_t get_var_dco_1_volume() {
  return 127 / 3;
}
void set_var_dco_1_volume(int32_t value) {}
int32_t get_var_envelop_attack() {
  return synthManager.ADSR.Attack;
}
void set_var_envelop_attack(int32_t value) {
  synthManager.ADSR.Attack = value;
}
int32_t get_var_envelope_decay() {
  return synthManager.ADSR.Decay;
}
void set_var_envelope_decay(int32_t value) {
  synthManager.ADSR.Decay = value;
}

int32_t get_var_envelope_sustain() {
  return synthManager.ADSR.Sustain;
}
void set_var_envelope_sustain(int32_t value) {
  synthManager.ADSR.Sustain = value;
}
int32_t get_var_envelope_release() {
  return synthManager.ADSR.Release;
}
void set_var_envelope_release(int32_t value) {
  synthManager.ADSR.Release = value;
}

BootscreenPicture get_var_bootscreen_type() {
  return BootscreenPicture_Distorted;
}
void set_var_bootscreen_type(BootscreenPicture value) {}
int32_t get_var_midichannel() {
  return 0;
}
void set_var_midichannel(int32_t value) {}
bool get_var_show_bootscreen() {
  return true;
}
void set_var_show_bootscreen(bool value) {}