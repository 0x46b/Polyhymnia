#ifndef SPI_COMMANDS_H
#define SPI_COMMANDS_H
#include <stdint.h>

/* Return codes, that the slave can send back to the master to indicate some
 * states */
typedef enum {
  /* Slave listens, transaction could be done normally */
  MODULE_LISTENING = 0xA,
  /* Something went horribly wrong, so the current command must be indicated
   * "lost" and resend */
  MODULE_FAILURE = 0xF,
  /* The module is busy at the moment and cannot receive commands. Resend
   * command after a short delay */
  MODULE_BUSY = 0xB,
  MODULE_UNKNOWN_COMMAND = 0xC
} module_status_codes;

/* Command definitions for using in the SPI_Frame */
typedef enum {
  NOP = 0x0,
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

/* Frame for sending/receiving SPI-commands */
typedef struct {
  spi_command command;
  uint8_t payload;
} SPI_Frame;

/* Checks, wether the byte is a valid command (returns 1) or not (returns 0) */
uint8_t is_byte_valid_command(uint8_t byte);

#endif
