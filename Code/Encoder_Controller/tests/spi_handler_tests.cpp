#include "spi_commands.h"
#include <CppUTest/TestHarness.h>
#include <CppUTest/UtestMacros.h>
#include <stdint.h>

extern "C" {
#include "../include/spi_handler.h"
}

volatile uint8_t mock_PORTB = 0;
volatile uint8_t mock_DDRB = 0;
volatile uint8_t mock_PINB = 0;
volatile uint8_t mock_SPCR = 0;
volatile uint8_t mock_SPDR = 0;

TEST_GROUP(SpiHandlerTests){void setup(){mock_DDRB = 0;
mock_PINB = 0;
mock_PORTB = 0;
mock_SPCR = 0;
mock_SPDR = 0;
spi_initialize();
}
}
;

TEST(SpiHandlerTests, handleReceivedBytesSendsCorrectStates) {
  handle_received_byte(ReadOSC);
  ENUMS_EQUAL_INT(MODULE_LISTENING, SPDR);

  handle_received_byte(1);
  BYTES_EQUAL(MODULE_BUSY, SPDR);
}

TEST(SpiHandlerTests, handleReceivedBytesParsesCommandCorrectly) {
  spi_command received_command = ReadOSC;
  uint8_t received_payload = 0xA;

  handle_received_byte(received_command);
  handle_received_byte(received_payload);

  uint8_t cmdReady = is_command_ready();
  CHECK(cmdReady);

  spi_command cmd = get_command();
  BYTES_EQUAL(received_command, cmd);
  uint8_t payload = get_payload();
  BYTES_EQUAL(received_payload, payload);
}

TEST(SpiHandlerTests, sendSingleByte) {
  write_to_transfer_buffer(7);
  set_transfer_ready();

  handle_received_byte(ReadOSC);
  BYTES_EQUAL(7, SPDR);
}

TEST(SpiHandlerTests, handleReceivedBytesSendsIfTransferReady) {
  write_to_transfer_buffer(4);
  write_to_transfer_buffer(5);
  write_to_transfer_buffer(6);
  write_to_transfer_buffer(7);
  set_transfer_ready();

  handle_received_byte(ReadOSC);
  BYTES_EQUAL(4, SPDR);

  handle_received_byte(ReadOSC);
  BYTES_EQUAL(5, SPDR);

  handle_received_byte(ReadOSC);
  BYTES_EQUAL(6, SPDR);

  handle_received_byte(ReadOSC);
  BYTES_EQUAL(7, SPDR);
}
