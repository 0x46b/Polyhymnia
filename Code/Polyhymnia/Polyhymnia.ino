#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

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

const float DIV127 = (1.0 / 127.0);

// Class-Definitions
class MIDI {
private:
  // MIDI-value to note lookup
  const float midiToFrequency[128] = { 8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568,
                                       15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5,
                                       29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913,
                                       55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826,
                                       110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998,
                                       207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994,
                                       391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456,
                                       739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51,
                                       1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318,
                                       2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922,
                                       4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018,
                                       8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85 };

public:
  float MidiToFrequency(int midiValue) {
    if (midiValue < 0 || midiValue > 127) {
      return 0;
    }

    return midiToFrequency[midiValue];
  }

  static float MidiValueToValue(byte value, float maxValue, float offset) {
    return offset + maxValue * (value * DIV127);
  }


  static void PrintMidiNoteInfoToSerial(const String& msg, byte channel, byte note, byte velocity) {
    Serial.printf("%s Channel: %i Note: %i Velocity: %i\n", msg, channel, note, velocity);
  }


  static void PrintMidiCCInfoToSerial(byte channel, byte control, byte value) {
    Serial.printf("%s Channel: %i CC: %i Value: %i\n", channel, control, value);
  }
};

class VCO {
private:
  const short DEFAULT_TYPE = WAVEFORM_SAWTOOTH;
  float _current_detune = 0;
  float _maxVolume = 1.0;
  AudioSynthWaveform* _teensyVCO;
  MIDI _midi;

  // Waveform lookup
  // Note: Noise is not generated through the VCO1, so we had to handle it separately
  const short _waveformLookup[4] = { WAVEFORM_SAWTOOTH, WAVEFORM_TRIANGLE, WAVEFORM_SQUARE, WAVEFORM_SINE };
  byte _detuneChangeMidiCC;
  byte _typeChangeMidiCC;

  void PrintWaveformChangeToSerial(int waveform) {
    switch(waveform) {
        case 0:
          Serial.println("WaveformChange: Sawtooth\n");
          break;
        case 1:
          Serial.println("WaveformChange: Triangle\n");
          break;
        case 2:
          Serial.println("WaveformChange: Square\n");
          break;
        case 4:
          Serial.println("WaveformChange: Sine\n");
          break;
        default:
          Serial.println("WaveformChange: UNKNOWN\n");
      }
  }

public:
  VCO(AudioSynthWaveform* vco, int typeChangeMidiCC, int detuneChangeMidiCC, float maxVolume)
    : _midi() {
    this->_teensyVCO = vco;
    this->_maxVolume = maxVolume;
    this->_detuneChangeMidiCC = detuneChangeMidiCC;
    this->_typeChangeMidiCC = typeChangeMidiCC;
  }

  void Initialize() {
    _teensyVCO->begin(_maxVolume, _midi.MidiToFrequency(60), DEFAULT_TYPE);
  }

  void SwitchVCO1Waveform(int waveform) {
    PrintWaveformChangeToSerial(waveform);
    _teensyVCO->begin(waveform);
  }

  void HandleMidiCC(byte cc, byte value) {
    if (cc == _typeChangeMidiCC) {
      this->HandleTypeChange(value);
    }

    if (cc == _detuneChangeMidiCC) {
      this->HandleDetuneChange(value);
    }
  }

  void HandleTypeChange(byte waveformId) {
    if (waveformId < 0 || waveformId > 3) {
      waveformId = 0;
    }

    _teensyVCO->begin(_waveformLookup[waveformId]);
  }

  void HandlePitchChange(byte midiValue) {
    float frequency = _midi.MidiToFrequency(midiValue);
    Serial.printf("PitchChange: %f\n", frequency);
    _teensyVCO->frequency(frequency + _current_detune);
  }

  void HandleVelocityChange(byte velocity) {
    Serial.printf("VelocityChange: %i\n", velocity);
    _teensyVCO->amplitude(velocity * DIV127);
  }

  void HandleDetuneChange(byte detune) {
    // TODO
    Serial.printf("(NotImplementedYet)DetuneChange: %i\n", detune);
  }
};

