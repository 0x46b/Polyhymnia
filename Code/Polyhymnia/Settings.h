#ifndef SETTINGS_H
#define SETTINGS_H

#include "Constants.h"

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

  PatchSetting(){
    Name = "Unused";
  }
};

// Class-Definitions
class Settings {

public:
  SystemSettings System;
  PatchSetting Patches[100];

  Settings()
    : System() {
  }

  bool LoadSettings() {
    if (!SD.begin(BUILTIN_SDCARD)) {
      Serial.println("initialization failed!");
      return false;
    }

    File input = SD.open(SETTINGS_FILENAME, FILE_READ);
    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, input);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return false;
    }

    JsonObject settings = doc["settings"];
    System.ShowBootscreen = settings["ShowBootscreen"];          // "true"
    System.BootscreenFilepath = settings["BootscreenFilepath"];  // nullptr
    System.MidiChannel = settings["MidiChannel"];                // 1

    int patchCounter = 0;
    for (JsonObject patche : doc["patches"].as<JsonArray>()) {
      PatchSetting currentPatch = Patches[patchCounter];
      currentPatch.Name = patche["Name"];  // "Patch 1", "Patch 2"

      currentPatch.VCO1.Type = patche["VCO1"]["Type"];      // 1, 1
      currentPatch.VCO1.Detune = patche["VCO1"]["Detune"];  // 0, 0

      currentPatch.VCO2.Type = patche["VCO2"]["Type"];      // 1, 1
      currentPatch.VCO2.Detune = patche["VCO2"]["Detune"];  // 0, 0

      currentPatch.VCO3.Type = patche["VCO3"]["Type"];      // 1, 1
      currentPatch.VCO3.Detune = patche["VCO3"]["Detune"];  // 0, 0

      currentPatch.Noise.Gain = patche["Noise"]["Gain"];  // 0, 0

      JsonObject patche_Envelope = patche["Envelope"];
      currentPatch.Envelope.Attack = patche_Envelope["Attack"];    // 0, 0
      currentPatch.Envelope.Decay = patche_Envelope["Decay"];      // 35, 35
      currentPatch.Envelope.Sustain = patche_Envelope["Sustain"];  // 1, 1
      currentPatch.Envelope.Release = patche_Envelope["Release"];  // 300, 300

      JsonObject patche_Filter = patche["Filter"];
      currentPatch.Filter.Type = patche_Filter["FilterType"];      // 0, 0
      currentPatch.Filter.Cutoff = patche_Filter["Cutoff"];        // 1, 1
      currentPatch.Filter.Resonance = patche_Filter["Resonance"];  // 0, 0

      currentPatch.LFO.Rate = patche["LFO"]["Rate"];      // 10, 10
      currentPatch.LFO.Amount = patche["LFO"]["Amount"];  // 50, 50

      JsonObject patche_Mixer = patche["Mixer"];
      currentPatch.Mixer.VCO1Gain = patche_Mixer["VCO1Gain"];    // 0.3, 0.3
      currentPatch.Mixer.VCO2Gain = patche_Mixer["VCO2Gain"];    // 0.3, 0.3
      currentPatch.Mixer.VCO3Gain = patche_Mixer["VCO3Gain"];    // 0.3, 0.3
      currentPatch.Mixer.NoiseGain = patche_Mixer["NoiseGain"];  // 0, 0

      patchCounter++;
    }

    return true;
  }
};

#endif