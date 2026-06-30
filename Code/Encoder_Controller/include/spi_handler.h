#ifndef SPI_HANDLER_H
#define SPI_HANDLER_H
#include "ringbuffer.h"
#include "spi_commands.h"
#include <avr/io.h>

#define SS PB4
#define MOSI PB5
#define MISO PB6
#define SCK PB7

/* State machine for command-handling over SPI. Normal execution as follows:
CMD_READ => We are "idling", so the next byte received will be the
command-portion of the frame PAYLOAD_READ => We already received a command, so
the next byte will be the payload CMD_EXE => The whole frame is received, so if
this state is set the main code could read _lastCommand and fill _transferBuffer
with the requested data TRANSFER_READY => _transferBuffer has been filled, so
the next cycles from master we send them out */
typedef enum {
  /* Waiting for the command of the SPI frame*/
  CMD_READ,

  /* Waiting for payload of the SPI frame */
  PAYLOAD_READ,

  /* SPI frame is complete, this signals the main code the command can get
     processed and output could get stored into _transferBuffer */
  CMD_EXEC,

  /* _transferBuffer has something, that we could send as response of the last
     command. Will get set by main code */
  TRANSFER_READY,

  /* Could indicate that the last command was somehow not known, either not
     implemented or somehow "invalid" */
  UNKNOWN_COMMAND
} spi_state;

extern volatile spi_state _spi_state;
extern volatile RingBuffer _transferBuffer;
extern volatile SPI_Frame _lastCommand;

/* Will get set by main code to how many bytes should get send before switching
 * back to CMD_READ */
extern volatile spi_command_response_length_in_bytes _transfer_length_in_bytes;

/* Counter to memorize how many bytes for TRANSFER_READY already got send */
extern volatile uint8_t _transferred_number_of_bytes;

void initialize_spi(void);
void handle_received_byte(uint8_t byte);
#endif
