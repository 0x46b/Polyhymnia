#include "LadderFilter.hpp"

 float LadderFilter::CalculateCutoff(byte midiValue) {
    // TODO: Add potentially LFO
    return MIDI::MidiValueToValue(midiValue, 20000, 0);
  }

  void LadderFilter::SetCutoff(byte value) {
    _teensyFilter->frequency(CalculateCutoff(value));
  }

  void LadderFilter::SetResonance(byte value) {
    _teensyFilter->resonance(1.8 * (value * DIV127));
  }

  // Public

  LadderFilter::LadderFilter(AudioFilterLadder* teensyFilter)
  :_logger("Filter", CURRENT_LOGLEVEL) {
    _teensyFilter = teensyFilter;
  }

  void LadderFilter::HandleMidiCC(byte cc, byte value) {
    switch (cc) {
        // Cutoff (16Hz - 20 kHz)
      case 74:
        SetCutoff(value);
        break;
      // Resonance (value Range from 0 - 1.8, everything over 1 self-resonates)
      case 71:
        SetResonance(value);
        break;
    }
  }

  void LadderFilter::Initialize() {
    _logger.println("Initializing filter with default values", LOGLEVEL_DEBUG);
    SetCutoff(127);
    SetResonance(0);
  }

  void LadderFilter::Initialize(FilterSetting setting) {
    _logger.println("Initializing filter with loaded settings", LOGLEVEL_DEBUG);
    SetCutoff(setting.Cutoff);
    SetResonance(setting.Resonance);
  }