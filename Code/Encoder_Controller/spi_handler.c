#include "spi_handler.h"

volatile spi_state _spi_state = CMD_EXEC;
volatile RingBuffer _transferBuffer;
volatile SPI_Frame _lastCommand;
volatile spi_command_response_length_in_bytes _transfer_length_in_bytes = None;
volatile uint8_t _transferred_number_of_bytes = 0;

void initialize_spi(void) {
  DDRB &= ~((1 << MOSI) | (1 << SCK) |
            (1 << SS)); /* Make MOSI, SCK, SS as input pins */
  DDRB |= (1 << MISO);  /* Make MISO pin as output pin */
  SPCR = (1 << SPE) | (1 << SPIE) | (1 << DORD); /* Enable SPI in slave mode */
}

void handle_received_byte(uint8_t byte) {
  switch (_spi_state) {
  case CMD_READ:
    _lastCommand.command = byte;
    _spi_state = PAYLOAD_READ;
    SPDR = MODULE_LISTENING;
    break;

  case PAYLOAD_READ:
    _lastCommand.payload = byte;
    _spi_state = CMD_EXEC;
    SPDR = MODULE_BUSY;

  case TRANSFER_READY:
    SPDR = buffer_read(&_transferBuffer);
    _transferred_number_of_bytes++;

    if (_transferred_number_of_bytes == _transfer_length_in_bytes) {
      _transferred_number_of_bytes = 0;
      _transfer_length_in_bytes = 0;
      _spi_state = CMD_READ;
    }
    break;

  case UNKNOWN_COMMAND:
    SPDR = MODULE_UNKNOWN_COMMAND;
    break;

  default:
    SPDR = MODULE_FAILURE;
    break;
  };
}
