#ifndef SYNTHENVELOPE_H
#define SYNTHENVELOPE_H
#include <Audio.h>

#include "SerialLogger.hpp"
#include "Settings.hpp"

class SynthEnvelope {
private:
  AudioEffectEnvelope* _teensyEnvelope;
  uint8_t _attackCC;
  uint8_t _decayCC;
  uint8_t _sustainCC;
  uint8_t _releaseCC;
  // 11800ms = 1.96s
  const float MAX_ATTACK_IN_MS = 3000;
  // 11800ms = 1.96s
  const float MAX_DECAY_IN_MS = 3000;
  // 11800ms = 1.96s
  const float MAX_RELEASE_IN_MS = 3000;

  Logger* _logger;


public:
  SynthEnvelope(AudioEffectEnvelope* teensyEnvelope, uint8_t attackCC, uint8_t decayCC, uint8_t sustainCC, uint8_t releaseCC, Logger *logger);
  ~SynthEnvelope(void);
  void Initialize();
  void Initialize(EnvelopeSetting setting);
  void HandleMidiCC(uint8_t cc, uint8_t value);
  void NoteOn(void);
  void NoteOff(void);
};

#endif