#ifndef ENCODER_H
#define ENCODER_H

#include "control_types.h"
#include "led_driver.h"
#include <assert.h>
#include <stdint.h>
/* Gray-table for all possible combinations of A and B to determine movement at
 * the encoder
 * 1 = CW-turn -1 = CCW-turn
 */
static const int8_t STATETABLE[] =
    // 00 01 11 10
    {0,  1,  -1, 0,  // 00
     -1, 0,  0,  1,  // 01
     1,  0,  0,  -1, // 11
     0,  -1, 1,  0}; // 10

/* Port and pin configuration */
typedef struct {
  uint8_t pinA;
  uint8_t pinB;
  volatile uint8_t *port;
} encoder_config;

/* State of the encoder
 * config: configuration to read from the correct pins
 * oldState: saved state from the last read
 * offset: number indicating, how "far" the encoder got turned since the last
 *         read (positive => clockwise, negative => counter-clockwise
 */
typedef struct {
  encoder_config config;
  volatile uint8_t oldState;
  volatile int offset;
} encoder_state;

/* Bundled data for a whole oscillator-control-unit
 * state: holding the current values of detune and type
 * detuneState: state-data for the detune-encoder
 * typeState: state-data for the type-encoder
 * led_state: state-data for controlling the "type"-leds on the unit
 */
typedef struct {
  OscillatorState state;
  volatile encoder_state detuneState;
  volatile encoder_state typeState;
  led_controller_state led_state;
} oscillator_controller;

/* Initialize the encoder. Sets the corresponding data direction registers and
 * pullup-resistors */
void encoder_initialize(volatile encoder_config *config);

/* Returns the offset since the last read */
int encoder_read_offset(volatile encoder_state *encoder);

void initialize_oscillator_controller(oscillator_controller *oscillator_control,
                                      uint8_t id);

/* Reads the values for all needed encoders and updates its own state
 * (detuneOffset and type) accordingly.
 *
 * Note:
 * To function correctly it has to get called fast enough to not "miss" clicks
 * at the encoder (e.g. from a short-enough firing timer-interrupt)
 */
void oscillator_tick(volatile oscillator_controller *controller);
#endif
