#ifndef SPI_COMMANDS_H
#define SPI_COMMANDS_H

#include <inttypes.h>

/* Return codes, that the slave can send back to the master to indicate some states */
/* Slave listens, transaction could be done normally */
#define MODULE_LISTENING 0xC0
/* Something went horribly wrong, so the current command must be indicated "lost" and resend */
#define MODULE_FAILURE 0xBD
/* The module is busy at the moment and cannot receive commands. Resend command after a short delay */
#define MODULE_BUSY 0xBF

#define MODULE_UNKNOWN_COMMAND 0xAA

/* Command definitions for using in the SPI_Frame */
typedef enum {
  ReadOSC = 0x1,
  ReadEnvelope = 0x2,
  ReadFilter = 0x3,
  ReadLFO = 0x4,
  SetWaveformSaw = 0x5,
  SetWaveformSquare = 0x6,
  SetWaveformTriangle = 0x7,
  SetWaveformSine = 0x8,
  SetEnvelope = 0x9,
  SetLFO = 0x10,
  SetFilter = 0x11,
} spi_command;

/* Indicates how long the response of the commands above are in bytes */
typedef enum {
  ReadOSCLen = 3,
  ReadEnvelopeLen = 4,
  ReadFilterLen = 2,
  ReadLFOLen = 2,
  None = 0,
} spi_command_response_length_in_bytes;
	
/* Frame for sending SPI-commands */
typedef struct {
  spi_command command;
  uint8_t payload;
} SPI_Frame;

#endif
