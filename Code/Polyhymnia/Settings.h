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

    return true;
  }

  void print_vco_info_to_serial(VCOSetting vco){
    Serial.print("\t\t\tType: ");
    switch(vco.Type){
      case 0:
        Serial.println("SAWTOOTH");
        break;
      case 1:
        Serial.println("SQUARE");
        break;
      case 2:
        Serial.println("TRIANGLE");
        break;
      case 3:
        Serial.println("SINE");
        break;
    }
    Serial.print("\t\t\tDetune: ");
    Serial.println(vco.Detune);
  }

  void print_envelope_filter_to_serial(EnvelopeSetting envelope){
    Serial.print("\t\t\tAttack: ");
    Serial.println(envelope.Attack);
    Serial.print("\t\t\tDecay: ");
    Serial.println(envelope.Decay);
    Serial.print("\t\t\tSustain: ");
    Serial.println(envelope.Sustain);
    Serial.print("\t\t\tRelease: ");
    Serial.println(envelope.Release);
  }

  void print_lfo_to_serial(LFOSetting lfo){
    Serial.print("\t\t\tRate: ");
    Serial.println(lfo.Rate);
    Serial.print("\t\t\tAmount: ");
    Serial.println(lfo.Amount);
  }

  void print_mixer_to_serial(MixerSetting mixer){
    Serial.print("\t\t\tVCO1Gain: ");
    Serial.println(mixer.VCO1Gain);
    Serial.print("\t\t\tVCO2Gain: ");
    Serial.println(mixer.VCO2Gain);
    Serial.print("\t\t\tVCO3Gain: ");
    Serial.println(mixer.VCO3Gain);
    Serial.print("\t\t\tNoise: ");
    Serial.println(mixer.NoiseGain);
  }

  void print_patch_info_to_serial(PatchSetting patch){
    Serial.print("\tName: ");
    Serial.println(patch.Name);
    Serial.println("\t\tVCO1: ");
    print_vco_info_to_serial(patch.VCO1);
    Serial.println("\t\tVCO2: ");
    print_vco_info_to_serial(patch.VCO2);
    Serial.println("\t\tVCO3: ");
    print_vco_info_to_serial(patch.VCO3);
    Serial.println("\t\tEnvelope: ");
    print_envelope_filter_to_serial(patch.Envelope);
    Serial.println("\t\tLFO: ");
    print_lfo_to_serial(patch.LFO);
    Serial.println("\t\tMixer: ");
    print_mixer_to_serial(patch.Mixer);
  }

  void print_settings_to_serial() {
    Serial.println("Loaded settings: ");
    Serial.println("System: ");
    Serial.print("\tShowBootscreen: ");
    if(System.ShowBootscreen){
      Serial.println("true");
    }else{
      Serial.println("false");
    }
    Serial.print("\tBootscreenFilepath: ");
    Serial.println(System.BootscreenFilepath);
    Serial.print("\tMIDI channel: ");
    Serial.println(System.MidiChannel);
    print_patch_info_to_serial(Patches[0]);
    print_patch_info_to_serial(Patches[1]);
  }
};

#endif