#include "MIDI.hpp"
#include <cstdint>

float MIDI::midivalue_to_frequency(uint8_t midiValue) {
  return midiToFrequency[midiValue];
}

float MIDI::MidiValueToValue(uint8_t value, float maxValue, float offset) {
  return offset + maxValue * (value * DIV127);
}