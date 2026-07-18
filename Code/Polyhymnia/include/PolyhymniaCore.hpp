#ifndef POLYHYMNIA_CORE_H
#define POLYHYMNIA_CORE_H
#include "DCO.hpp"
#include "HardwareInterfaceCommunication.h"
#include "LadderFilter.hpp"
#include "LoggerFactory.hpp"
#include "Settings.hpp"
#include "SynthEnvelope.hpp"
#include "SynthMixer.hpp"
#include <Audio.h>
/* Core-class for the polyhymnia-synthesizer-system.
 * It will initialize all needed systems, like oscillators, mixers etc. and
 * handle changes.
 */
class PolyhymniaCore {
private:
  DCO _polyVCO1;
  DCO _polyVCO2;
  DCO _polyVCO3;
  SynthMixer _mixer;
  SynthEnvelope _envelope;
  LadderFilter _filter;
  Settings _settings;
  Logger *_logger;
  HardwareInterfaceCommunication _hardwareCommunication;
  AudioControlSGTL5000 *_sgtl5000;

public:
  PolyhymniaCore(AudioSynthWaveform *vco1, AudioSynthWaveform *vco2,
                 AudioSynthWaveform *vco3, AudioMixer4 *mixer,
                 AudioEffectEnvelope *envelope, AudioFilterLadder *filter,
                 AudioControlSGTL5000 *sgtl5000, LoggerFactory factory);
  /* Loads the settings (if any) and applies them. If no settings are found it
   * will use default values instead
   */
  void Initialize();
  void HandleMIDICC(uint8_t channel, uint8_t control, uint8_t value);
  void HandleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
  void HandleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
  void Tick();
};
#endif