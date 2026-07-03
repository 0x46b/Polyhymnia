#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

#include "control_types.h"
#include "fader.h"
#include "oscillator_controller.h"
#include "serial.h"
#include "spi_commands.h"
#include "spi_handler.h"

#define ENCODER_TICK_FREQUENCY_HZ 72
#define XTAL 8e6

oscillator_controller oscillator_controllers[3];
envelope_controller adsr_controller;
filter_controller lowpass_controller;

ISR(TIMER0_COMP_vect) {
  for (int i = 0; i < 3; i++) {
    oscillator_tick(&oscillator_controllers[i]);
  }
}

ISR(SPI_STC_vect) { handle_received_byte(SPDR); }

void initialize_encoder_timer(void) { // nur Timer 0 initialisieren
  TCCR0 = (1 << WGM01) | (1 << CS02) | (1 << CS00); // CTC, prescaler 1024
  OCR0 = (uint8_t)(F_CPU / 1024.0 * ENCODER_TICK_FREQUENCY_HZ) - 1;
}

void start_encoder_timer(void) { TIMSK |= 1 << OCIE0; }

void setup(void) {
  serial_initialize();

  serial_send_string("Initializing OSC 1 controller...", false);
  // OSC1
  oscillator_controllers[0].detuneState.config.port = &PORTC;
  oscillator_controllers[0].detuneState.config.pinA = PC2;
  oscillator_controllers[0].detuneState.config.pinB = PC3;

  oscillator_controllers[0].typeState.config.port = &PORTC;
  oscillator_controllers[0].typeState.config.pinA = PC0;
  oscillator_controllers[0].typeState.config.pinB = PC1;

  initialize_oscillator_controller(&oscillator_controllers[0], 1);

  serial_send_string("[OK]", true);
  serial_send_string("Initializing OSC 3 controller...", false);
  // OSC2
  oscillator_controllers[1].detuneState.config.port = &PORTC;
  oscillator_controllers[1].detuneState.config.pinA = PC6;
  oscillator_controllers[1].detuneState.config.pinB = PC7;

  oscillator_controllers[1].typeState.config.port = &PORTC;
  oscillator_controllers[1].typeState.config.pinA = PC4;
  oscillator_controllers[1].typeState.config.pinB = PC5;

  initialize_oscillator_controller(&oscillator_controllers[1], 2);
  serial_send_string("[OK]", true);
  serial_send_string("Initializing OSC 3 controller...", false);
  // OSC3
  oscillator_controllers[2].detuneState.config.port = &PORTD;
  oscillator_controllers[2].detuneState.config.pinA = PD4;
  oscillator_controllers[2].detuneState.config.pinB = PD5;

  oscillator_controllers[2].typeState.config.port = &PORTD;
  oscillator_controllers[2].typeState.config.pinA = PD2;
  oscillator_controllers[2].typeState.config.pinB = PD3;

  initialize_oscillator_controller(&oscillator_controllers[2], 3);
  serial_send_string("[OK]", true);
  serial_send_string("Initializing Envelope controller...", false);
  // ADSR
  envelope_initialize(&adsr_controller, 0, 1, 2, 3);
  serial_send_string("[OK]", true);
  serial_send_string("Initializing Filter controller...", false);
  // LowPass
  filter_initialize(&lowpass_controller, 4, 5);
  serial_send_string("[OK]", true);
  // SPI
  /* serial_send_string("Initializing SPI connection...", false); */
  /* spi_initialize(); */
  /* serial_send_string("[OK]", true); */

  // Encoder timer interrupt
  serial_send_string("Initializing encoder polling...", false);
  initialize_encoder_timer();
  serial_send_string("[OK]", true);
}

void put_envelope_data_into_transfer_buffer(void) {
  update_envelope_state(&adsr_controller);
  write_to_transfer_buffer(adsr_controller.state.Attack);
  write_to_transfer_buffer(adsr_controller.state.Decay);
  write_to_transfer_buffer(adsr_controller.state.Sustain);
  write_to_transfer_buffer(adsr_controller.state.Release);
}

void put_filter_data_into_transfer_buffer(void) {
  update_filter_state(&lowpass_controller);
  write_to_transfer_buffer(lowpass_controller.state.Cutoff);
  write_to_transfer_buffer(lowpass_controller.state.Resonance);
}

void put_lfo_data_into_transfer_buffer(void) {
  // assert(!"The method or operation is not implemented.");
}

void put_osc_data_into_transfer_buffer(uint8_t id) {
  write_to_transfer_buffer(oscillator_controllers[id].state.Id);
  write_to_transfer_buffer(oscillator_controllers[id].state.DetuneOffset);
  write_to_transfer_buffer(oscillator_controllers[id].state.Type);
}

void handle_spi_commands(void) {
  uint8_t payload;

  if (is_command_ready()) {
    spi_command cmd = get_command();
    switch (cmd) {
    case ReadEnvelope:
      put_envelope_data_into_transfer_buffer();
      set_transfer_ready();
      break;
    case ReadFilter:
      put_filter_data_into_transfer_buffer();
      set_transfer_ready();
      break;
    case ReadLFO:
      put_lfo_data_into_transfer_buffer();
      set_transfer_ready();
      break;
    case ReadOSC:
      payload = get_payload();
      put_osc_data_into_transfer_buffer(payload);
      set_transfer_ready();
      break;
    /* TODO: Make ID configurable instead of using the first every time*/
    case SetWaveformSaw:
      payload = get_payload();
      set_waveform_for_osc(&oscillator_controllers[0], SAW, payload);
      set_ready_for_next_cmd();
      break;
    case SetWaveformSine:
      payload = get_payload();
      set_waveform_for_osc(&oscillator_controllers[0], SINE, payload);
      set_ready_for_next_cmd();
      break;
    case SetWaveformSquare:
      payload = get_payload();
      set_waveform_for_osc(&oscillator_controllers[0], SQUARE, payload);
      set_ready_for_next_cmd();
      break;
    case SetWaveformTriangle:
      payload = get_payload();
      set_waveform_for_osc(&oscillator_controllers[0], TRIANGLE, payload);
      set_ready_for_next_cmd();
      break;
    case SetEnvelope:
      break;
    case SetLFO:
      break;
    case SetFilter:
      break;
    default:
      write_to_transfer_buffer(MODULE_UNKNOWN_COMMAND);
      set_transfer_ready();
      break;
    }
  }
}

int main(void) {
  setup();
  serial_send_string("Enabling encoder polling...", false);
  // start_encoder_timer();
  serial_send_string("[OK]", true);
  serial_send_string("Enabling global-interrupts...", false);
  sei();
  serial_send_string("[OK]", true);

  while (1) {
    handle_spi_commands();
    for (int i = 0; i < 3; i++) {
      oscillator_tick(&oscillator_controllers[i]);
    }
  }
}
