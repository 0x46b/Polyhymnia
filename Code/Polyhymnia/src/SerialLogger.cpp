#include "SerialLogger.hpp"

SerialLogger::SerialLogger(Print &serial, const char *context,
                           LogLevel logLevel)
    : Logger(context, logLevel), _serial(serial) {}

bool SerialLogger::loglevel_active(LogLevel level) {
  return level >= _logLevel;
}

void SerialLogger::start_action(const char *actionName, LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }
  _serial.printf("[%s] : Starting %s...", _context, actionName);
}

void SerialLogger::end_action(ActionResult result, LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }

  switch (result) {
  case ACTION_SUCCESS:
    _serial.println("\t[OK]");
    break;
  case ACTION_WARNING:
    _serial.println("\t[WARNING]");
    break;
  case ACTION_ERROR:
    _serial.println("\t[ERROR]");
    break;
  default:
    _serial.println("\t[UNKNOWN]");
  }
}

void SerialLogger::end_action(ActionResult result, const char *msg,
                              LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }

  if (sizeof(msg) == 0) {
    end_action(result, logLevel);
    return;
  }

  switch (result) {
  case ACTION_SUCCESS:
    _serial.printf("\t[OK]: %s\n", msg);
    break;
  case ACTION_WARNING:
    _serial.printf("\t[WARNING]: %s\n", msg);
    break;
  case ACTION_ERROR:
    _serial.printf("\t[ERROR]: %s\n", msg);
    break;
  default:
    _serial.printf("\t[UNKNOWN]: %s\n", msg);
  }
}

void SerialLogger::println(const char *msg, LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }
  _serial.printf("[%s] : %s\n", _context, msg);
}
void SerialLogger::println(float num, LogLevel logLevel) {
  char buff[10];
  dtostrf(num, 1, 0, buff);
  println(buff, logLevel);
}

void SerialLogger::print(const char *msg, LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }

  _serial.printf("[%s] : %s", _context, msg);
}

void SerialLogger::print(float num, LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }
  char buff[10];
  dtostrf(num, 1, 0, buff);

  _serial.printf("[%s] : %s\n", _context, buff);
}

void SerialLogger::printf(const char *msg, ...) {
  // va_list args;
  // va_start(args, msg);
  // vsprintf(msg, args);
  // va_end(args);
}

void SerialLogger::print_vco_settings(DCOSetting vco, LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }

  _serial.print("\t\t\tType: ");
  switch (vco.Waveform) {
  case 0:
    _serial.println("SAWTOOTH");
    break;
  case 1:
    _serial.println("SQUARE");
    break;
  case 2:
    _serial.println("TRIANGLE");
    break;
  case 3:
    _serial.println("SINE");
    break;
  }
  _serial.print("\t\t\tDetune: ");
  _serial.println(vco.Detune);
}

void SerialLogger::print_envelope_settings(EnvelopeSetting envelope,
                                           LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }

  _serial.print("\t\t\tAttack: ");
  _serial.println(envelope.Attack);
  _serial.print("\t\t\tDecay: ");
  _serial.println(envelope.Decay);
  _serial.print("\t\t\tSustain: ");
  _serial.println(envelope.Sustain);
  _serial.print("\t\t\tRelease: ");
  _serial.println(envelope.Release);
}

void SerialLogger::print_lfo_settings(LFOSetting lfo, LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }

  _serial.print("\t\t\tRate: ");
  _serial.println(lfo.Rate);
  _serial.print("\t\t\tAmount: ");
  _serial.println(lfo.Amount);
}

void SerialLogger::print_mixer_settings(MixerSetting mixer, LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }

  _serial.print("\t\t\tVCO1Gain: ");
  _serial.println(mixer.DCO1Gain);
  _serial.print("\t\t\tVCO2Gain: ");
  _serial.println(mixer.DCO2Gain);
  _serial.print("\t\t\tVCO3Gain: ");
  _serial.println(mixer.DCO3Gain);
  _serial.print("\t\t\tNoise: ");
  _serial.println(mixer.NoiseGain);
}

void SerialLogger::print_patch_settings(PatchSetting patch, LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }

  _serial.print("\tName: ");
  _serial.println(patch.Name);
  _serial.println("\t\tVCO1: ");
  print_vco_settings(patch.DCO1, logLevel);
  _serial.println("\t\tVCO2: ");
  print_vco_settings(patch.DCO2, logLevel);
  _serial.println("\t\tVCO3: ");
  print_vco_settings(patch.DCO3, logLevel);
  _serial.println("\t\tEnvelope: ");
  print_envelope_settings(patch.Envelope, logLevel);
  _serial.println("\t\tLFO: ");
  print_lfo_settings(patch.LFO, logLevel);
  _serial.println("\t\tMixer: ");
  print_mixer_settings(patch.Mixer, logLevel);
}

void SerialLogger::print_settings(Settings settings, LogLevel logLevel) {
  if (!loglevel_active(logLevel)) {
    return;
  }

  _serial.println("System: ");
  _serial.print("\tShowBootscreen: ");
  if (settings.System.ShowBootscreen) {
    _serial.println("true");
  } else {
    _serial.println("false");
  }
  _serial.print("\tBootscreenFilepath: ");
  _serial.println(settings.System.BootscreenFilepath);
  _serial.print("\tMIDI channel: ");
  _serial.println(settings.System.MidiChannel);
  print_patch_settings(settings.Patches[0], logLevel);
  print_patch_settings(settings.Patches[1], logLevel);
}