class SynthMixer {
private:
  AudioMixer4* _teensyMixer;
  float _vco1Volume;
  float _vco2Volume;
  float _vco3Volume;
  float _noiseVolume;

  byte _vco1CC;
  byte _vco2CC;
  byte _vco3CC;
  byte _noiseCC;

  float CalculatePercentage(byte quantity, float total) {
    // Avoid dividing by zero
    if (total == 0) {
      if (quantity == 0) {
        total = quantity;
      } else {
        return 1;
      }
    }

    return 1 / total * quantity;
  }

  // We had to make sure total gain is never over 1, so calculate the percentage of each volume and apply it as gain
  /*
    Channels:
      0 = VCO1
      1 = VCO2
      2 = VCO3
      3 = Noise
  */
  void UpdateVolumes() {
    int totalVolumes = this->_vco1Volume + this->_vco2Volume + this->_vco3Volume + this->_noiseVolume;

    float vco1gain = CalculatePercentage(this->_vco1Volume, totalVolumes);
    Serial.printf("Setting VCO1 gain to %f\n", vco1gain);
    this->_teensyMixer->gain(0, vco1gain);

    float vco2gain = CalculatePercentage(this->_vco2Volume, totalVolumes);
    Serial.printf("Setting VCO2 gain to %f\n", vco2gain);
    this->_teensyMixer->gain(1, vco2gain);

    float vco3gain = CalculatePercentage(this->_vco3Volume, totalVolumes);
    Serial.printf("Setting VCO3 gain to %f\n", vco3gain);
    this->_teensyMixer->gain(2, vco3gain);

    float noisegain = CalculatePercentage(this->_noiseVolume, totalVolumes);
    Serial.printf("Setting Noise gain to %f\n", noisegain);
    this->_teensyMixer->gain(3, noisegain);
  }

public:
  SynthMixer(AudioMixer4* teensyMixer, byte vco1CC, byte vco2CC, byte vco3CC, byte noiseCC) {
    this->_teensyMixer = teensyMixer;
    this->_vco1CC = vco1CC;
    this->_vco2CC = vco2CC;
    this->_vco3CC = vco3CC;
    this->_noiseCC = noiseCC;
  }

  void Initialize() {
    this->_vco1Volume = 42;
    this->_vco2Volume = 42;
    this->_vco3Volume = 42;
    this->UpdateVolumes();
  }

  void SetVCOVolume(int vcoNumber, byte volume) {

    switch (vcoNumber) {
      case 0:
        this->_vco1Volume = volume;
        Serial.printf("Changing volume of VCO1 to %f\n", volume);
        break;
      case 1:
        this->_vco2Volume = volume;
        Serial.printf("Changing volume of VCO2 to %f\n", volume);
        break;
      case 2:
        this->_vco3Volume = volume;
        Serial.printf("Changing volume of VCO3 to %f\n", volume);
        break;
      case 3:
        this->_noiseVolume = volume;
        Serial.printf("Changing volume of Noise to %f\n", volume);
        break;
    }
    this->UpdateVolumes();
  }

  void HandleMidiCC(byte cc, byte value) {
    if (cc == this->_vco1CC) {
      this->SetVCOVolume(0, value);
    }
    if (cc == this->_vco2CC) {
      this->SetVCOVolume(1, value);
    }
    if (cc == this->_vco3CC) {
      this->SetVCOVolume(2, value);
    }
    if (cc == this->_noiseCC) {
      this->SetVCOVolume(3, value);
    }
  }
};

class SynthEnvelope {
private:
  AudioEffectEnvelope* _teensyEnvelope;
  byte _attackCC;
  byte _decayCC;
  byte _sustainCC;
  byte _releaseCC;
  // 11800ms = 1.96s
  const float MAX_ATTACK_IN_MS = 3000;
  // 11800ms = 1.96s
  const float MAX_DECAY_IN_MS = 3000;
  // 11800ms = 1.96s
  const float MAX_RELEASE_IN_MS = 3000;


public:
  SynthEnvelope(AudioEffectEnvelope* teensyEnvelope, byte attackCC, byte decayCC, byte sustainCC, byte releaseCC) {
    this->_teensyEnvelope = teensyEnvelope;
    this->_attackCC = attackCC;
    this->_decayCC = decayCC;
    this->_sustainCC = sustainCC;
    this->_releaseCC = releaseCC;
  }

