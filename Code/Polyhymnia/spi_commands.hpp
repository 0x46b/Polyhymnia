#ifndef SPI_COMMANDS_H
#define SPI_COMMANDS_H
/*
  Commands are one byte, the first 4 bits are the command, the last 4 bits the
  "data"
  e.g.
  |0001 |0001|
  ^read ^ encoder-id 1
 */
// Commands (first 4 bits)
#include <inttypes.h>

/* Return codes, that the slave can send back to the master to indicate some states */

/* Slave listens, transaction could be done normally */
#define MODULE_LISTENING 0xC0
/* Something went horribly wrong, so the current command must be indicated "lost" and resend */
#define MODULE_FAILURE 0xBD
/* The module is busy at the moment and cannot receive commands. Resend command after a short delay */
#define MODULE_BUSY 0xBF

/* Commanddefinitions for using in the SPI_Frame */
typedef enum {
  ReadOSC = 0x1,
  ReadEnvelope = 0x2,
  ReadFilter = 0x3,
  ReadLFO = 0x4,
  SetWaveformSaw = 0x5,
  SetWaveformSquare = 0x6,
  SetWaveformTriangle = 0x7,
  SetWaveformSine = 0x8,
} spi_command;

/* Frame for sending SPI-commands */
typedef struct {
  spi_command command;
  uint8_t payload;
} SPI_Frame;

#endif
