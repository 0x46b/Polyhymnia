#ifndef LOGGER_FACTORY_H
#define LOGGER_FACTORY_H
#include "Logger.hpp"
#include <Arduino.h>

typedef enum LoggerType { SERIALLOGGER, FILELOGGER } LoggerType;

class LoggerFactory {
private:
  Print &_serial;
  LogLevel _currentLogLevel;
  LoggerType _defaultType = SERIALLOGGER;

public:
  LoggerFactory(Print &serial, LogLevel currentLoglevel);
  Logger *CreateForContext(const char *context, LoggerType type);
  Logger *CreateDefaultForContext(const char *context);
  void SetDefaultType(LoggerType type);
};
#endif