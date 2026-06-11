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

struct EncoderConfiguration {
	uint8_t encoderId;
	uint8_t pinA;
	uint8_t pinB;
	volatile uint8_t *pin;
	volatile uint8_t oldState;
	volatile int offset;
	volatile uint8_t *led_port;
	uint8_t led_saw;
	uint8_t led_square;
	uint8_t led_triangle;
	uint8_t led_sine;
};
typedef struct EncoderConfiguration encoderConfiguration;

void encoder_initialize(volatile encoderConfiguration* config, uint8_t encoderId, volatile uint8_t *pin, volatile uint8_t *ddr, volatile uint8_t *port, uint8_t phaseA, uint8_t phaseB);
int encoder_read_offset(volatile encoderConfiguration *encoder);
void encoder_tick(volatile encoderConfiguration *encoder);
void initialize_oscillator_type_leds(volatile encoderConfiguration* encoder, volatile uint8_t *ddr, volatile uint8_t *port, uint8_t led_saw, uint8_t led_square, uint8_t led_triangle, uint8_t led_sine);
void set_oscillator_type_led(encoderConfiguration encoder, int value);
#endif