#ifndef SYNTHMIXER_H
#define SYNTHMIXER_H

#include "Constants.h"

class SynthMixer {
private:
  AudioMixer4* _teensyMixer;
  float _vco1Volume;
  float _vco2Volume;
  float _vco3Volume;
  float _noiseVolume;

  byte _vco1CC;
  byte _vco2CC;
  byte _vco3CC;
  byte _noiseCC;

  float CalculatePercentage(byte quantity, float total) {
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

  // We had to make sure total gain is never over 1, so calculate the percentage of each volume and apply it as gain
  /*
    Channels:
      0 = VCO1
      1 = VCO2
      2 = VCO3
      3 = Noise
  */
  void UpdateVolumes() {
    int totalVolumes = this->_vco1Volume + this->_vco2Volume + this->_vco3Volume + this->_noiseVolume;

    float vco1gain = CalculatePercentage(this->_vco1Volume, totalVolumes);
    Serial.printf("Setting VCO1 gain to %f\n", vco1gain);
    this->_teensyMixer->gain(0, vco1gain);

    float vco2gain = CalculatePercentage(this->_vco2Volume, totalVolumes);
    Serial.printf("Setting VCO2 gain to %f\n", vco2gain);
    this->_teensyMixer->gain(1, vco2gain);

    float vco3gain = CalculatePercentage(this->_vco3Volume, totalVolumes);
    Serial.printf("Setting VCO3 gain to %f\n", vco3gain);
    this->_teensyMixer->gain(2, vco3gain);

    float noisegain = CalculatePercentage(this->_noiseVolume, totalVolumes);
    Serial.printf("Setting Noise gain to %f\n", noisegain);
    this->_teensyMixer->gain(3, noisegain);
  }

public:
  SynthMixer(AudioMixer4* teensyMixer, byte vco1CC, byte vco2CC, byte vco3CC, byte noiseCC) {
    this->_teensyMixer = teensyMixer;
    this->_vco1CC = vco1CC;
    this->_vco2CC = vco2CC;
    this->_vco3CC = vco3CC;
    this->_noiseCC = noiseCC;
  }

  void Initialize() {
    this->_vco1Volume = 42;
    this->_vco2Volume = 42;
    this->_vco3Volume = 42;
    this->UpdateVolumes();
  }

  void SetVCOVolume(int vcoNumber, byte volume) {

    switch (vcoNumber) {
      case 0:
        this->_vco1Volume = volume;
        Serial.printf("Changing volume of VCO1 to %f\n", volume);
        break;
      case 1:
        this->_vco2Volume = volume;
        Serial.printf("Changing volume of VCO2 to %f\n", volume);
        break;
      case 2:
        this->_vco3Volume = volume;
        Serial.printf("Changing volume of VCO3 to %f\n", volume);
        break;
      case 3:
        this->_noiseVolume = volume;
        Serial.printf("Changing volume of Noise to %f\n", volume);
        break;
    }
    this->UpdateVolumes();
  }

  void HandleMidiCC(byte cc, byte value) {
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
};

#endif