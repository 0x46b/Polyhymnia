#include "oscillator_controller.h"

void encoder_initialize(volatile encoder_config *config) {
  // Get DDR via offset
  volatile uint8_t *ddr = config->port - 1;
  // Set pinA and pinB as output
  *ddr &= ~(1 << config->pinA) | ~(1 << config->pinB);
  *config->port |= (1 << config->pinA) | (1 << config->pinB);
}

void initialize_oscillator_controller(oscillator_controller *oscillator_control,
                                      uint8_t id) {
  oscillator_control->state.Id = id;
  oscillator_control->state.DetuneOffset = 0;
  oscillator_control->state.Type = SAW;
  encoder_initialize(&oscillator_control->typeState.config);
  encoder_initialize(&oscillator_control->detuneState.config);
  led_controller_initialize(&oscillator_control->led_state.config);
}

int encoder_read_offset(volatile encoder_state *encoder) {
  int8_t currentOffsetBuff = encoder->offset;
  encoder->offset = 0;

  return currentOffsetBuff;
}

void encoder_tick(volatile encoder_state *encoder) {
  // Shift old-state 2 to the right and trim first byte
  // e.g. old-state = 00001010 => <<2 => 00101000 => &0x0F => 00001000
  encoder->oldState = (encoder->oldState << 2) & 0x0F;

  // Get PIN from Port via offset
  volatile uint8_t *pin_reg = encoder->config.port - 2;

  // Check, if A is HIGH, if so set second last bit to 1
  if (*pin_reg & (1 << encoder->config.pinA)) {
    encoder->oldState |= 2;
  }
  // Check, if B is HIGH, if so set last bit to 1
  if (*pin_reg & (1 << encoder->config.pinB)) {
    encoder->oldState |= 1;
  }

  // Get value from our gray-table
  int8_t movement = STATETABLE[encoder->oldState];
  if (movement == 1 || movement == -1) {
    encoder->offset += movement;
  }
}

OscillatorType handle_type_change(int typeOffset) {
  assert(!"The method or operation is not implemented.");
}

void oscillator_tick(volatile oscillator_controller *controller) {
  encoder_tick(&controller->detuneState);
  encoder_tick(&controller->typeState);
  controller->state.DetuneOffset +=
      encoder_read_offset(&controller->detuneState);
  controller->state.Type =
      handle_type_change(encoder_read_offset(&controller->typeState));
}

void set_waveform_for_osc(volatile oscillator_controller *controller,
                          OscillatorType type, uint8_t id) {
  /* switch (type) { */
  /* case SAW: */
  /*   *controller->ledConfig.pin |= (1 << controller->ledConfig.pinSaw); */
  /*   *controller->ledConfig.pin &= ~(1 << controller->ledConfig.pinSine) | */
  /*                                 ~(1 << controller->ledConfig.pinTriangle) |
   */
  /*                                 ~(1 << controller->ledConfig.pinSquare); */
  /*   break; */
  /* case TRIANGLE: */
  /*   *controller->ledConfig.pin |= (1 << controller->ledConfig.pinTriangle);
   */
  /*   *controller->ledConfig.pin &= ~(1 << controller->ledConfig.pinSine) | */
  /*                                 ~(1 << controller->ledConfig.pinSaw) | */
  /*                                 ~(1 << controller->ledConfig.pinSquare); */
  /*   break; */
  /* case SINE: */
  /*   *controller->ledConfig.pin |= (1 << controller->ledConfig.pinSine); */
  /*   *controller->ledConfig.pin &= ~(1 << controller->ledConfig.pinSaw) | */
  /*                                 ~(1 << controller->ledConfig.pinTriangle) |
   */
  /*                                 ~(1 << controller->ledConfig.pinSquare); */
  /*   break; */
  /* case SQUARE: */
  /*   *controller->ledConfig.pin |= (1u << controller->ledConfig.pinSquare); */
  /*   *controller->ledConfig.pin &= ~(1u << controller->ledConfig.pinSine) | */
  /*                                 ~(1u << controller->ledConfig.pinTriangle)
   * | */
  /*                                 ~(1u << controller->ledConfig.pinSaw); */
  /*   break; */
  /* } */
  controller->state.Type = type;
}
