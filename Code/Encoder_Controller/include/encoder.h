#ifndef ENCODER_H
#define ENCODER_H
#include <inttypes.h>

static const int8_t STATETABLE[] =
// Gray-table for all possible combinations of A and B
// 1 = CW-turn
// -1 = CCW-turn
// 00 01 11 10
{0,  1,  -1, 0,  // 00
-1, 0,  0,  1,  // 01
	1,  0,  0,  -1, // 11
0,  -1, 1,  0}; // 10

typedef struct {
	uint8_t pinSaw;
	uint8_t pinSquare;
	uint8_t pinSine;
	uint8_t pinTriangle;
	volatile uint8_t *pin;
	} oscillator_type_LED_config; 

typedef struct{
	uint8_t pinA;
	uint8_t pinB;
	oscillator_type_LED_config leds;
	volatile uint8_t *pin;
	volatile uint8_t oldState;
	volatile int offset;
}  encoder_config;

typedef struct {
	OscillatorState state;
	volatile encoder_config encoderDetune;
	volatile encoder_config encoderType;
	oscillator_type_LED_config ledConfig;
} oscillator_controller;

void encoder_initialize(encoder_config *config, volatile uint8_t *pin, volatile uint8_t *ddr, volatile uint8_t *port, uint8_t phaseA, uint8_t phaseB);
int encoder_read_offset(volatile encoder_config *encoder);
void encoder_tick(volatile encoder_config *encoder);
void oscillator_tick(volatile oscillator_controller *controller);
#endif