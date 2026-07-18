#include "SynthMixer.hpp"
#include "SerialLogger.hpp"

SynthMixer::SynthMixer(AudioMixer4 *teensyMixer, uint8_t vco1CC, uint8_t vco2CC,
                       uint8_t vco3CC, uint8_t noiseCC, Logger *logger) {
  this->_teensyMixer = teensyMixer;
  this->_vco1CC = vco1CC;
  this->_vco2CC = vco2CC;
  this->_vco3CC = vco3CC;
  this->_noiseCC = noiseCC;
  this->_logger = logger;
}

SynthMixer::~SynthMixer(void) { free(_logger); }

float SynthMixer::CalculatePercentage(uint8_t quantity, float total) {
  // Avoid dividing by zero
  if (total == 0) {
    if (quantity == 0) {
      total = quantity;
    } else {
      return 1;
    }
  }

  return 1 / total * quantity;
}

// We had to make sure total gain is never over 1, so calculate the percentage
// of each volume and apply it as gain
/*
  Channels:
    0 = VCO1
    1 = VCO2
    2 = VCO3
    3 = Noise
*/
void SynthMixer::UpdateVolumes(void) {
  int totalVolumes = this->_vco1Volume + this->_vco2Volume + this->_vco3Volume +
                     this->_noiseVolume;

  float vco1gain = CalculatePercentage(this->_vco1Volume, totalVolumes);
  _logger->print("Setting VCO1 gain to ", LOGLEVEL_DEBUG);
  _logger->print(vco1gain, LOGLEVEL_DEBUG);

  this->_teensyMixer->gain(0, vco1gain);

  float vco2gain = CalculatePercentage(this->_vco2Volume, totalVolumes);
  _logger->printf("Setting VCO2 gain to %f\n", vco2gain);
  this->_teensyMixer->gain(1, vco2gain);

  float vco3gain = CalculatePercentage(this->_vco3Volume, totalVolumes);
  _logger->printf("Setting VCO3 gain to %f\n", vco3gain);
  this->_teensyMixer->gain(2, vco3gain);

  float noisegain = CalculatePercentage(this->_noiseVolume, totalVolumes);
  _logger->printf("Setting Noise gain to %f\n", noisegain);
  this->_teensyMixer->gain(3, noisegain);
}

void SynthMixer::Initialize(MixerSetting settings) {
  _logger->println("Initializing mixer with loaded settings", LOGLEVEL_DEBUG);
  this->_vco1Volume = settings.VCO1Gain;
  this->_vco2Volume = settings.VCO2Gain;
  this->_vco3Volume = settings.VCO3Gain;
  this->_noiseVolume = settings.NoiseGain;

  this->UpdateVolumes();
}

void SynthMixer::Initialize(void) {
  _logger->println("Initializing mixer with default values", LOGLEVEL_DEBUG);
  this->_vco1Volume = 42;
  this->_vco2Volume = 42;
  this->_vco3Volume = 42;

  this->UpdateVolumes();
}

void SynthMixer::SetVCOVolume(int vcoNumber, uint8_t volume) {

  switch (vcoNumber) {
  case 0:
    this->_vco1Volume = volume;
    _logger->printf("Changing volume of VCO1 to %f\n", volume);
    break;
  case 1:
    this->_vco2Volume = volume;
    _logger->printf("Changing volume of VCO2 to %f\n", volume);
    break;
  case 2:
    this->_vco3Volume = volume;
    _logger->printf("Changing volume of VCO3 to %f\n", volume);
    break;
  case 3:
    this->_noiseVolume = volume;
    _logger->printf("Changing volume of Noise to %f\n", volume);
    break;
  }
  this->UpdateVolumes();
}

void SynthMixer::HandleMidiCC(uint8_t cc, uint8_t value) {
  if (cc == this->_vco1CC) {
    this->SetVCOVolume(0, value);
  }
  if (cc == this->_vco2CC) {
    this->SetVCOVolume(1, value);
  }
  if (cc == this->_vco3CC) {
    this->SetVCOVolume(2, value);
  }
  if (cc == this->_noiseCC) {
    this->SetVCOVolume(3, value);
  }
}