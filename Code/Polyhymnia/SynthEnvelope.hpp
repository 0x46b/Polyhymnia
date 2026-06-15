#ifndef SYNTHENVELOPE_H
#define SYNTHENVELOPE_H

#include "Constants.hpp"
#include "SerialLogger.hpp"
#include "Settings.hpp"

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

  SerialLogger _logger;


public:
  SynthEnvelope(AudioEffectEnvelope* teensyEnvelope, byte attackCC, byte decayCC, byte sustainCC, byte releaseCC)
  : _logger("Envelope", CURRENT_LOGLEVEL) {
    this->_teensyEnvelope = teensyEnvelope;
    this->_attackCC = attackCC;
    this->_decayCC = decayCC;
    this->_sustainCC = sustainCC;
    this->_releaseCC = releaseCC;
  }

  void Initialize() {
    _logger.println("Initializing envelope with default values", LOGLEVEL_DEBUG);
    this->_teensyEnvelope->attack(0);
    this->_teensyEnvelope->decay(35);
    this->_teensyEnvelope->hold(0);
    this->_teensyEnvelope->sustain(1);
    this->_teensyEnvelope->release(300);
  }

  void Initialize(EnvelopeSetting setting) {
    _logger.println("Initializing envelope with loaded settings", LOGLEVEL_DEBUG);
    this->_teensyEnvelope->attack(setting.Attack);
    this->_teensyEnvelope->decay(setting.Decay);
    this->_teensyEnvelope->hold(0);
    this->_teensyEnvelope->sustain(setting.Sustain);
    this->_teensyEnvelope->release(setting.Release);
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

#endif