#ifndef VCO_H
#define VCO_H

#include "Constants.h"
#include "MIDI.h"

class VCO {
private:
  const short DEFAULT_TYPE = WAVEFORM_SAWTOOTH;
  float _current_detune = 0;
  float _maxVolume = 1.0;
  AudioSynthWaveform* _teensyVCO;
  MIDI _midi;

  // Waveform lookup
  // Note: Noise is not generated through the VCO1, so we had to handle it separately
  const short _waveformLookup[4] = { WAVEFORM_SAWTOOTH, WAVEFORM_TRIANGLE, WAVEFORM_SQUARE, WAVEFORM_SINE };
  byte _detuneChangeMidiCC;
  byte _typeChangeMidiCC;

  void PrintWaveformChangeToSerial(int waveform) {
    switch (waveform) {
      case 0:
        Serial.println("WaveformChange: Sawtooth\n");
        break;
      case 1:
        Serial.println("WaveformChange: Triangle\n");
        break;
      case 2:
        Serial.println("WaveformChange: Square\n");
        break;
      case 4:
        Serial.println("WaveformChange: Sine\n");
        break;
      default:
        Serial.println("WaveformChange: UNKNOWN\n");
    }
  }

public:
  VCO(AudioSynthWaveform* vco, int typeChangeMidiCC, int detuneChangeMidiCC, float maxVolume)
    : _midi() {
    this->_teensyVCO = vco;
    this->_maxVolume = maxVolume;
    this->_detuneChangeMidiCC = detuneChangeMidiCC;
    this->_typeChangeMidiCC = typeChangeMidiCC;
  }

  void Initialize() {
    _teensyVCO->begin(_maxVolume, _midi.MidiToFrequency(60), DEFAULT_TYPE);
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
    Serial.printf("PitchChange: %f\n", frequency);
    _teensyVCO->frequency(frequency + _current_detune);
  }

  void HandleVelocityChange(byte velocity) {
    Serial.printf("VelocityChange: %i\n", velocity);
    _teensyVCO->amplitude(velocity * DIV127);
  }

  void HandleDetuneChange(byte detune) {
    // TODO
    Serial.printf("(NotImplementedYet)DetuneChange: %i\n", detune);
  }
};

#endif