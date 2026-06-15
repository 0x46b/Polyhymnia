#ifndef MIDI_HPP
#define MIDI_HPP
#include <Arduino.h>
#include "Constants.hpp"

class MIDI {
public:
  static float MidiToFrequency(int midiValue) {
    if (midiValue < 0 || midiValue > 127) {
      return 0;
    }

    return midiToFrequency[midiValue];
  }

  static float MidiValueToValue(byte value, float maxValue, float offset){
    return offset + maxValue * (value * DIV127);
  }
  
  static void PrintMidiNoteInfoToSerial(const String& msg, byte channel, byte note, byte velocity) {
    Serial.printf("%s Channel: %i Note: %i Velocity: %i\n", msg, channel, note, velocity);
  }

  static void PrintMidiCCInfoToSerial(byte channel, byte control, byte value) {
    Serial.printf("%s Channel: %i CC: %i Value: %i\n", channel, control, value);
  }
};

#endif