#include "MIDI.hpp"
#include <cstdint>

float MIDI::midivalue_to_frequency(uint8_t midiValue) {
  return midiToFrequency[midiValue];
}

float MIDI::scale_cc_linear(uint8_t value, float maxValue, float offset) {
  return offset + maxValue * (value * DIV127);
}