  void Initialize() {
    this->_teensyEnvelope->attack(0);
    this->_teensyEnvelope->decay(35);
    this->_teensyEnvelope->hold(0);
    this->_teensyEnvelope->sustain(1);
    this->_teensyEnvelope->release(300);
  }

  void HandleMidiCC(byte cc, byte value) {
    // Attack (0 - 11880)
    if (cc == this->_attackCC) {
      float attack = MAX_ATTACK_IN_MS * value * DIV127;
      Serial.print("Changing attack to ");
      Serial.print(attack);
      Serial.println("ms");
      this->_teensyEnvelope->attack(attack);
    }
    // Decay (0 - 11880)
    if (cc == this->_decayCC) {
      float decay = MAX_DECAY_IN_MS * (value * DIV127);
      Serial.print("Changing decay to ");
      Serial.print(MAX_DECAY_IN_MS * value * DIV127);
      Serial.println("ms");
      this->_teensyEnvelope->decay(decay);
    }
    // Sustain (0 - 1.0)
    if (cc == this->_sustainCC) {
      float sustain = value * DIV127;
      Serial.print("Changing sustain to ");
      Serial.println(sustain);
      Serial.println("ms");
      this->_teensyEnvelope->sustain(sustain);
    }
    // Release (0 - 11880)
    if (cc == this->_releaseCC) {
      float release = MAX_RELEASE_IN_MS * value * DIV127;
      Serial.print("Changing release to ");
      Serial.print(release);
      Serial.println("ms");
      this->_teensyEnvelope->release(release);
    }
  }

  void NoteOn() {
    Serial.println("Envelope: NoteOn");
    this->_teensyEnvelope->noteOn();
  }

  void NoteOff() {
    Serial.println("Envelope: NoteOff");
    this->_teensyEnvelope->noteOff();
  }
};

// Global variables
VCO* PolyVCO1;
VCO* PolyVCO2;
VCO* PolyVCO3;
SynthMixer* Mixer;
SynthEnvelope* Envelope;
// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.x / Teensy LC have the LED on pin 13
const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  AudioMemory(20);
  usbMIDI.setHandleControlChange(handleCC);
  usbMIDI.setHandleNoteOff(handleNoteOff);
  usbMIDI.setHandleNoteOn(handleNoteOn);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);

  PolyVCO1 = new VCO(&VCO1, 70, 76, 0.25);
  PolyVCO2 = new VCO(&VCO2, 77, 78, 0.25);
  PolyVCO3 = new VCO(&VCO3, 85, 86, 0.25);
  Mixer = new SynthMixer(&VCOMixer, 20, 21, 22, 23);
  Envelope = new SynthEnvelope(&ADSR, 73, 80, 75, 72);

  PolyVCO1->Initialize();
  PolyVCO2->Initialize();
  PolyVCO3->Initialize();
  Mixer->Initialize();
  Envelope->Initialize();

  Noise.amplitude(1.0);
  LFO.begin(WAVEFORM_SINE);
  LFO.amplitude(0.75);
  LFO.frequency(10);
  LFO.pulseWidth(0.15);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);  // set the LED on
}

void loop() {
  usbMIDI.read();
}

float calculateCutoff(byte midiValue) {
  // TODO: Add potentially LFO
  return MIDI::MidiValueToValue(midiValue, 20000, 0);
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

  switch (control) {
    // Cutoff (16Hz - 20 kHz)
    case 74:
      VCF.frequency(calculateCutoff(value));
      break;
    // Resonance (value Range from 0 - 1.8, everything over 1 self-resonates)
    case 71:
      VCF.resonance(1.8 * (value / 127));
      break;

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
