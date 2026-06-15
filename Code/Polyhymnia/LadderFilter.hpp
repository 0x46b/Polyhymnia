#ifndef LADDER_FILTER_HPP
#define LADDER_FILTER_HPP

#include <Audio.h>
#include "Constants.hpp"
#include "MIDI.hpp"
#include "Settings.hpp"
#include "SerialLogger.hpp"

class LadderFilter {
private:
  AudioFilterLadder* _teensyFilter;
  SerialLogger _logger;

  float CalculateCutoff(byte midiValue);
  void SetCutoff(byte value);
  void SetResonance(byte value);

  public:
  LadderFilter(AudioFilterLadder* teensyFilter);

  void HandleMidiCC(byte cc, byte value);
  void Initialize();
  void Initialize(FilterSetting setting);
};

#endif