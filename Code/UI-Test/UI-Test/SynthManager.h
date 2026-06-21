#ifndef SYNTHMANAGER_H
#define SYNTHMANAGER_H
#include "vars.h"
#include "Envelope.h"
#include "Oscillator.h"

typedef struct {
  Oscillator Osc1;
  Oscillator Osc2;
  Oscillator Osc3;
  Envelope ADSR;
} SynthManager;


extern SynthManager synthManager;

#endif