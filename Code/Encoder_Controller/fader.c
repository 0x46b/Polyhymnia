#include "fader.h"

void envelope_initialize(envelope_controller *controller, uint8_t channelAttack,
                         uint8_t channelDecay, uint8_t channelSustain,
                         uint8_t channelRelease) {
  controller->state.Attack = 0;
  controller->state.Decay = 0;
  controller->state.Sustain = 0;
  controller->state.Release = 0;

  controller->config_attack.channel = channelAttack;
  controller->config_attack.factor = 1;
  controller->config_decay.channel = channelDecay;
  controller->config_decay.factor = 1;
  controller->config_release.channel = channelRelease;
  controller->config_release.factor = 1;
  controller->config_sustain.channel = channelSustain;
  controller->config_sustain.factor = 1;
}

void filter_initialize(filter_controller *controller, uint8_t channelCutoff,
                       uint8_t channelResonance) {
  controller->config_cutoff.channel = channelCutoff;
  ;
  controller->config_cutoff.factor = 1;

  controller->config_resonance.channel = channelResonance;
  controller->config_resonance.factor = 1;

  controller->state.Cutoff = 0;
  controller->state.Resonance = 0;
}

uint16_t read_fader_value(potentiometer_config config) {
  uint16_t faderValue = ADC_read(config.channel);
  return config.factor * faderValue;
}

void update_envelope_state(envelope_controller *controller) {
  controller->state.Attack = read_fader_value(controller->config_attack);
  controller->state.Decay = read_fader_value(controller->config_decay);
  controller->state.Sustain = read_fader_value(controller->config_sustain);
  controller->state.Release = read_fader_value(controller->config_release);
}

void update_filter_state(filter_controller *controller) {
  controller->state.Cutoff = read_fader_value(controller->config_cutoff);
  controller->state.Resonance = read_fader_value(controller->config_resonance);
}

// TODO: Set correct values
void ADC_init(void) {
  PORTB |= 0xF0;
  ADCSRA |= ADEN;
  ADCSRA |= ADPS2;
  ADCSRA |= ADPS1;
}

uint16_t ADC_read(uint8_t channel) {
  ADMUX = channel;
  ADCSRA |= ADSC;
  while (ADCSRA & ADSC)
    ;

  return ADCW;
}
