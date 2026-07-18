#ifndef LADDER_FILTER_HPP
#define LADDER_FILTER_HPP

#include <Audio.h>
#include<inttypes.h>
#include "Settings.hpp"
#include "SerialLogger.hpp"

class LadderFilter {
private:
  AudioFilterLadder* _teensyFilter;
  Logger* _logger;

  float CalculateCutoff(uint8_t midiValue);
  void SetCutoff(uint8_t value);
  void SetResonance(uint8_t value);

  public:
  LadderFilter(AudioFilterLadder* teensyFilter, Logger* logger);
  ~LadderFilter(void);

  void HandleMidiCC(uint8_t cc, uint8_t value);
  void Initialize();
  void Initialize(FilterSetting setting);
};

#endif