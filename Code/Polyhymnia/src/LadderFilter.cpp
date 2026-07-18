#include "LadderFilter.hpp"
#include "MIDI.hpp"
#include "SerialLogger.hpp"

LadderFilter::LadderFilter(AudioFilterLadder *teensyFilter, Logger *logger) {
  _logger = logger;
  _teensyFilter = teensyFilter;
}

LadderFilter::~LadderFilter(void) { free(_logger); }

float LadderFilter::CalculateCutoff(byte midiValue) {
  // TODO: Add potentially LFO
  return MIDI::scale_cc_linear(midiValue, 20000, 0);
}

void LadderFilter::SetCutoff(byte value) {
  _teensyFilter->frequency(CalculateCutoff(value));
}

void LadderFilter::SetResonance(byte value) {
  _teensyFilter->resonance(1.8 * (value * DIV127));
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
  _logger->println("Initializing filter with default values", LOGLEVEL_DEBUG);
  SetCutoff(127);
  SetResonance(0);
}

void LadderFilter::Initialize(FilterSetting setting) {
  _logger->println("Initializing filter with loaded settings", LOGLEVEL_DEBUG);
  SetCutoff(setting.Cutoff);
  SetResonance(setting.Resonance);
}