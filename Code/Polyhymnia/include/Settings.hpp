#ifndef SETTINGS_H
#define SETTINGS_H

#include "Constants.hpp"

class SystemSettings {
public:
  bool ShowBootscreen;
  const char* BootscreenFilepath;
  int MidiChannel;
};

class VCOSetting {
public:
  int Type;
  float Detune;
};

class NoiseSetting {
public:
  float Gain;
};

class EnvelopeSetting {
public:
  float Attack;
  float Decay;
  float Sustain;
  float Release;
};

class MixerSetting {
public:
  float VCO1Gain;
  float VCO2Gain;
  float VCO3Gain;
  float NoiseGain;
};

class FilterSetting {
public:
  int Type;
  float Cutoff;
  float Resonance;
};

class LFOSetting {
public:
  float Rate;
  float Amount;
};

class PatchSetting {
public:
  const char* Name;
  VCOSetting VCO1;
  VCOSetting VCO2;
  VCOSetting VCO3;
  NoiseSetting Noise;
  EnvelopeSetting Envelope;
  MixerSetting Mixer;
  FilterSetting Filter;
  LFOSetting LFO;

  PatchSetting() {
    Name = "Unused";
  }
};

// Class-Definitions
class Settings {
private:
  bool _loadedSuccessfully = false;
  const char* _filename;

public:
  SystemSettings System;
  PatchSetting Patches[NUMBER_OF_PATCHES];

  Settings(const char* filename);

  bool LoadSettings();

  bool Save();

  bool is_loaded();
};

#endif