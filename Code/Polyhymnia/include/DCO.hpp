#ifndef DCO_H
#define DCO_H
#include "Constants.hpp"
#include "Logger.hpp"
#include "MIDI.hpp"
#include <Audio.h>
#include <cstdint>

typedef enum oscillator_waveform {
  OSC_SAW = WAVEFORM_SAWTOOTH,
  OSC_TRIANGLE = WAVEFORM_TRIANGLE,
  OSC_SQUARE = WAVEFORM_SQUARE,
  OSC_SINE = WAVEFORM_SINE
} oscillator_waveform;

/* Wrapper for the teensy AudioSynthWaveform object to control the oscillator
 */
class DCO {
private:
  const short DEFAULT_TYPE = WAVEFORM_SAWTOOTH;
  float _current_detune = 0;
  float _maxVolume = 1.0;
  AudioSynthWaveform *_teensyVCO;
  Logger *_logger;

  // Waveform lookup
  // Note: Noise is not generated through the VCO1, so we had to handle it
  // separately
  const short _waveformLookup[4] = {WAVEFORM_SAWTOOTH, WAVEFORM_TRIANGLE,
                                    WAVEFORM_SQUARE, WAVEFORM_SINE};
  uint8_t _detuneChangeMidiCC;
  uint8_t _typeChangeMidiCC;

  void PrintWaveformChangeToSerial(oscillator_waveform waveform);

public:
  DCO(AudioSynthWaveform *vco, int typeChangeMidiCC, int detuneChangeMidiCC,
      float maxVolume, const char *loggingContext, Logger *logger);

  /* Initialize with default values */
  void Initialize();

  /* Initialize with the values from the given settings */
  void Initialize(VCOSetting setting);

  /* Switch waveform of the oscillator */
  void SwitchVCO1Waveform(oscillator_waveform waveform);

  /* Handle a CC coming from MIDI, used as callback from the MIDI-system */
  void HandleMidiCC(uint8_t cc, uint8_t value);

  void HandleTypeChange(uint8_t waveformId);

  void HandlePitchChange(uint8_t midiValue);

  void HandleVelocityChange(uint8_t velocity);

  void HandleDetuneChange(uint8_t detune);
};

#endif