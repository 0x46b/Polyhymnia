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
};

struct EncoderConfiguration encoder_initialize(uint8_t encoderId, volatile uint8_t *pin, volatile uint8_t *ddr, volatile uint8_t *port, uint8_t phaseA, uint8_t phaseB);
int encoder_read_offset(volatile struct EncoderConfiguration *encoder);
void encoder_tick(volatile struct EncoderConfiguration *encoder);

#endif