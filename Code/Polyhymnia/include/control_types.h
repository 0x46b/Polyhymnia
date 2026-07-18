#ifndef CONTROL_TYPES_H
#define CONTROL_TYPES_H

typedef enum {
  SAW = 0,
  TRIANGLE = 1,
  SQUARE = 2,
  SINE = 3
} OscillatorType;

typedef struct {
  uint8_t Id;
  uint8_t Offset;
  OscillatorType Type;
} OscillatorState;

typedef struct {
  uint8_t Attack;
  uint8_t Sustain;
  uint8_t Decay;
  uint8_t Release;
} EnvelopeState;

typedef struct {
  uint8_t Cutoff;
  uint8_t Resonance;
} FilterState;

typedef struct {
  uint8_t Frequency;
  uint8_t Amount;
} LFOState;

#endif