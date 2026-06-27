#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include<stdlib.h>

#define F_CPU 8000000UL
#include <util/delay.h>

#include "encoder.h"
#include "serial.h"
#include "spi_handler.h"
#include "control_types.h"
#include "ringbuffer.h"
#include "fader.h"

#define XTAL 8e6

oscillator_controller oscillator_controllers[3];
envelope_controller adsr_controller;
filter_controller lowpass_controller;

void print_encoder_to_serial(encoder_config encoder){
	char buffer[10];
	serial_send_string("Encoder ", false);
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
	for (int i=0; i < 3; i++) {
		oscillator_tick(&oscillator_controllers[i]);
	}
}

ISR(SPI_STC_vect)
{
	handle_received_byte(SPDR);
}

void initialize_encoder_timer(void) { // nur Timer 0 initialisieren
	TCCR0 = (1 << WGM01) | (1 << CS01) | (1 << CS00); // CTC, prescaler 64
	OCR0 = (uint8_t)(F_CPU / 64.0 * 1e-3 - 0.5);       // 1ms
	TIMSK |= 1 << OCIE0;
}

void leds_initialize(oscillator_type_LED_config* ledConfig)
{
	assert(!"The method or operation is not implemented.");
}

void initialize_oscillator_controller(oscillator_controller *oscillator, uint8_t id) {
	oscillator->state.Id = id;
	oscillator->state.DetuneOffset = 0;
	oscillator->state.Type = SAW;
}

void setup() {
	serial_initialize();
	serial_send_string("Initializing Ports...", true);
	// OSC1
	initialize_oscillator_controller(&oscillator_controllers[0]);
	// Type encoder
	encoder_initialize(&oscillator_controllers[0].encoderType, &PINC, &DDRC, &PORTC, PC0, PC1);
	// Detune encoder
	encoder_initialize(&oscillator_controllers[0].encoderDetune, &PINC, &DDRC, &PORTC, PC2, PC3);
	leds_initialize(&oscillator_controllers[0].ledConfig);
	
	// OSC2
	initialize_oscillator_controller(&oscillator_controllers[1]);
	// OSC2 Type
	encoder_initialize(&oscillator_controllers[1].encoderType, &PINC, &DDRC, &PORTC, PC4, PC5);
	// OSC2 Detune
	encoder_initialize(&oscillator_controllers[1].encoderDetune, &PINC, &DDRC, &PORTC, PC6, PC7);
	leds_initialize(&oscillator_controllers[1].ledConfig);
	
	// OSC3
	initialize_oscillator_controller(&oscillator_controllers[2]);	
	// OSC3 Type (PD0 + PD1 are used for debugging output via serial)
	encoder_initialize(&oscillator_controllers[2].encoderType, &PIND, &DDRD, &PORTD,  PD2, PD3);
	// OSC3 Detune
	encoder_initialize(&oscillator_controllers[2].encoderType, &PIND, &DDRD, &PORTD, PD4, PD5);
	leds_initialize(&oscillator_controllers[2].ledConfig);
	
	// ADSR
	envelope_initialize(&adsr_controller, 0, 1, 2, 3);
	
	//LowPass
	filter_initialize(&lowpass_controller, 4, 5);
	
	serial_send_string("Starting timer...", true);
	initialize_encoder_timer();
	initialize_spi();
}

void put_envelope_data_into_transfer_buffer()
{
	update_envelope_state(&adsr_controller);
	buffer_write(&_transferBuffer, adsr_controller.state.Attack);
	buffer_write(&_transferBuffer, adsr_controller.state.Decay);
	buffer_write(&_transferBuffer, adsr_controller.state.Sustain);
	buffer_write(&_transferBuffer, adsr_controller.state.Release);
	_transfer_length_in_bytes = ReadEnvelopeLen;
}

void put_filter_data_into_transfer_buffer()
{
	update_filter_state(&lowpass_controller);
	buffer_write(&_transferBuffer, lowpass_controller.state.Cutoff);
	buffer_write(&_transferBuffer, lowpass_controller.state.Resonance);
	_transfer_length_in_bytes = ReadFilterLen;
}

void put_lfo_data_into_transfer_buffer()
{
	assert(!"The method or operation is not implemented.");
}

void put_osc_data_into_transfer_buffer(uint8_t id)
{
	buffer_write(&_transferBuffer, oscillator_controllers[id].id);
	buffer_write(&_transferBuffer, oscillator_controllers[id].state.DetuneOffset);	
	buffer_write(&_transferBuffer, oscillator_controllers[id].state.Type);
	_transfer_length_in_bytes = ReadOSCLen;
}

void set_waveform_for_osc(OscillatorType type, uint8_t id)
{
	oscillator_controller *controller = &oscillator_controllers[id];
	switch(type){
		case SAW:
			controller->ledConfig.pin |= (1u << controller->ledConfig.pinSaw);
			controller->ledConfig.pin &= ~(1u << controller->ledConfig.pinSine) 
			| ~(1u << controller->ledConfig.pinTriangle)
			| ~(1u << controller->ledConfig.pinSquare);
			break;		
		case TRIANGLE:
			controller->ledConfig.pin |= (1u << controller->ledConfig.pinTriangle);
			controller->ledConfig.pin &= ~(1u << controller->ledConfig.pinSine)
			| ~(1u << controller->ledConfig.pinSaw)
			| ~(1u << controller->ledConfig.pinSquare);
			break;
		case SINE:
			controller->ledConfig.pin |= (1u << controller->ledConfig.pinSine);
			controller->ledConfig.pin &= ~(1u << controller->ledConfig.pinSaw)
			| ~(1u << controller->ledConfig.pinTriangle)
			| ~(1u << controller->ledConfig.pinSquare);
			break;
		case SQUARE:
			controller->ledConfig.pin |= (1u << controller->ledConfig.pinSquare);
			controller->ledConfig.pin &= ~(1u << controller->ledConfig.pinSine)
			| ~(1u << controller->ledConfig.pinTriangle)
			| ~(1u << controller->ledConfig.pinSaw);
			break;
	}
	controller->state.Type = type;
}

void handle_spi_commands(){
	if(_spi_state == CMD_EXEC){
		switch(_lastCommand.command){
			case ReadEnvelope:
				put_envelope_data_into_transfer_buffer();
				_spi_state = TRANSFER_READY;
				break;
			case ReadFilter:
				put_filter_data_into_transfer_buffer();
				_spi_state = TRANSFER_READY;
				break;
			case ReadLFO:
				put_lfo_data_into_transfer_buffer();
				_spi_state = TRANSFER_READY;
				break;
			case ReadOSC:
				put_osc_data_into_transfer_buffer(_lastCommand.payload);
				_spi_state = TRANSFER_READY;
				break;
			case SetWaveformSaw:
				set_waveform_for_osc(SAW, _lastCommand.payload);
				_spi_state = CMD_READ;
				break;
			case SetWaveformSine:
				set_waveform_for_osc(SINE, _lastCommand.payload);
				_spi_state = CMD_READ;
				break;
			case SetWaveformSquare:
				set_waveform_for_osc(SQUARE, _lastCommand.payload);
				_spi_state = CMD_READ;
				break;
			case SetWaveformTriangle:
				set_waveform_for_osc(TRIANGLE, _lastCommand.payload);
				_spi_state = CMD_READ;
				break;
			default:
				_spi_state = UNKNOWN_COMMAND;
				break;
				case SetEnvelope:
				break;
				case SetLFO:
				break;
				case SetFilter:
				break;
								
					
		}
	}
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
