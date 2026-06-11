#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include<stdlib.h>

#define F_CPU 8000000UL
#include <util/delay.h>

#include "encoder.h"
#include "serial.h"

#define XTAL 8e6

volatile encoderConfiguration osc1_frequency_encoder;
volatile encoderConfiguration osc1_type_encoder;

void print_encoder_to_serial(struct EncoderConfiguration encoder){
	char buffer[10];
	serial_send_string("Encoder ", false);
	itoa(encoder.encoderId, buffer, 10);
	serial_send_string(buffer, false);
	serial_send_string(": {", false);
		serial_send_string("Offset:", false);
		itoa(encoder.offset, buffer, 10);
		serial_send_string(buffer, false);
		serial_send(',', false);
		serial_send_string("OldState:", false);
		itoa(encoder.oldState, buffer, 10);
		serial_send_string(buffer, false);
		serial_send(',', false);
		serial_send_string("PinA:", false);
		itoa(encoder.pinA, buffer, 2);
		serial_send_string(buffer, false);
		serial_send(',', false);
		serial_send_string("PinB:", false);
		itoa(encoder.pinB, buffer, 2);
		serial_send_string(buffer, false);
		
	serial_send('}', true);
}

ISR(TIMER0_COMP_vect) {
	encoder_tick(&osc1_frequency_encoder);
	encoder_tick(&osc1_type_encoder);
}
//
//ISR(SPI_STC_vect) { spi.Read(); }

void initialize_encoder_timer(void) { 
	TCCR0 = (1 << WGM01) | (1 << CS01) | (1 << CS00); // CTC, prescaler 64
	OCR0 = (uint8_t)(F_CPU / 64.0 * 1e-3 - 0.5);       // 1ms
	TIMSK |= 1 << OCIE0;
}

void setup() {
	serial_initialize();
	serial_send_string("Initializing Ports...", true);
	
	// OSC1 Frequency
	encoder_initialize(&osc1_frequency_encoder, 1, &PINC, &DDRC, &PORTC, PC2, PC3);
	// OSC1 Type
	encoder_initialize(&osc1_type_encoder, 2, &PINC, &DDRC, &PORTC, PC0, PC1);
	initialize_oscillator_type_leds(&osc1_type_encoder, &DDRA, &PORTA, PA4, PA5, PA6, PA7);
	
	serial_send_string("Starting timer...", true);
	initialize_encoder_timer();
	// spi.Initialize(false);
	DDRC = 0xF0;
}

int main(void) {
	setup();
	serial_send_string("Setup finished", true);
	sei();

	int32_t frequency = 0;
	int32_t oldFrequency = 0;
	int type = 0;
	int oldType = 0;
	char buffer[10];
	
	while (1) {
		frequency += encoder_read_offset(&osc1_frequency_encoder);
		type += encoder_read_offset(&osc1_type_encoder);
		
		if(frequency != oldFrequency){
			
			serial_send_string("Value for Frequency:", false);
			itoa(frequency, buffer, 10);
			serial_send_string(buffer, true);	
			
			uint8_t portB_dir = DDRC;
			serial_send_string("DDRC:", false);
			itoa(portB_dir, buffer, 2);
			serial_send_string(buffer, true);	
		}
		if(type != oldType) {
			serial_send_string("Value for OSC Type:", false);
			itoa(type, buffer, 10);
			serial_send_string(buffer, true);
			
			serial_send_string("Updating LED with type value:", false);
			itoa(type, buffer, 10);
			serial_send_string(buffer, true);
			set_oscillator_type_led(osc1_type_encoder, type);			
		}
		oldFrequency = frequency;
		oldType = type;		
	}
}
