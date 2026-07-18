#ifndef SYNTHENVELOPE_H
#define SYNTHENVELOPE_H
#include <Audio.h>

#include "SerialLogger.hpp"
#include "Settings.hpp"

/*! Wrapper for the AudioEffectEnvelop of the teensy-audio-library to get an
 * ADSR-envelope */
class SynthEnvelope {
private:
  AudioEffectEnvelope *_teensyEnvelope;
  uint8_t _attackCC;
  uint8_t _decayCC;
  uint8_t _sustainCC;
  uint8_t _releaseCC;
  // 11800ms = 1.96s
  const float MAX_ATTACK_IN_MS = 3000; /**< Maximum time for the attack in ms */
  // 11800ms = 1.96s
  const float MAX_DECAY_IN_MS = 3000; /**< Maximum time for the decay in ms */
  // 11800ms = 1.96s
  const float MAX_RELEASE_IN_MS =
      3000; /**< Maximum time for the release in ms */

  Logger *_logger;

public:
  /*!
   * \param[in] teensyEnvelope
   * \param[in] attackCC CC-value for controlling the attack-value
   * \param[in] attackCC CC-value for controlling the decay-value
   * \param[in] attackCC CC-value for controlling the sustain-value
   * \param[in] attackCC CC-value for controlling the release-value
   * \param[in] logger instance of the logger
   */
  SynthEnvelope(AudioEffectEnvelope *teensyEnvelope, uint8_t attackCC,
                uint8_t decayCC, uint8_t sustainCC, uint8_t releaseCC,
                Logger *logger);

  /*! Destructor, frees logger */
  ~SynthEnvelope(void);
  void Initialize(void);
  void Initialize(EnvelopeSetting setting);
  void HandleMidiCC(uint8_t cc, uint8_t value);
  void NoteOn(void);
  void NoteOff(void);
};

#endif