#include "encoder.h"


struct EncoderConfiguration encoder_initialize(uint8_t encoderId, volatile uint8_t *pin, volatile uint8_t *port, uint8_t phaseA, uint8_t phaseB) {
	struct EncoderConfiguration config;
	config.encoderId = encoderId;
	config.pinA = (1 << phaseA);
	config.pinB = (1 << phaseB);
	config.pin = pin;
	config.offset = 0;
	config.oldState = 0;
	
	*port |= config.pinA | config.pinB;
	return config;
}

int encoder_read_offset(volatile struct EncoderConfiguration *encoder) {
	int8_t currentOffsetBuff = encoder->offset;
	encoder->offset = 0;

	return currentOffsetBuff;
}

void encoder_tick(volatile struct EncoderConfiguration *encoder) {
	// Shift old-state 2 to the right and trim first byte
	// e.g. old-state = 00001010 => <<2 => 00101000 => &0x0F => 00001000
	encoder->oldState = (encoder->oldState << 2) & 0x0F;
	// Check, if A is HIGH, if so set second last bit to 1
	if (*encoder->pin & encoder->pinA) {
		encoder->oldState |= 2;
	}
	// Check, if B is HIGH, if so set last bit to 1
	if (*encoder->pin & encoder->pinB) {
		encoder->oldState |= 1;
	}

	// Get value from our gray-table
	int8_t movement = STATETABLE[encoder->oldState];
	if (movement == 1 || movement == -1) {
		encoder->offset += movement;
	}
}
