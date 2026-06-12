#ifndef VCO_H
#define VCO_H

#include "SerialLogger.hpp"
#include "Constants.h"
#include "MIDI.h"

class VCO {
private:
  const short DEFAULT_TYPE = WAVEFORM_SAWTOOTH;
  float _current_detune = 0;
  float _maxVolume = 1.0;
  AudioSynthWaveform* _teensyVCO;
  MIDI _midi;
  SerialLogger _logger;

  // Waveform lookup
  // Note: Noise is not generated through the VCO1, so we had to handle it separately
  const short _waveformLookup[4] = { WAVEFORM_SAWTOOTH, WAVEFORM_TRIANGLE, WAVEFORM_SQUARE, WAVEFORM_SINE };
  byte _detuneChangeMidiCC;
  byte _typeChangeMidiCC;

  void PrintWaveformChangeToSerial(int waveform) {
    switch (waveform) {
      case 0:
        _logger.println("WaveformChange: Sawtooth\n", LOGLEVEL_DEBUG);
        break;
      case 1:
        _logger.println("WaveformChange: Triangle\n", LOGLEVEL_DEBUG);
        break;
      case 2:
        _logger.println("WaveformChange: Square\n", LOGLEVEL_DEBUG);
        break;
      case 4:
        _logger.println("WaveformChange: Sine\n", LOGLEVEL_DEBUG);
        break;
      default:
        _logger.println("WaveformChange: UNKNOWN\n", LOGLEVEL_DEBUG);
    }
  }

public:
  VCO(AudioSynthWaveform* vco, int typeChangeMidiCC, int detuneChangeMidiCC, float maxVolume, String loggingContext)
    : _midi(), _logger(loggingContext, CURRENT_LOGLEVEL) {
    this->_teensyVCO = vco;
    this->_maxVolume = maxVolume;
    this->_detuneChangeMidiCC = detuneChangeMidiCC;
    this->_typeChangeMidiCC = typeChangeMidiCC;
  }

  void Initialize() {
    _logger.println("Initializing VCO with default values", LOGLEVEL_DEBUG);
    _teensyVCO->begin(_maxVolume, _midi.MidiToFrequency(60), DEFAULT_TYPE);
  }

  void Initialize(VCOSetting setting) {
    _logger.println("Initializing VCO with loaded settings", LOGLEVEL_DEBUG);
    if (setting.Type >= 0 && setting.Type <= 4) {
      _teensyVCO->begin(_maxVolume, _midi.MidiToFrequency(60), _waveformLookup[setting.Type]);
    } else {
      _logger.println("Value for type out of range, using default", LOGLEVEL_ERROR);
      Initialize();
    }
  }

  void SwitchVCO1Waveform(int waveform) {
    PrintWaveformChangeToSerial(waveform);
    _teensyVCO->begin(waveform);
  }

  void HandleMidiCC(byte cc, byte value) {
    if (cc == _typeChangeMidiCC) {
      this->HandleTypeChange(value);
    }

    if (cc == _detuneChangeMidiCC) {
      this->HandleDetuneChange(value);
    }
  }

  void HandleTypeChange(byte waveformId) {
    if (waveformId < 0 || waveformId > 3) {
      waveformId = 0;
    }

    _teensyVCO->begin(_waveformLookup[waveformId]);
  }

  void HandlePitchChange(byte midiValue) {
    float frequency = _midi.MidiToFrequency(midiValue);
    //_logger.printf("PitchChange: %f\n", frequency);
    _teensyVCO->frequency(frequency + _current_detune);
  }

  void HandleVelocityChange(byte velocity) {
    //_logger.printf("VelocityChange: %i\n", velocity);
    _teensyVCO->amplitude(velocity * DIV127);
  }

  void HandleDetuneChange(byte detune) {
    // TODO
    //_logger.printf("(NotImplementedYet)DetuneChange: %i\n", detune);
  }
};

#endif