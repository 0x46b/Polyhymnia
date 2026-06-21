#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include <stdint.h>
#include "vars.h"

typedef struct {
  uint8_t Number;
  Waveform Waveform;
  int8_t Detune;
  uint8_t Volume;
} Oscillator;

#endif