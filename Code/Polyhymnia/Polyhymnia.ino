#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <ArduinoJson.h>
#include "SynthEnvelope.h"
#include "SynthMixer.h"
#include "VCO.h"
#include "Settings.h"
#include "LadderFilter.h"

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
Settings settings;

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.x / Teensy LC have the LED on pin 13
const int ledPin = 13;
const int chipSelect = BUILTIN_SDCARD;

void initialize_audio_system(){
  Serial.print("Initializing Audio System...");
  AudioMemory(20);
  usbMIDI.setHandleControlChange(handleCC);
  usbMIDI.setHandleNoteOff(handleNoteOff);
  usbMIDI.setHandleNoteOn(handleNoteOn);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);
  Serial.println("[OK]");
}

void initialize_synthesizer_system(Settings settings){
  Serial.print("Initializing synthesizer system...");
  PolyVCO1 = new VCO(&VCO1, 70, 76, 0.25);
  PolyVCO2 = new VCO(&VCO2, 77, 78, 0.25);
  PolyVCO3 = new VCO(&VCO3, 85, 86, 0.25);
  Mixer = new SynthMixer(&VCOMixer, 20, 21, 22, 23);
  Envelope = new SynthEnvelope(&ADSR, 73, 80, 75, 72);
  Filter = new LadderFilter(&VCF);

  PolyVCO1->Initialize();
  PolyVCO2->Initialize();
  PolyVCO3->Initialize();
  Mixer->Initialize();
  Envelope->Initialize();
  Filter->Initialize();

  Noise.amplitude(1.0);
  LFO.begin(WAVEFORM_SINE);
  LFO.amplitude(0.75);
  LFO.frequency(10);
  LFO.pulseWidth(0.15);
  Serial.println("[OK]");
}

bool initialize_sd_card(){
  Serial.print("Initializing SD-card...");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("[FAILED]: Card failed, or not present");
    return false;
  }

  Serial.println("[OK]");
  return true;
}

void intialize_settings(){
  Serial.print("Loading settings...");
  settings.LoadSettings();
  settings.print_settings_to_serial();
  Serial.println("[OK]");
}  

void setup() {
  Serial.begin(9600);
  // Wait for serial to connect
  while (!Serial) {}

  initialize_audio_system();
  
  if(initialize_sd_card()) {
    intialize_settings();  
  }

  initialize_synthesizer_system(Settings settings);

  Serial.print("Setting status-led to communicate ready...");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);  // set the LED on
  Serial.println("[OK]");

  Serial.println("Initializing [Done]");
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
