#include "SynthEnvelope.hpp"
#include "Logger.hpp"
#include "SerialLogger.hpp"

SynthEnvelope::SynthEnvelope(AudioEffectEnvelope *teensyEnvelope,
                             uint8_t attackCC, uint8_t decayCC,
                             uint8_t sustainCC, uint8_t releaseCC,
                             Logger *logger) {
  this->_teensyEnvelope = teensyEnvelope;
  this->_attackCC = attackCC;
  this->_decayCC = decayCC;
  this->_sustainCC = sustainCC;
  this->_releaseCC = releaseCC;
  this->_logger = logger;
}

SynthEnvelope::~SynthEnvelope(void) { free(_logger); }

void SynthEnvelope::Initialize(void) {
  _logger->println("Initializing envelope with default values", LOGLEVEL_DEBUG);
  this->_teensyEnvelope->attack(0);
  this->_teensyEnvelope->decay(35);
  this->_teensyEnvelope->hold(0);
  this->_teensyEnvelope->sustain(1);
  this->_teensyEnvelope->release(300);
}

void SynthEnvelope::Initialize(EnvelopeSetting setting) {
  _logger->println("Initializing envelope with loaded settings",
                   LOGLEVEL_DEBUG);
  this->_teensyEnvelope->attack(setting.Attack);
  this->_teensyEnvelope->decay(setting.Decay);
  this->_teensyEnvelope->hold(0);
  this->_teensyEnvelope->sustain(setting.Sustain);
  this->_teensyEnvelope->release(setting.Release);
}

void SynthEnvelope::HandleMidiCC(byte cc, byte value) {
  // Attack (0 - 11880)
  if (cc == this->_attackCC) {
    float attack = MAX_ATTACK_IN_MS * value * DIV127;
    _logger->print("Changing attack to ", LOGLEVEL_INFO);
    _logger->print(attack, LOGLEVEL_INFO);
    _logger->println("ms", LOGLEVEL_INFO);
    this->_teensyEnvelope->attack(attack);
  }
  // Decay (0 - 11880)
  if (cc == this->_decayCC) {
    float decay = MAX_DECAY_IN_MS * (value * DIV127);
    _logger->print("Changing decay to ", LOGLEVEL_INFO);
    _logger->print(MAX_DECAY_IN_MS * value * DIV127, LOGLEVEL_INFO);
    _logger->println("ms", LOGLEVEL_INFO);
    this->_teensyEnvelope->decay(decay);
  }
  // Sustain (0 - 1.0)
  if (cc == this->_sustainCC) {
    float sustain = value * DIV127;
    _logger->print("Changing sustain to ", LOGLEVEL_INFO);
    _logger->println(sustain, LOGLEVEL_INFO);
    _logger->println("ms", LOGLEVEL_INFO);
    this->_teensyEnvelope->sustain(sustain);
  }
  // Release (0 - 11880)
  if (cc == this->_releaseCC) {
    float release = MAX_RELEASE_IN_MS * value * DIV127;
    _logger->print("Changing release to ", LOGLEVEL_INFO);
    _logger->print(release, LOGLEVEL_INFO);
    _logger->println("ms", LOGLEVEL_INFO);
    this->_teensyEnvelope->release(release);
  }
}

void SynthEnvelope::NoteOn(void) {
  _logger->println("Envelope: NoteOn", LOGLEVEL_INFO);
  this->_teensyEnvelope->noteOn();
}

void SynthEnvelope::NoteOff(void) {
  _logger->println("Envelope: NoteOff", LOGLEVEL_INFO);
  this->_teensyEnvelope->noteOff();
}