#ifndef WAVEFORM_TYPES_HPP
#define WAVEFORM_TYPES_HPP
#include <Audio.h>

/*! Enum for defining valid waveforms for the oscillators */
typedef enum oscillator_waveform {
  OSC_SAW = WAVEFORM_SAWTOOTH,
  OSC_TRIANGLE = WAVEFORM_TRIANGLE,
  OSC_SQUARE = WAVEFORM_SQUARE,
  OSC_SINE = WAVEFORM_SINE
} oscillator_waveform;

#endif