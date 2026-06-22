#include "actions.h"
#include "ui.h"
#include "vars.h"
#include "SynthManager.h"

// Automatically switch to dashboard after 3000 ms
void action_switch_to_main(lv_event_t* e) {
  loadScreenWithDelay(SCREEN_ID_DASHBOARD, 3000);
}

void initialize_osc1_data(Oscillator osc) {
  lv_label_set_text_fmt(objects.dco_1__dco_number, "%i", osc.Number);
  lv_bar_set_value(objects.dco_1__detune, osc.Detune, LV_ANIM_ON);
  lv_bar_set_value(objects.dco_1__volume, osc.Volume, LV_ANIM_ON);
  switch (osc.Waveform) {
    case Waveform_SQUARE:
      lv_obj_add_flag(objects.dco_1__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_1__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(objects.dco_1__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_1__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
    case Waveform_TRIANGLE:
      lv_obj_remove_flag(objects.dco_1__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_1__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_1__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_1__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
    case Waveform_SINE:
      lv_obj_add_flag(objects.dco_1__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_1__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_1__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(objects.dco_1__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
    case Waveform_SAW:
      lv_obj_add_flag(objects.dco_1__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(objects.dco_1__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_1__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_1__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
  }
}

void initialize_osc2_data(Oscillator osc) {
  lv_label_set_text_fmt(objects.dco_2__dco_number, "%i", osc.Number);
  lv_bar_set_value(objects.dco_2__detune, osc.Detune, LV_ANIM_ON);
  lv_bar_set_value(objects.dco_2__volume, osc.Volume, LV_ANIM_ON);
  switch (osc.Waveform) {
    case Waveform_SQUARE:
      lv_obj_add_flag(objects.dco_2__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_2__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(objects.dco_2__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_2__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
    case Waveform_TRIANGLE:
      lv_obj_remove_flag(objects.dco_2__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_2__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_2__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_2__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
    case Waveform_SINE:
      lv_obj_add_flag(objects.dco_2__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_2__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_2__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(objects.dco_2__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
    case Waveform_SAW:
      lv_obj_add_flag(objects.dco_2__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(objects.dco_2__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_2__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_2__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
  }
}

void initialize_osc3_data(Oscillator osc) {
  lv_label_set_text_fmt(objects.dco_3__dco_number, "%i", osc.Number);
  lv_bar_set_value(objects.dco_3__detune, osc.Detune, LV_ANIM_ON);
  lv_bar_set_value(objects.dco_3__volume, osc.Volume, LV_ANIM_ON);
  switch (osc.Waveform) {
    case Waveform_SQUARE:
      lv_obj_add_flag(objects.dco_3__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_3__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(objects.dco_3__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_3__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
    case Waveform_TRIANGLE:
      lv_obj_remove_flag(objects.dco_3__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_3__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_3__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_3__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
    case Waveform_SINE:
      lv_obj_add_flag(objects.dco_3__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_3__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_3__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(objects.dco_3__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
    case Waveform_SAW:
      lv_obj_add_flag(objects.dco_3__waveform_triangle, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(objects.dco_3__waveform_saw, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_3__waveform_square, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.dco_3__waveform_sine, LV_OBJ_FLAG_HIDDEN);
      break;
  }
}

void initialize_envelope_data(Envelope env){
  lv_bar_set_value(objects.envelope__attack, env.Attack, LV_ANIM_ON);
  lv_bar_set_value(objects.envelope__decay, env.Decay, LV_ANIM_ON);
  lv_bar_set_value(objects.envelope__release, env.Release, LV_ANIM_ON);
  lv_bar_set_value(objects.envelope__sustain, env.Sustain, LV_ANIM_ON);
}

void action_save_settings(lv_event_t* e) {}
void action_exit_settings(lv_event_t* e) {}
void action_open_settings(lv_event_t* e) {}
void action_start_visualization(lv_event_t* e) {}
void action_set_waveform_graphic(lv_event_t* e) {
  initialize_osc1_data(synthManager.Osc1);
  initialize_osc2_data(synthManager.Osc2);
  initialize_osc3_data(synthManager.Osc3);
  initialize_envelope_data(synthManager.ADSR);
}