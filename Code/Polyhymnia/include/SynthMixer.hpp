#ifndef SYNTHMIXER_H
#define SYNTHMIXER_H

#include "SerialLogger.hpp"
#include "Settings.hpp"
#include <Audio.h>
#include <cstdint>

class SynthMixer {
private:
  AudioMixer4 *_teensyMixer;
  float _vco1Volume;
  float _vco2Volume;
  float _vco3Volume;
  float _noiseVolume;

  uint8_t _vco1CC;
  uint8_t _vco2CC;
  uint8_t _vco3CC;
  uint8_t _noiseCC;
  Logger *_logger;

  float CalculatePercentage(uint8_t quantity, float total);

  // We had to make sure total gain is never over 1, so calculate the percentage
  // of each volume and apply it as gain
  /*
    Channels:
      0 = VCO1
      1 = VCO2
      2 = VCO3
      3 = Noise
  */
  void UpdateVolumes();

public:
  SynthMixer(AudioMixer4 *teensyMixer, uint8_t vco1CC, uint8_t vco2CC,
             uint8_t vco3CC, uint8_t noiseCC, Logger *logger);
  ~SynthMixer(void);
  void Initialize(MixerSetting settings);
  void Initialize(void);
  void SetVCOVolume(int vcoNumber, uint8_t volume);
  void HandleMidiCC(uint8_t cc, uint8_t value);
};

#endif