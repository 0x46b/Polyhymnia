#include "spi_handler.h"
#include "ringbuffer.h"
#include "spi_commands.h"

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
} spi_state_flag;

typedef struct {
  spi_state_flag state;
  SPI_Frame lastCommand;
  uint8_t bytes_to_send;
  uint8_t transferred_bytes;
} spi_state;

static spi_state _spi_state = (spi_state){.state = CMD_READ,
                                          .lastCommand = {NOP, 0},
                                          .bytes_to_send = 0,
                                          .transferred_bytes = 0};

static RingBuffer _transferBuffer = (RingBuffer){
    .maxlen = INPUT_BUFFER_SIZE, .data = {0}, .head = 0, .tail = 0};

int is_command_ready(void) {
  if (_spi_state.state == CMD_EXEC)
    return 1;
  return 0;
}

uint8_t get_payload(void) { return _spi_state.lastCommand.payload; }

spi_command get_command(void) { return _spi_state.lastCommand.command; }

void set_transfer_ready(void) { _spi_state.state = TRANSFER_READY; }

void set_ready_for_next_cmd(void) { _spi_state.state = CMD_READ; }

buffer_action_result write_to_transfer_buffer(uint8_t byte) {
  buffer_action_result result = buffer_write(&_transferBuffer, byte);
  if (result == BUFFER_SUCCESS) {
    _spi_state.bytes_to_send++;
  }
  return result;
}

void spi_initialize(void) {
  _spi_state.state = CMD_READ;
  _spi_state.bytes_to_send = 0;
  _spi_state.transferred_bytes = 0;
  _spi_state.lastCommand.command = NOP;
  _spi_state.lastCommand.payload = 0;

  DDRB &= ~((1 << MOSI) | (1 << SCK) |
            (1 << SS)); /* Make MOSI, SCK, SS as input pins */
  DDRB |= (1 << MISO);  /* Make MISO pin as output pin */
  SPCR = (1 << SPE) | (1 << SPIE) | (1 << DORD); /* Enable SPI in slave mode */
}

void handle_received_byte(uint8_t byte) {
  uint8_t data;
  buffer_action_result result;

  switch (_spi_state.state) {
  case CMD_READ:
    if (is_byte_valid_command(byte)) {
      _spi_state.lastCommand.command = byte;
      _spi_state.state = PAYLOAD_READ;
      SPDR = MODULE_LISTENING;
    } else {
      SPDR = MODULE_UNKNOWN_COMMAND;
    }
    return;
    ;

  case PAYLOAD_READ:
    _spi_state.lastCommand.payload = byte;
    _spi_state.state = CMD_EXEC;
    SPDR = MODULE_BUSY;
    return;
    ;

  case TRANSFER_READY:
    result = buffer_read(&_transferBuffer, &data);
    if (result == BUFFER_EMPTY) {
      SPDR = MODULE_FAILURE;
      return;
    }

    SPDR = data;
    _spi_state.transferred_bytes++;

    if (_spi_state.transferred_bytes == _spi_state.bytes_to_send) {
      _spi_state.transferred_bytes = 0;
      _spi_state.bytes_to_send = 0;
      _spi_state.state = CMD_READ;
    }
    return;
    ;

  case UNKNOWN_COMMAND:
    SPDR = MODULE_UNKNOWN_COMMAND;
    _spi_state.state = CMD_READ;
    return;

  default:
    SPDR = MODULE_FAILURE;
    return;
    ;
  };
}
