#ifndef ENVELOPE_H
#define ENVELOPE_H
#include <stdint.h>

typedef struct {
  uint8_t Attack;
  uint8_t Decay;
  uint8_t Sustain;
  uint8_t Release;
} Envelope;
#endif