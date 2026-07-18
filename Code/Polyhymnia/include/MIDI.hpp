#ifndef MIDI_HPP
#define MIDI_HPP
#include "Constants.hpp"
#include <cstdint>

class MIDI {
public:
  static float MidiToFrequency(int midiValue) {
    if (midiValue < 0 || midiValue > 127) {
      return 0;
    }

    return midiToFrequency[midiValue];
  }

  static float MidiValueToValue(uint8_t value, float maxValue, float offset) {
    return offset + maxValue * (value * DIV127);
  }

  static void PrintMidiNoteInfoToSerial(const char* msg, uint8_t channel,
                                        uint8_t note, uint8_t velocity) {
    // Serial.printf("%s Channel: %i Note: %i Velocity: %i\n", msg, channel, note,
    //               velocity);
  }

  static void PrintMidiCCInfoToSerial(uint8_t channel, uint8_t control,
                                      uint8_t value) {
    // Serial.printf("%s Channel: %i CC: %i Value: %i\n", channel, control, value);
  }
};

#endif