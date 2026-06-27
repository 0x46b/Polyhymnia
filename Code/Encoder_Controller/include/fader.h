#ifndef FADER_H
#define FADER_H

#include <avr/io.h>

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

void initialize_envelope(envelope_controller *controller);
void update_envelope_state(envelope_controller *controller);
void initialize_filter(filter_controller *controller);
void ADC_init(void);
uint16_t ADC_read(uint8_t channel);
#endif