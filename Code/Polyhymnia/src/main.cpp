
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

#include "HardwareInterfaceCommunication.h"
#include "Logger.hpp"
#include "PolyhymniaCore.hpp"
#include "SerialLogger.hpp"
#include "Settings.hpp"
#include "version.h"

// GUItool: begin automatically generated code
AudioSynthWaveform VCO3;    // xy=389.20001220703125,478.00001525878906
AudioSynthWaveform VCO1;    // xy=391.20001220703125,405.00001525878906
AudioSynthWaveform VCO2;    // xy=391.20001220703125,443.00001525878906
AudioSynthNoiseWhite Noise; // xy=391.20001220703125,517.0000152587891
AudioSynthWaveform LFO;     // xy=394.20001220703125,614.0000152587891
AudioMixer4 VCOMixer;       // xy=569.2000122070312,420.00001525878906
AudioFilterLadder VCF;      // xy=728.2000122070312,494.00001525878906
AudioEffectEnvelope ADSR;   // xy=888.2000122070312,495.00001525878906
AudioOutputI2S i2s1;        // xy=1105.3999938964844,437.99998474121094
AudioOutputUSB usb2;        // xy=1109.2000122070312,548.0000152587891
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
AudioControlSGTL5000 sgtl5000_1; // xy=965.2000122070312,582.0000152587891
// GUItool: end automatically generated code

// Global variables
LoggerFactory _loggerFactory((Stream *)&Serial, LOGLEVEL_DEBUG);
Logger *_logger;
PolyhymniaCore core(&VCO1, &VCO2, &VCO3, &VCOMixer, &ADSR, &VCF, &sgtl5000_1,
                    _loggerFactory);

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.x / Teensy LC have the LED on pin 13
const int ledPin = 13;
const int chipSelect = BUILTIN_SDCARD;

void handleMidiCC(uint8_t channel, uint8_t control, uint8_t value) {
  core.HandleMIDICC(channel, control, value);
}

void handleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  core.HandleNoteOff(channel, note, velocity);
}

void handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  core.HandleNoteOn(channel, note, velocity);
}

void initialize_audio_system() {
  _logger->start_action("Audio System Initialization", LOGLEVEL_DEBUG);
  AudioMemory(20);
  usbMIDI.setHandleControlChange(handleMidiCC);
  usbMIDI.setHandleNoteOff(handleNoteOff);
  usbMIDI.setHandleNoteOn(handleNoteOn);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);
  _logger->end_action(ACTION_SUCCESS, LOGLEVEL_DEBUG);
}

void initialize_synthesizer_system(Settings settings) {}

bool initialize_sd_card() {
  ActionResult result = ACTION_SUCCESS;
  String msg;
  _logger->start_action("SD-card Initialization", LOGLEVEL_DEBUG);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    result = ACTION_WARNING;
    msg = "SD-card could not get opened. Is an SD-card present? Is it "
          "formatted correctly? Is there a settings.json present?";
    return false;
  }

  _logger->end_action(result, msg.c_str(), LOGLEVEL_DEBUG);
  return true;
}

// void intialize_settings() {
//   uint8_t result = ACTION_SUCCESS;
//   String msg;

//   _logger->start_action("Loading settings", DEBUG);
//   if (!settings.LoadSettings()) {
//     result = ACTION_WARNING;
//     msg = "Could not load settings";
//   }
//   // _logger->print_settings(settings);
//   _logger->end_action(result, msg.c_str(), DEBUG);
// }

// void initialize_hardware_communication() {
//   _logger->start_action("Initializing hardware-communication", DEBUG);
//   hardwareCommunication.Initialize(&SPI);
//   _logger->end_action(ACTION_SUCCESS, DEBUG);
// }

void setup() {
  Serial.begin(9600);

  _logger = _loggerFactory.CreateDefaultForContext("Main");
  // Wait for logger to connect
  while (!Serial) {
  }

  Serial.print("Polyhymnia v");
  Serial.println(_VERSION);

  initialize_audio_system();

  // if (initialize_sd_card()) {
  //   intialize_settings();
  // }

  // initialize_synthesizer_system(settings);
  // initialize_hardware_communication();
  // _logger->start_action("Setting status-led to ON", DEBUG);
  // pinMode(ledPin, OUTPUT);
  // digitalWrite(ledPin, HIGH);  // set the LED on
  // _logger->end_action(ACTION_SUCCESS, DEBUG);
}

void loop() {
  usbMIDI.read();
  core.Tick();
}
