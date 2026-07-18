#ifndef DCO_H
#define DCO_H
#include "Constants.hpp"
#include "Logger.hpp"
#include "MIDI.hpp"
#include "WaveformTypes.hpp"
#include <Audio.h>
#include <cstdint>

/*! Wrapper for the teensy AudioSynthWaveform object to control the oscillator
 */
class DCO {
private:
  const oscillator_waveform DEFAULT_TYPE = OSC_SAW;
  float _current_detune = 0;
  float _maxVolume = 1.0;
  AudioSynthWaveform *_teensyVCO;
  Logger *_logger;

  /*! Waveform lookup to get used to map a value coming over midi to an actual
   * waveform */
  const short _waveformLookup[4] = {WAVEFORM_SAWTOOTH, WAVEFORM_TRIANGLE,
                                    WAVEFORM_SQUARE, WAVEFORM_SINE};
  /*! CC-value for controlling detuning */
  uint8_t _detuneChangeMidiCC;
  /*! CC-value for controlling type-change */
  uint8_t _typeChangeMidiCC;

  void PrintWaveformChangeToSerial(oscillator_waveform waveform);

public:
  /*! Ctor for the DCO
   * \param[in] vco The teensy "oscillator"
   * \param[in] typeChangeMidiCC MIDI-CC-value that gets used to change the
   * waveform
   * \param[in] detuneChangeMidiCC MIDI-CC-value that gets used to change the
   * detuning
   * \param[in] maxVolume
   * \param[in] logger Instance of a Logger instance used to write logs
   */
  DCO(AudioSynthWaveform *vco, int typeChangeMidiCC, int detuneChangeMidiCC,
      float maxVolume, Logger *logger);

  /*! Initialize with default values */
  void Initialize();

  /*! Initialize with the values from the given VCOSetting */
  void Initialize(DCOSetting setting);

  /*! Switch waveform of the oscillator */
  void SwitchVCO1Waveform(oscillator_waveform waveform);

  /*! Handle a CC coming from MIDI, used as callback from the MIDI-system */
  void HandleMidiCC(uint8_t cc, uint8_t value);

  /*! Handle a type-change from MIDI */
  void HandleTypeChange(uint8_t waveformId);

  /*! Handle a pitch-change from MIDI */
  void HandlePitchChange(uint8_t midiValue);

  /*! Handle a velocity-change from MIDI */
  void HandleVelocityChange(uint8_t velocity);

  /*! Handle a detune-change from MIDI */
  void HandleDetuneChange(uint8_t detune);
};

#endif