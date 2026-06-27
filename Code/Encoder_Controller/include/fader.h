#ifndef FADER_H
#define FADER_H

#include "control_types.h"
#include <avr/io.h>
#include <stdint.h>

typedef struct {
  uint8_t channel;
  uint8_t factor;
} potentiometer_config;

typedef struct {
  EnvelopeState state;
  potentiometer_config config_attack;
  potentiometer_config config_decay;
  potentiometer_config config_sustain;
  potentiometer_config config_release;
} envelope_controller;

typedef struct {
  volatile potentiometer_config config_cutoff;
  volatile potentiometer_config config_resonance;
  FilterState state;
} filter_controller;

void envelope_initialize(envelope_controller *controller, uint8_t channelAttack,
                         uint8_t channelDecay, uint8_t channelSustain,
                         uint8_t channelRelease);
void update_envelope_state(envelope_controller *controller);
void filter_initialize(filter_controller *controller, uint8_t channelCutoff,
                       uint8_t channelResonance);
void update_filter_state(filter_controller *controller);
void ADC_init(void);
uint16_t ADC_read(uint8_t channel);
#endif
