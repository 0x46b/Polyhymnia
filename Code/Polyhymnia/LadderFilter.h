#ifndef FILTER_H
#define FILTER_H

#include "Constants.h"
#include "MIDI.h"
#include "Settings.h"

class LadderFilter {
private:
  AudioFilterLadder* _teensyFilter;
  SerialLogger _logger;

  float calculateCutoff(byte midiValue) {
    // TODO: Add potentially LFO
    return MIDI::MidiValueToValue(midiValue, 20000, 0);
  }

  void set_cutoff(byte value) {
    _teensyFilter->frequency(calculateCutoff(value));
  }

  void set_resonance(byte value) {
    _teensyFilter->resonance(1.8 * (value * DIV127));
  }
public:
  LadderFilter(AudioFilterLadder* teensyFilter)
  :_logger("Filter", CURRENT_LOGLEVEL) {
    _teensyFilter = teensyFilter;
  }

  void HandleMidiCC(byte cc, byte value) {
    switch (cc) {
        // Cutoff (16Hz - 20 kHz)
      case 74:
        set_cutoff(value);
        break;
      // Resonance (value Range from 0 - 1.8, everything over 1 self-resonates)
      case 71:
        set_resonance(value);
        break;
    }
  }

  void Initialize() {
    _logger.println("Initializing filter with default values", LOGLEVEL_DEBUG);
    set_cutoff(127);
    set_resonance(0);
  }

  void Initialize(FilterSetting setting) {
    _logger.println("Initializing filter with loaded settings", LOGLEVEL_DEBUG);
    set_cutoff(setting.Cutoff);
    set_resonance(setting.Resonance);
  }
};

#endif