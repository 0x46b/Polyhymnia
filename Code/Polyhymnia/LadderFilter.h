#ifndef FILTER_H
#define FILTER_H

#include "Constants.h"
#include "MIDI.h"

class LadderFilter {
private:
  AudioFilterLadder* _teensyFilter;

  float calculateCutoff(byte midiValue) {
    // TODO: Add potentially LFO
    return MIDI::MidiValueToValue(midiValue, 20000, 0);
  }
public:
  LadderFilter(AudioFilterLadder* teensyFilter) {
    _teensyFilter = teensyFilter;
  }

  void HandleMidiCC(byte cc, byte value) {
    switch (cc) {
        // Cutoff (16Hz - 20 kHz)
      case 74:
        _teensyFilter->frequency(calculateCutoff(value));
        break;
      // Resonance (value Range from 0 - 1.8, everything over 1 self-resonates)
      case 71:
        _teensyFilter->resonance(1.8 * (value * DIV127));
        break;
    }
  }

  void Initialize() {}
};

#endif