#include "DCO.hpp"

void DCO::PrintWaveformChangeToSerial(oscillator_waveform waveform) {
  switch (waveform) {
  case OSC_SAW:
    _logger->println("WaveformChange: Sawtooth\n", LOGLEVEL_DEBUG);
    break;
  case OSC_TRIANGLE:
    _logger->println("WaveformChange: Triangle\n", LOGLEVEL_DEBUG);
    break;
  case OSC_SQUARE:
    _logger->println("WaveformChange: Square\n", LOGLEVEL_DEBUG);
    break;
  case OSC_SINE:
    _logger->println("WaveformChange: Sine\n", LOGLEVEL_DEBUG);
    break;
  default:
    _logger->println("WaveformChange: UNKNOWN\n", LOGLEVEL_DEBUG);
  }
}

DCO::DCO(AudioSynthWaveform *vco, int typeChangeMidiCC, int detuneChangeMidiCC,
         float maxVolume, const char *loggingContext, Logger *logger) {
  this->_teensyVCO = vco;
  this->_maxVolume = maxVolume;
  this->_detuneChangeMidiCC = detuneChangeMidiCC;
  this->_typeChangeMidiCC = typeChangeMidiCC;
  this->_logger = logger;
}

void DCO::Initialize() {
  _logger->println("Initializing VCO with default values", LOGLEVEL_DEBUG);
  _teensyVCO->begin(_maxVolume, MIDI::MidiToFrequency(60), DEFAULT_TYPE);
}

void DCO::Initialize(VCOSetting setting) {
  _logger->println("Initializing VCO with loaded settings", LOGLEVEL_DEBUG);
  if (setting.Type >= 0 && setting.Type <= 4) {
    _teensyVCO->begin(_maxVolume, MIDI::MidiToFrequency(60),
                      _waveformLookup[setting.Type]);
  } else {
    _logger->println("Value for type out of range, using default",
                     LOGLEVEL_ERROR);
    Initialize();
  }
}

void DCO::SwitchVCO1Waveform(oscillator_waveform waveform) {
  PrintWaveformChangeToSerial(waveform);
  _teensyVCO->begin(waveform);
}

void DCO::HandleMidiCC(uint8_t cc, uint8_t value) {
  if (cc == _typeChangeMidiCC) {
    this->HandleTypeChange(value);
  }

  if (cc == _detuneChangeMidiCC) {
    this->HandleDetuneChange(value);
  }
}

void DCO::HandleTypeChange(uint8_t waveformId) {
  if (waveformId < 0 || waveformId > 3) {
    waveformId = 0;
  }

  _teensyVCO->begin(_waveformLookup[waveformId]);
}

void DCO::HandlePitchChange(uint8_t midiValue) {
  float frequency = MIDI::MidiToFrequency(midiValue);
  //_logger->printf("PitchChange: %f\n", frequency);
  _teensyVCO->frequency(frequency + _current_detune);
}

void DCO::HandleVelocityChange(uint8_t velocity) {
  //_logger->printf("VelocityChange: %i\n", velocity);
  _teensyVCO->amplitude(velocity * DIV127);
}

void DCO::HandleDetuneChange(uint8_t detune) {
  // TODO
  //_logger->printf("(NotImplementedYet)DetuneChange: %i\n", detune);
}