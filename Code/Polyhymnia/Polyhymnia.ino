#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>

class Synthesizer {
private:
  // MIDI-value to note lookup
  const float midiToFrequency[128] = { 8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85 };

  float current_detune_1 = 0;
  AudioSynthWaveform VCO1;
  AudioSynthWaveform VCO2;
  AudioSynthNoiseWhite noise;
  AudioMixer4 VCOMixer;

public:
  void SwitchToNoise() {
    VCOMixer.gain(0, 0);
    VCOMixer.gain(1, 0);
    VCOMixer.gain(2, 1);
  }

  void SwitchVCO1Waveform(int waveform) {
    VCO1.begin(waveform);
  }

  void SwitchVCO2Waveform(int waveform) {
    VCO2.begin(waveform);
  }

  void PlayNote(byte note, byte velocity) {
    if (note > 23 && note < 108) {
      float noteFrequency = midiToFrequency[note];
      VCO1.frequency(noteFrequency + current_detune_1);
      VCO1.amplitude(velocity / 127);
    }
  }
};

// GUItool: begin automatically generated code
AudioSynthWaveform VCO2;       //xy=99,69
AudioSynthWaveform VCO1;       //xy=101,32
AudioSynthNoiseWhite noise1;   //xy=101,127
AudioSynthWaveform LFO;        //xy=102,178
AudioMixer4 VCOMixer;          //xy=277,46
AudioFilterLadder ladder1;     //xy=436,120
AudioEffectEnvelope envelope;  //xy=596,121
AudioOutputI2S Headphones;     //xy=793,123
AudioConnection patchCord1(VCO2, 0, VCOMixer, 1);
AudioConnection patchCord2(VCO1, 0, VCOMixer, 0);
AudioConnection patchCord3(noise1, 0, VCOMixer, 2);
AudioConnection patchCord4(VCOMixer, 0, ladder1, 0);
AudioConnection patchCord5(ladder1, envelope);
AudioConnection patchCord6(envelope, 0, Headphones, 0);
AudioConnection patchCord7(envelope, 0, Headphones, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=673,208
// GUItool: end automatically generated code

// Waveform lookup
// Note: Noise is not generated through the VCO1, so we had to handle it separately
const int waveFormLookup[4] = { WAVEFORM_SAWTOOTH, WAVEFORM_TRIANGLE, WAVEFORM_SQUARE, WAVEFORM_SINE };

void setup() {
  // put your setup code here, to run once:
  AudioMemory(20);
  usbMIDI.setHandleControlChange(handleCC);
  usbMIDI.setHandleNoteOff(handleNoteOff);
  usbMIDI.setHandleNoteOn(handleNoteOn);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);

  VCO1.begin(0.5, 82.41, WAVEFORM_SAWTOOTH);
  VCO2.begin(0.5, 82.41, WAVEFORM_SAWTOOTH);

  LFO.begin(WAVEFORM_SINE);
  LFO.amplitude(0.75);
  LFO.frequency(10);
  LFO.pulseWidth(0.15);
}

void loop() {
  // put your main code here, to run repeatedly:
  usbMIDI.read();
}

float calculateCutoff(byte midiValue) {
  // TODO: Add potentially LFO
  return 20000 * (midiValue / 127);
}

void handleNoteOn(byte channel, byte note, byte velocity) {
  envelope.noteOn();
}

void handleNoteOff(byte channel, byte note, byte velocity) {
  envelope.noteOff();
}
void handleCC(byte channel, byte control, byte value) {
  switch (control) {
    // Cutoff (16Hz - 20 kHz)
    case 74:
      ladder1.frequency(calculateCutoff(value));
      break;
    // Resonance (value Range from 0 - 1.8, everything over 1 self-resonates)
    case 71:
      ladder1.resonance(1.8 * (value / 127));
      break;

    // Attack (0 - 11880)
    case 73:
      envelope.attack(11800 * (value / 127));
      break;
    // Decay (0 - 11880)
    case 80:
      envelope.decay(11800 * (value / 127));
      break;
    // Sustain (0 - 1.0)
    case 75:
      envelope.sustain(value / 127);
      break;
    // Release (0 - 11880)
    case 72:
      envelope.release(11800 * (value / 127));
      break;

    // Waveform (0 = Saw, 1 = Triangle, 2 = Pulse, 3 = Sine, 4 = Noise)
    case 70:
      if (value < 0 || value > 4) {
        // Channels:
        // 0 VCO1
        // 1 VCO2
        // 2 Noise
        // Shutoff VCOs
        VCOMixer.gain(0, 0);
        VCOMixer.gain(1, 0);
        VCOMixer.gain(2, 1.0);
        break;
      } else {
        // Shutoff noise and enable VCOs
        VCOMixer.gain(0, 0.5);
        VCOMixer.gain(1, 0.5);
        VCOMixer.gain(2, 0);
      }
      VCO1.begin(waveFormLookup[value]);
      break;
    // Detune
    case 94:
      break;
    // LFO Rate (0 - 20 Hz)
    case 3:
      LFO.frequency(20 * (value / 127));
      break;
    // LFO Amount
    case 9:
      LFO.amplitude(1 * (value / 127));
      break;
  }
}
