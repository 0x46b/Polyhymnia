#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>
#include "SynthEnvelope.hpp"
#include "SynthMixer.hpp"
#include "VCO.hpp"
#include "Settings.hpp"
#include "LadderFilter.hpp"
#include "SerialLogger.hpp"

// GUItool: begin automatically generated code
AudioSynthWaveform VCO3;     //xy=389.20001220703125,478.00001525878906
AudioSynthWaveform VCO1;     //xy=391.20001220703125,405.00001525878906
AudioSynthWaveform VCO2;     //xy=391.20001220703125,443.00001525878906
AudioSynthNoiseWhite Noise;  //xy=391.20001220703125,517.0000152587891
AudioSynthWaveform LFO;      //xy=394.20001220703125,614.0000152587891
AudioMixer4 VCOMixer;        //xy=569.2000122070312,420.00001525878906
AudioFilterLadder VCF;       //xy=728.2000122070312,494.00001525878906
AudioEffectEnvelope ADSR;    //xy=888.2000122070312,495.00001525878906
AudioOutputI2S i2s1;         //xy=1105.3999938964844,437.99998474121094
AudioOutputUSB usb2;         //xy=1109.2000122070312,548.0000152587891
AudioConnection patchCord1(VCO3, 0, VCOMixer, 2);
AudioConnection patchCord2(VCO1, 0, VCOMixer, 0);
AudioConnection patchCord3(VCO2, 0, VCOMixer, 1);
AudioConnection patchCord4(Noise, 0, VCOMixer, 3);
AudioConnection patchCord5(LFO, 0, VCF, 1);
AudioConnection patchCord6(VCOMixer, 0, VCF, 0);
AudioConnection patchCord7(VCF, ADSR);
AudioConnection patchCord8(ADSR, 0, i2s1, 0);
AudioConnection patchCord9(ADSR, 0, i2s1, 1);
AudioConnection patchCord10(ADSR, 0, usb2, 0);
AudioConnection patchCord11(ADSR, 0, usb2, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=965.2000122070312,582.0000152587891
// GUItool: end automatically generated code

// Global variables
VCO* PolyVCO1;
VCO* PolyVCO2;
VCO* PolyVCO3;
SynthMixer* Mixer;
SynthEnvelope* Envelope;
LadderFilter* Filter;
Settings settings(SETTINGS_FILENAME);
SerialLogger logger("Polyhymnia", CURRENT_LOGLEVEL);

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.x / Teensy LC have the LED on pin 13
const int ledPin = 13;
const int chipSelect = BUILTIN_SDCARD;

void dump_crash_report(){
  if (CrashReport) {
    if (SD.begin(chipSelect)) {
      /* FILE_WRITE will append to end of the file */
      File logFile = SD.open("crashlog.txt", FILE_WRITE);
      if (logFile) {
        logFile.print(CrashReport);
        logFile.close();
      }
    }
    Serial.print(CrashReport);
  }
}

void initialize_audio_system() {
  logger.start_action("Audio System Initialization", LOGLEVEL_DEBUG);
  AudioMemory(20);
  usbMIDI.setHandleControlChange(handleCC);
  usbMIDI.setHandleNoteOff(handleNoteOff);
  usbMIDI.setHandleNoteOn(handleNoteOn);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);
  logger.end_action(ACTION_RESULT_SUCCESS, LOGLEVEL_DEBUG);
}

