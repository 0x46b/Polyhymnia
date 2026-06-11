#include "encoder.h"
#include <util/delay.h>

void encoder_initialize(volatile encoderConfiguration* config, uint8_t encoderId, volatile uint8_t *pin, volatile uint8_t *ddr, volatile uint8_t *port, uint8_t phaseA, uint8_t phaseB) {
	config->encoderId = encoderId;
	config->pinA = (1 << phaseA);
	config->pinB = (1 << phaseB);
	config->pin = pin;
	config->offset = 0;
	config->oldState = 0;
	
	*ddr &= ~config->pinA | ~config->pinB;
	*port |= config->pinA | config->pinB;
}

void initialize_oscillator_type_leds(volatile encoderConfiguration* encoder, volatile uint8_t *ddr, volatile uint8_t *port, uint8_t led_saw, uint8_t led_square, uint8_t led_triangle, uint8_t led_sine){
	encoder->led_port = port;
	encoder->led_saw = (1 << led_saw);
	encoder->led_sine = (1 << led_sine);
	encoder->led_square = (1 << led_square);
	encoder->led_triangle = (1 << led_triangle);
	encoder->offset = 10;
	
	*ddr |= led_saw | led_sine | led_square | led_triangle;
	*port &= ~led_saw | ~led_sine | ~led_square | ~led_triangle;
}

int encoder_read_offset(volatile encoderConfiguration *encoder) {
	int8_t currentOffsetBuff = encoder->offset;
	encoder->offset = 0;

	return currentOffsetBuff;
}

void encoder_tick(volatile encoderConfiguration *encoder) {
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

void set_oscillator_type_led(encoderConfiguration encoder, int typeValue){
	
	if(typeValue > 0 && typeValue <= 10){
		*encoder.led_port |= encoder.led_saw; 
		*encoder.led_port &= ~encoder.led_square; 
		*encoder.led_port &= ~encoder.led_triangle;
		*encoder.led_port &= ~encoder.led_sine;
	}
	if(typeValue > 10 && typeValue <= 20){
		*encoder.led_port &= ~encoder.led_saw;
		*encoder.led_port |=  encoder.led_square;
		*encoder.led_port &= ~encoder.led_triangle;
		*encoder.led_port &= ~encoder.led_sine;
	}
	if(typeValue >= 20 && typeValue < 30){
		*encoder.led_port &= ~encoder.led_saw;
		*encoder.led_port &= ~encoder.led_square;
		*encoder.led_port |=  encoder.led_triangle;
		*encoder.led_port &= ~encoder.led_sine;
	}
	if(typeValue > 30){
		*encoder.led_port &= ~encoder.led_saw;
		*encoder.led_port &= ~encoder.led_square; 
		*encoder.led_port &= ~encoder.led_triangle;
		*encoder.led_port |=  encoder.led_sine;
	}	
}

void test_oscillator_type_leds(encoderConfiguration encoder){
	*encoder.led_port |= encoder.led_saw;
	_delay_ms(1000);
	*encoder.led_port |= encoder.led_square;
	_delay_ms(1000);
	*encoder.led_port |= encoder.led_triangle;
	_delay_ms(1000);
	*encoder.led_port |= encoder.led_sine;
	
	_delay_ms(1000);
	*encoder.led_port &= ~encoder.led_saw;
	_delay_ms(1000);
	*encoder.led_port &= ~encoder.led_square;
	_delay_ms(1000);
	*encoder.led_port &= ~encoder.led_triangle;
	_delay_ms(1000);
	*encoder.led_port &= ~encoder.led_sine;
	
}