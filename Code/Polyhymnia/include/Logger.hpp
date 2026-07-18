#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Settings.hpp"

typedef enum LogLevel {
  LOGLEVEL_FATAL = 5,
  LOGLEVEL_ERROR = 4,
  LOGLEVEL_WARNING = 3,
  LOGLEVEL_INFO = 2,
  LOGLEVEL_DEBUG = 1,
  LOGLEVEL_TRACE = 0
} LogLevel;

typedef enum ActionResult {
  ACTION_SUCCESS = 0,
  ACTION_WARNING = 1,
  ACTION_ERROR = 2
} ActionResult;

class Logger {
protected:
  const char *_context;
  LogLevel _logLevel;

public:
  Logger(const char *context, LogLevel logLevel) {
    _context = context;
    _logLevel = logLevel;
  }
  virtual void println(const char *msg, LogLevel logLevel) = 0;
  virtual void println(float num, LogLevel logLevel) = 0;
  virtual void print(const char *msg, LogLevel logLevel) = 0;
  virtual void print(float num, LogLevel logLevel) = 0;
  virtual void printf(const char *msg, ...) = 0;
  virtual void print_settings(Settings settings, LogLevel logLevel) = 0;
  virtual void print_envelope_settings(EnvelopeSetting envelope,
                                       LogLevel logLevel) = 0;
  virtual void print_vco_settings(DCOSetting vco, LogLevel logLevel) = 0;
  virtual void print_lfo_settings(LFOSetting lfo, LogLevel logLevel) = 0;
  virtual void print_patch_settings(PatchSetting patch, LogLevel logLevel) = 0;
  virtual void print_mixer_settings(MixerSetting mixer, LogLevel logLevel) = 0;
  virtual void start_action(const char *actionName, LogLevel logLevel) = 0;
  virtual void end_action(ActionResult result, LogLevel logLevel) = 0;
  virtual void end_action(ActionResult result, const char *msg,
                          LogLevel logLevel) = 0;
};

#endif