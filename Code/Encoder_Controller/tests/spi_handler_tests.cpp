#include "ringbuffer.h"
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
  // Buffer is locked wenn not in CMD_EXEC, so simulate receiving a command
  handle_received_byte(ReadEnvelope);
  handle_received_byte(29);

  uint8_t writeResult = write_to_transfer_buffer(7);
  ENUMS_EQUAL_INT_TEXT(BUFFER_SUCCESS, writeResult,
                       "Writing to transfer buffer failed");
  set_transfer_ready();

  handle_received_byte(ReadOSC);
  CHECK_EQUAL(7, SPDR);
}

TEST(SpiHandlerTests,
     handleReceivedBytesWillSendBusyIfCommandIsNotExecutedYet) {
  handle_received_byte(ReadOSC);
  handle_received_byte(23);
  BYTES_EQUAL(MODULE_BUSY, SPDR);

  handle_received_byte(25);
  BYTES_EQUAL(MODULE_BUSY, SPDR);

  handle_received_byte(25);
  BYTES_EQUAL(MODULE_BUSY, SPDR);

  handle_received_byte(25);
  BYTES_EQUAL(MODULE_BUSY, SPDR);

  set_ready_for_next_cmd();

  handle_received_byte(ReadEnvelope);
  BYTES_EQUAL(MODULE_LISTENING, SPDR);
}

TEST(SpiHandlerTests, is_command_readyReturnsFalseIfStateIsNotCorrect) {
  handle_received_byte(ReadFilter);

  uint8_t ready = is_command_ready();
  CHECK_FALSE(ready);
  handle_received_byte(23);
  set_transfer_ready();

  ready = is_command_ready();
  CHECK_FALSE(ready);
}

TEST(SpiHandlerTests, write_to_transfer_bufferFailsIfHandlerIsBusy) {
  handle_received_byte(ReadFilter);
  handle_received_byte(23);
  set_transfer_ready();

  buffer_action_result result = write_to_transfer_buffer(29);
  ENUMS_EQUAL_INT(BUFFER_LOCKED, result);

  // Simulating sending data out, but we have no command yet, so it is still
  // locked
  handle_received_byte(0);
  result = write_to_transfer_buffer(29);
  ENUMS_EQUAL_INT(BUFFER_LOCKED, result);

  handle_received_byte(ReadFilter);
  handle_received_byte(23);
  // Buffer should have been reset on new command, so we now can write
  result = write_to_transfer_buffer(29);
  ENUMS_EQUAL_INT(BUFFER_SUCCESS, result);
}

TEST(SpiHandlerTests, handleReceivedBytesSendsIfTransferReady) {
  // Buffer is locked when no command was received, simulate command receive
  handle_received_byte(ReadFilter);
  handle_received_byte(29);

  uint8_t data[] = {1, 2, 3, 4};
  uint8_t writeResult = write_to_transfer_buffer(data[0]);
  ENUMS_EQUAL_INT_TEXT(BUFFER_SUCCESS, writeResult, "Writing to buffer failed");

  writeResult = write_to_transfer_buffer(data[1]);
  ENUMS_EQUAL_INT_TEXT(BUFFER_SUCCESS, writeResult, "Writing to buffer failed");

  writeResult = write_to_transfer_buffer(data[2]);
  ENUMS_EQUAL_INT_TEXT(BUFFER_SUCCESS, writeResult, "Writing to buffer failed");

  writeResult = write_to_transfer_buffer(data[3]);
  ENUMS_EQUAL_INT_TEXT(BUFFER_SUCCESS, writeResult, "Writing to buffer failed");

  set_transfer_ready();

  handle_received_byte(0);
  CHECK_EQUAL(data[0], SPDR);

  handle_received_byte(0);
  CHECK_EQUAL(data[1], SPDR);

  handle_received_byte(0);
  CHECK_EQUAL(data[2], SPDR);

  handle_received_byte(0);
  CHECK_EQUAL(data[3], SPDR);
}
