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

volatile struct EncoderConfiguration encoders[2];

void print_encoder_to_serial(struct EncoderConfiguration encoder){
	char buffer[10];
	serial_send_string("Encoder ", false);
	itoa(encoder.encoderId, buffer, 10);
	serial_send_string(buffer, false);
	serial_send_string(": {", false);
		itoa(encoder.offset, buffer, 10);
		serial_send_string(buffer, false);
		serial_send(',', false);
		itoa(encoder.oldState, buffer, 10);
		serial_send_string(buffer, false);
		serial_send(',', false);
		itoa(encoder.pinA, buffer, 2);
		serial_send_string(buffer, false);
		serial_send(',', false);
		itoa(encoder.pinB, buffer, 2);
		serial_send_string(buffer, false);
		
	serial_send('}', true);
}

ISR(TIMER0_COMP_vect) {
	for (int i=0; i < 8; i++) {
		encoder_tick(&encoders[i]);
	}
}
//
//ISR(SPI_STC_vect) { spi.Read(); }

void initialize_encoder_timer(void) { // nur Timer 0 initialisieren
	TCCR0 = (1 << WGM01) | (1 << CS01) | (1 << CS00); // CTC, prescaler 64
	OCR0 = (uint8_t)(F_CPU / 64.0 * 1e-3 - 0.5);       // 1ms
	TIMSK |= 1 << OCIE0;
}

void setup() {
	serial_initialize();
	serial_send_string("Initializing Ports...", true);
	// Filter Cutoff
	encoders[0] = encoder_initialize(1, &PINA, &DDRA, &PORTA, PA0, PA1);
	// Filter Resonance
	encoders[1] = encoder_initialize(2, &PINA, &DDRA, &PORTA, PA2, PA3);
	
	// OSC1 Type
	encoders[2] = encoder_initialize(3, &PINC, &DDRC, &PORTC, PC0, PC1);
	// OSC1 Detune
	encoders[3] = encoder_initialize(4, &PINC, &DDRC, &PORTC, PC2, PC3);
	
	// OSC2 Type
	encoders[4] = encoder_initialize(5, &PINC, &DDRC, &PORTC, PC4, PC5);
	// OSC2 Detune
	encoders[5] = encoder_initialize(6, &PINC, &DDRC, &PORTC, PC6, PC7);

	 // OSC3 Type (PD0 + PD1 are used for debugging output via serial)
	 encoders[6] = encoder_initialize(7, &PIND, &DDRD, &PORTD,  PD2, PD3);
	 // OSC3 Detune
	 encoders[7] = encoder_initialize(8, &PIND, &DDRD, &PORTD, PD4, PD5);

	serial_send_string("Starting timer...", true);
	initialize_encoder_timer();
	// spi.Initialize(false);
}

int main(void) {
	setup();
	serial_send_string("Setup finished", true);
	sei();

	int32_t val1 = 0;
	int32_t oldVal1 = 0;
	int32_t val2 = 0;
	int32_t oldval2 = 0;
	char buffer[10];
	
	while (1) {
		val1 += encoder_read_offset(&encoders[0]);
		val2 += encoder_read_offset(&encoders[2]);
		
		if(val1 != oldVal1){
			serial_send_string("Value for Encoder 1:", false);
			itoa(val1, buffer, 10);
			serial_send_string(buffer, true);
		}
		if(val2 != oldval2) {
			serial_send_string("Value for Encoder 3:", false);
			itoa(val2, buffer, 10);
			serial_send_string(buffer, true);
		}
		oldVal1 = val1;
		oldval2 = val2;
	}
}
