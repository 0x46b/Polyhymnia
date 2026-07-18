#ifndef SERIAL_LOGGER_HPP
#define SERIAL_LOGGER_HPP

#include "Logger.hpp"
#include <Arduino.h>

// TODO: Implement non-blocking logging (Save messages to Ringbuffer and send
// them out by calling a "send"- method, that could get called in the loop to
// have control over when we have time for sending)
class SerialLogger : public Logger {
private:
  Stream *_serial;

public:
  SerialLogger(Stream *serial, const char *context, LogLevel logLevel);
  void start_action(const char *actionName, LogLevel logLevel);
  void end_action(ActionResult result, LogLevel logLevel);
  void end_action(ActionResult result, const char *msg, LogLevel logLevel);
  void println(const char *msg, LogLevel logLevel);
  void println(float num, LogLevel logLevel);
  void print(const char *msg, LogLevel logLevel);
  void print(float num, LogLevel logLevel);
  void printf(const char *msg, ...);
  void print_vco_settings(VCOSetting vco, LogLevel logLevel);
  void print_envelope_settings(EnvelopeSetting envelope, LogLevel logLevel);
  void print_lfo_settings(LFOSetting lfo, LogLevel logLevel);
  void print_mixer_settings(MixerSetting mixer, LogLevel logLevel);
  void print_patch_settings(PatchSetting patch, LogLevel logLevel);
  void print_settings(Settings settings, LogLevel logLevel);
};
#endif