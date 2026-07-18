#include "PolyhymniaCore.hpp"
#include "Logger.hpp"
#include "SerialLogger.hpp"
#include "usb_serial.h"

PolyhymniaCore::PolyhymniaCore(AudioSynthWaveform *vco1,
                               AudioSynthWaveform *vco2,
                               AudioSynthWaveform *vco3, AudioMixer4 *mixer,
                               AudioEffectEnvelope *envelope,
                               AudioFilterLadder *filter,
                               AudioControlSGTL5000 *sgtl5000,
                               LoggerFactory factory)
    : _polyVCO1(vco1, 70, 76, 0.25, factory.CreateDefaultForContext("SCO 1")),
      _polyVCO2(vco2, 77, 78, 0.25, factory.CreateDefaultForContext("SCO 2")),
      _polyVCO3(vco3, 85, 86, 0.25, factory.CreateDefaultForContext("SCO 3")),
      _mixer(mixer, 20, 21, 22, 23, factory.CreateDefaultForContext("Mixer")),
      _envelope(envelope, 73, 80, 75, 72,
                factory.CreateDefaultForContext("Envelope")),
      _filter(filter, factory.CreateDefaultForContext("Filter")),
      _settings(SETTINGS_FILENAME) {
  _sgtl5000 = sgtl5000;
  _logger = factory.CreateDefaultForContext("PolyhymniaCore");
}

void PolyhymniaCore::Initialize() {
  ActionResult result = ACTION_SUCCESS;

  _logger->start_action("Synthesizer System Initialization", LOGLEVEL_DEBUG);

  if (_settings.is_loaded()) {
    _polyVCO1.Initialize(_settings.Patches[0].DCO1);
    _polyVCO2.Initialize(_settings.Patches[0].DCO2);
    _polyVCO3.Initialize(_settings.Patches[0].DCO3);
    _mixer.Initialize(_settings.Patches[0].Mixer);
    _envelope.Initialize(_settings.Patches[0].Envelope);
    _filter.Initialize(_settings.Patches[0].Filter);
  } else {
    result = ACTION_WARNING;
    _polyVCO1.Initialize();
    _polyVCO2.Initialize();
    _polyVCO3.Initialize();
    _mixer.Initialize();
    _envelope.Initialize();
    _filter.Initialize();
  }

  // Noise.amplitude(1.0);
  // LFO.begin(WAVEFORM_SINE);
  // LFO.amplitude(0.75);
  // LFO.frequency(10);
  // LFO.pulseWidth(0.15);

  _logger->end_action(result, LOGLEVEL_DEBUG);
}
void PolyhymniaCore::HandleMIDICC(uint8_t channel, uint8_t control,
                                  uint8_t value) {
  _polyVCO1.HandleMidiCC(control, value);
  _polyVCO2.HandleMidiCC(control, value);
  _polyVCO3.HandleMidiCC(control, value);
  _mixer.HandleMidiCC(control, value);
  _envelope.HandleMidiCC(control, value);
  _filter.HandleMidiCC(control, value);

  switch (control) {
    // LFO Rate (0 - 20 Hz)
  case 105:
    // LFO.frequency(20 * (value / 127));
    break;
  // LFO Amount
  case 106:
    // LFO.amplitude(1 * (value / 127));
    break;
  // Overall volume
  case 24:
    _sgtl5000->volume(value / 127);
    break;
  }
}

void PolyhymniaCore::HandleNoteOff(uint8_t channel, uint8_t note,
                                   uint8_t velocity) {
  _envelope.NoteOff();
}

void PolyhymniaCore::HandleNoteOn(uint8_t channel, uint8_t note,
                                  uint8_t velocity) {
  _polyVCO1.HandlePitchChange(note);
  _polyVCO1.HandleVelocityChange(velocity);
  _polyVCO2.HandlePitchChange(note);
  _polyVCO2.HandleVelocityChange(velocity);
  _polyVCO3.HandlePitchChange(note);
  _polyVCO3.HandleVelocityChange(velocity);
  // Noise.amplitude(velocity / 127);

  _envelope.NoteOn();
}

void PolyhymniaCore::Tick() {
  OscillatorState state = _hardwareCommunication.GetOscillatorState(2);
}