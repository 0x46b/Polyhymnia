#ifndef CONSTANTS_H
#define CONSTANTS_H

const float DIV127 = (1.0 / 127.0);
const char* SETTINGS_FILENAME = "settings.json";


#define LOGLEVEL_TRACE 5
#define LOGLEVEL_DEBUG 4
#define LOGLEVEL_INFO 3
#define LOGLEVEL_WARNING 2
#define LOGLEVEL_ERROR 1
#define LOGLEVEL_FATAL 0

// This is a little bit hacky, replace it with correct handling ASAP
#define CURRENT_LOGLEVEL LOGLEVEL_DEBUG
#endif