void initialize_synthesizer_system(Settings settings) {
  uint8_t result = ACTION_RESULT_SUCCESS;

  logger.start_action("Synthesizer System Initialization", LOGLEVEL_DEBUG);
  PolyVCO1 = new VCO(&VCO1, 70, 76, 0.25, "VCO 1");
  PolyVCO2 = new VCO(&VCO2, 77, 78, 0.25, "VCO 2");
  PolyVCO3 = new VCO(&VCO3, 85, 86, 0.25, "VCO 3");
  Mixer = new SynthMixer(&VCOMixer, 20, 21, 22, 23);
  Envelope = new SynthEnvelope(&ADSR, 73, 80, 75, 72);
  Filter = new LadderFilter(&VCF);

  if (settings.is_loaded()) {
    PolyVCO1->Initialize(settings.Patches[0].VCO1);
    PolyVCO2->Initialize(settings.Patches[0].VCO2);
    PolyVCO3->Initialize(settings.Patches[0].VCO3);
    Mixer->Initialize(settings.Patches[0].Mixer);
    Envelope->Initialize(settings.Patches[0].Envelope);
    Filter->Initialize(settings.Patches[0].Filter);
  } else {
    result = ACTION_RESULT_WARNING;
    PolyVCO1->Initialize();
    PolyVCO2->Initialize();
    PolyVCO3->Initialize();
    Mixer->Initialize();
    Envelope->Initialize();
    Filter->Initialize();
  }


  Noise.amplitude(1.0);
  LFO.begin(WAVEFORM_SINE);
  LFO.amplitude(0.75);
  LFO.frequency(10);
  LFO.pulseWidth(0.15);
  
  logger.end_action(result, LOGLEVEL_DEBUG);
}

bool initialize_sd_card() {
  uint8_t result = ACTION_RESULT_SUCCESS;
  String msg;
  logger.start_action("SD-card Initialization", LOGLEVEL_DEBUG);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    result = ACTION_RESULT_WARNING;
    msg = "SD-card could not get opened. Is an SD-card present? Is it formatted correctly? Is there a settings.json present?";
    return false;
  }

  logger.end_action(result, msg, LOGLEVEL_DEBUG);
  return true;
}

void intialize_settings() {
  uint8_t result = ACTION_RESULT_SUCCESS;
  String msg;

  logger.start_action("Loading settings", LOGLEVEL_DEBUG);
  if(!settings.LoadSettings()){
    result = ACTION_RESULT_WARNING;
    msg = "Could not load settings";
  }
  //logger.print_settings(settings);
  logger.end_action(result, msg, LOGLEVEL_DEBUG);
}

void setup() {
  Serial.begin(9600);
  // Wait for logger to connect
  while (!Serial) {}

  initialize_audio_system();

  if (initialize_sd_card()) {
    intialize_settings();
  }

  initialize_synthesizer_system(settings);

  logger.start_action("Setting status-led to ON", LOGLEVEL_DEBUG);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);  // set the LED on
  logger.end_action(ACTION_RESULT_SUCCESS, LOGLEVEL_DEBUG);
}

void loop() {
  usbMIDI.read();
}

void handleNoteOn(byte channel, byte note, byte velocity) {
  MIDI::PrintMidiNoteInfoToSerial("Received MIDI NoteOn: ", channel, note, velocity);
  PolyVCO1->HandlePitchChange(note);
  PolyVCO1->HandleVelocityChange(velocity);
  PolyVCO2->HandlePitchChange(note);
  PolyVCO2->HandleVelocityChange(velocity);
  PolyVCO3->HandlePitchChange(note);
  PolyVCO3->HandleVelocityChange(velocity);
  Noise.amplitude(velocity / 127);

  Envelope->NoteOn();
}

void handleNoteOff(byte channel, byte note, byte velocity) {
  MIDI::PrintMidiNoteInfoToSerial("Received MIDI NoteOff: ", channel, note, velocity);
  Envelope->NoteOff();
}

void handleCC(byte channel, byte control, byte value) {
  MIDI::PrintMidiCCInfoToSerial(channel, control, value);
  PolyVCO1->HandleMidiCC(control, value);
  PolyVCO2->HandleMidiCC(control, value);
  PolyVCO3->HandleMidiCC(control, value);
  Mixer->HandleMidiCC(control, value);
  Envelope->HandleMidiCC(control, value);
  Filter->HandleMidiCC(control, value);

  switch (control) {
      // LFO Rate (0 - 20 Hz)
    case 105:
      LFO.frequency(20 * (value / 127));
      break;
    // LFO Amount
    case 106:
      LFO.amplitude(1 * (value / 127));
      break;
    // Overall volume
    case 24:
      Serial.print("Changing volume to ");
      Serial.println(value / 127);
      sgtl5000_1.volume(value / 127);
      break;
  }
}
