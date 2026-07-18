#include "LoggerFactory.hpp"
#include "SerialLogger.hpp"

LoggerFactory::LoggerFactory(Print &serial, LogLevel currentLoglevel)
    : _serial(serial) {
  _currentLogLevel = currentLoglevel;
}

Logger *LoggerFactory::CreateForContext(const char *context, LoggerType type) {
  switch (type) {
  case SERIALLOGGER:
    return new SerialLogger(_serial, context, _currentLogLevel);
  case FILELOGGER:
  default:
    static_assert("FileLogger not implemented yet");
  }
}

Logger *LoggerFactory::CreateDefaultForContext(const char *context) {
  return CreateForContext(context, _defaultType);
}

void LoggerFactory::SetDefaultType(LoggerType type) { _defaultType = type; }
