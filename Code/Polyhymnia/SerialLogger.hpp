#ifndef SERIAL_LOGGER_HPP
#include "Settings.h"
#include "Constants.h"

class Logger {
protected:
  String _context;
  uint8_t _logLevel;

public:
  Logger(String context, uint8_t logLevel) {
    _context = context;
    _logLevel = logLevel;
  }
  virtual void println(const char* msg, uint8_t logLevel) = 0;
  virtual void print(const char* msg, uint8_t logLevel) = 0;
  virtual void print_float(float number, uint8_t logLevel) = 0;
  virtual void sprintf(const char* msg, ...) = 0;
  virtual void print_settings(Settings settings, uint8_t logLevel) =0;
  virtual void print_envelope_settings(EnvelopeSetting envelope, uint8_t logLevel) =0;
  virtual void print_vco_settings(VCOSetting vco, uint8_t logLevel)=0;
  virtual void print_lfo_settings(LFOSetting lfo, uint8_t logLevel)=0;
  virtual void print_patch_settings(PatchSetting patch, uint8_t logLevel)=0;
  virtual void print_mixer_settings(MixerSetting mixer, uint8_t logLevel)=0;
};

class SerialLogger : public Logger {
public:
  SerialLogger(String context, uint8_t logLevel)
    : Logger(context, logLevel) {
  }

  void println(const char* msg, uint8_t logLevel) {
    if(_logLevel <= logLevel) {
      return;
    }

    Serial.printf("[%s] : %s\n", _context.c_str(), msg);
  }

  void print(const char* msg, uint8_t logLevel) {
    if(_logLevel <= logLevel) {
      return;
    }

    Serial.printf("[%s] : %s", _context.c_str(), msg);
  }

  void print_float(float number, uint8_t logLevel) {
    if(_logLevel <= logLevel) {
      return;
    }
    char buff[10];
    dtostrf(number, 1, 0, buff);

    Serial.printf("[%s] : %s\n", _context.c_str(), buff);
  }

  void sprintf(const char* msg, ...) {
    // va_list args;
    // va_start(args, msg);
    // vsprintf(msg, args);
    // va_end(args);
  }

  void print_vco_settings(VCOSetting vco, uint8_t logLevel){
    if(_logLevel <= logLevel) {
      return;
    }

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

  void print_envelope_settings(EnvelopeSetting envelope, uint8_t logLevel){
    if(_logLevel <= logLevel) {
      return;
    }

    Serial.print("\t\t\tAttack: ");
    Serial.println(envelope.Attack);
    Serial.print("\t\t\tDecay: ");
    Serial.println(envelope.Decay);
    Serial.print("\t\t\tSustain: ");
    Serial.println(envelope.Sustain);
    Serial.print("\t\t\tRelease: ");
    Serial.println(envelope.Release);
  }

  void print_lfo_settings(LFOSetting lfo, uint8_t logLevel){
    if(_logLevel <= logLevel) {
      return;
    }

    Serial.print("\t\t\tRate: ");
    Serial.println(lfo.Rate);
    Serial.print("\t\t\tAmount: ");
    Serial.println(lfo.Amount);
  }

  void print_mixer_settings(MixerSetting mixer, uint8_t logLevel){
    if(_logLevel <= logLevel) {
      return;
    }

    Serial.print("\t\t\tVCO1Gain: ");
    Serial.println(mixer.VCO1Gain);
    Serial.print("\t\t\tVCO2Gain: ");
    Serial.println(mixer.VCO2Gain);
    Serial.print("\t\t\tVCO3Gain: ");
    Serial.println(mixer.VCO3Gain);
    Serial.print("\t\t\tNoise: ");
    Serial.println(mixer.NoiseGain);
  }

  void print_patch_settings(PatchSetting patch, uint8_t logLevel){
    if(_logLevel <= logLevel) {
      return;
    }

    Serial.print("\tName: ");
    Serial.println(patch.Name);
    Serial.println("\t\tVCO1: ");
    print_vco_settings(patch.VCO1, logLevel);
    Serial.println("\t\tVCO2: ");
    print_vco_settings(patch.VCO2, logLevel);
    Serial.println("\t\tVCO3: ");
    print_vco_settings(patch.VCO3, logLevel);
    Serial.println("\t\tEnvelope: ");
    print_envelope_settings(patch.Envelope, logLevel);
    Serial.println("\t\tLFO: ");
    print_lfo_settings(patch.LFO, logLevel);
    Serial.println("\t\tMixer: ");
    print_mixer_settings(patch.Mixer, logLevel);
  }

  void print_settings(Settings settings, uint8_t logLevel) {
    if(_logLevel <= logLevel) {
      return;
    }

    Serial.println("System: ");
    Serial.print("\tShowBootscreen: ");
    if(settings.System.ShowBootscreen){
      Serial.println("true");
    }else{
      Serial.println("false");
    }
    Serial.print("\tBootscreenFilepath: ");
    Serial.println(settings.System.BootscreenFilepath);
    Serial.print("\tMIDI channel: ");
    Serial.println(settings.System.MidiChannel);
    print_patch_settings(settings.Patches[0], logLevel);
    print_patch_settings(settings.Patches[1], logLevel);
  }
};
#define SERIAL_LOGGER_HPP
#endif