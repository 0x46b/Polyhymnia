#ifndef SETTINGS_H
#define SETTINGS_H

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <SD.h>
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
  String _filename;

public:
  SystemSettings System;
  PatchSetting Patches[NUMBER_OF_PATCHES];

  Settings(String filename)
    : System() {
  }

  bool LoadSettings() {
    if (!SD.begin(BUILTIN_SDCARD)) {
      Serial.println("initialization failed!");
      _loadedSuccessfully = false;
      return false;
    }

    File input = SD.open(_filename.c_str(), FILE_READ);
    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, input);
    input.close();

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
      PatchSetting* currentPatch = &Patches[patchCounter];
      currentPatch->Name = patche["Name"];  // "Patch 1", "Patch 2"

      currentPatch->VCO1.Type = patche["VCO1"]["Type"];      // 1, 1
      currentPatch->VCO1.Detune = patche["VCO1"]["Detune"];  // 0, 0

      currentPatch->VCO2.Type = patche["VCO2"]["Type"];      // 1, 1
      currentPatch->VCO2.Detune = patche["VCO2"]["Detune"];  // 0, 0

      currentPatch->VCO3.Type = patche["VCO3"]["Type"];      // 1, 1
      currentPatch->VCO3.Detune = patche["VCO3"]["Detune"];  // 0, 0

      currentPatch->Noise.Gain = patche["Noise"]["Gain"];  // 0, 0

      JsonObject patche_Envelope = patche["Envelope"];
      currentPatch->Envelope.Attack = patche_Envelope["Attack"];    // 0, 0
      currentPatch->Envelope.Decay = patche_Envelope["Decay"];      // 35, 35
      currentPatch->Envelope.Sustain = patche_Envelope["Sustain"];  // 1, 1
      currentPatch->Envelope.Release = patche_Envelope["Release"];  // 300, 300

      JsonObject patche_Filter = patche["Filter"];
      currentPatch->Filter.Type = patche_Filter["FilterType"];      // 0, 0
      currentPatch->Filter.Cutoff = patche_Filter["Cutoff"];        // 1, 1
      currentPatch->Filter.Resonance = patche_Filter["Resonance"];  // 0, 0

      currentPatch->LFO.Rate = patche["LFO"]["Rate"];      // 10, 10
      currentPatch->LFO.Amount = patche["LFO"]["Amount"];  // 50, 50

      JsonObject patche_Mixer = patche["Mixer"];
      currentPatch->Mixer.VCO1Gain = patche_Mixer["VCO1Gain"];    // 0.3, 0.3
      currentPatch->Mixer.VCO2Gain = patche_Mixer["VCO2Gain"];    // 0.3, 0.3
      currentPatch->Mixer.VCO3Gain = patche_Mixer["VCO3Gain"];    // 0.3, 0.3
      currentPatch->Mixer.NoiseGain = patche_Mixer["NoiseGain"];  // 0, 0

      patchCounter++;
    }

    _loadedSuccessfully = true;
    return true;
  }

  bool Save() {
    JsonDocument doc;

    JsonObject settings = doc["settings"].to<JsonObject>();
    settings["ShowBootscreen"] = System.ShowBootscreen;
    settings["BootscreenFilepath"] = System.BootscreenFilepath;
    settings["MidiChannel"] = System.MidiChannel;

    JsonArray patches = doc["patches"].to<JsonArray>();

    for (int i = 0; i <= NUMBER_OF_PATCHES; i++) {
      JsonObject patches_0 = patches.add<JsonObject>();
      patches_0["Name"] = Patches[i].Name;

      JsonObject patches_0_VCO1 = patches_0["VCO1"].to<JsonObject>();
      patches_0_VCO1["Type"] = Patches[i].VCO1.Type;
      patches_0_VCO1["Detune"] = Patches[i].VCO1.Detune;

      JsonObject patches_0_VCO2 = patches_0["VCO2"].to<JsonObject>();
      patches_0_VCO2["Type"] = Patches[i].VCO2.Type;
      patches_0_VCO2["Detune"] = Patches[i].VCO2.Detune;

      JsonObject patches_0_VCO3 = patches_0["VCO3"].to<JsonObject>();
      patches_0_VCO3["Type"] = Patches[i].VCO3.Type;
      patches_0_VCO3["Detune"] = Patches[i].VCO3.Detune;
      patches_0["Noise"]["Gain"] = Patches[i].Noise.Gain;

      JsonObject patches_0_Envelope = patches_0["Envelope"].to<JsonObject>();
      patches_0_Envelope["Attack"] = Patches[i].Envelope.Attack;
      patches_0_Envelope["Decay"] = Patches[i].Envelope.Decay;
      patches_0_Envelope["Sustain"] = Patches[i].Envelope.Sustain;
      patches_0_Envelope["Release"] = Patches[i].Envelope.Release;

      JsonObject patches_0_Filter = patches_0["Filter"].to<JsonObject>();
      patches_0_Filter["FilterType"] = Patches[i].Filter.Type;
      patches_0_Filter["Cutoff"] = Patches[i].Filter.Cutoff;
      patches_0_Filter["Resonance"] = Patches[i].Filter.Resonance;

      JsonObject patches_0_LFO = patches_0["LFO"].to<JsonObject>();
      patches_0_LFO["Rate"] = Patches[i].LFO.Rate;
      patches_0_LFO["Amount"] = Patches[i].LFO.Amount;

      JsonObject patches_0_Mixer = patches_0["Mixer"].to<JsonObject>();
      patches_0_Mixer["VCO1Gain"] = Patches[i].Mixer.VCO1Gain;
      patches_0_Mixer["VCO2Gain"] = Patches[i].Mixer.VCO2Gain;
      patches_0_Mixer["VCO3Gain"] = Patches[i].Mixer.VCO3Gain;
      patches_0_Mixer["NoiseGain"] = Patches[i].Mixer.NoiseGain;
    }

    String output;

    doc.shrinkToFit();  // optional

    serializeJson(doc, output);
    File outputFile = SD.open(_filename.c_str(), FILE_WRITE);
    if (outputFile) {
      outputFile.print(output.c_str());

      outputFile.close();
      return true;
    }
    return false;
  }

  bool is_loaded() {
    return _loadedSuccessfully;
  }
};

#endif