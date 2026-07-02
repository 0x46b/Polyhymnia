#include <CppUTest/TestHarness.h>
#include <CppUTest/UtestMacros.h>
#include <stdint.h>
extern "C" {
#include "../include/ringbuffer.h"
}

TEST_GROUP(RingbufferTests){};

TEST(RingbufferTests, resetResetsTheBuffer) {
  ring_buffer buffer = {{0}, 0, 0, INPUT_BUFFER_SIZE};
  buffer_write(&buffer, 10);
  buffer_write(&buffer, 11);
  buffer_reset(&buffer);
  uint8_t data;
  uint8_t result = buffer_read(&buffer, &data);
  ENUMS_EQUAL_INT(BUFFER_EMPTY, result);
}

TEST(RingbufferTests, StoringAndRetrivingSingleEntry) {
  ring_buffer buffer = {{0}, 0, 0, INPUT_BUFFER_SIZE};
  int8_t firstEntry = 10;
  int executionResult = buffer_write(&buffer, firstEntry);
  uint8_t entry = 0;
  executionResult = buffer_read(&buffer, &entry);
  CHECK_EQUAL(0, executionResult);
  CHECK_EQUAL(firstEntry, entry);
}

TEST(RingbufferTests, StoringAndRetrivingMultipleEntries) {
  ring_buffer buffer = {{0}, 0, 0, INPUT_BUFFER_SIZE};
  uint8_t firstEntry = 10;
  uint8_t secondEntry = 12;
  uint8_t thirdEntry = 15;

  buffer_action_result executionResult = buffer_write(&buffer, firstEntry);
  ENUMS_EQUAL_INT(BUFFER_SUCCESS, executionResult);

  executionResult = buffer_write(&buffer, secondEntry);
  ENUMS_EQUAL_INT(BUFFER_SUCCESS, executionResult);

  executionResult = buffer_write(&buffer, thirdEntry);
  ENUMS_EQUAL_INT(BUFFER_SUCCESS, executionResult);

  uint8_t entry = 0;
  executionResult = buffer_read(&buffer, &entry);
  CHECK_EQUAL(firstEntry, entry);
  ENUMS_EQUAL_INT(BUFFER_SUCCESS, executionResult);

  executionResult = buffer_read(&buffer, &entry);
  CHECK_EQUAL(secondEntry, entry);

  executionResult = buffer_read(&buffer, &entry);
  CHECK_EQUAL(thirdEntry, entry);
}

TEST(RingbufferTests, TryToReadMoreThanStored) {
  ring_buffer buffer = {{0}, 0, 0, INPUT_BUFFER_SIZE};
  uint8_t firstEntry = 10;
  uint8_t secondEntry = 12;

  buffer_action_result executionResult = buffer_write(&buffer, firstEntry);
  ENUMS_EQUAL_INT(executionResult, 0);

  executionResult = buffer_write(&buffer, secondEntry);
  ENUMS_EQUAL_INT(BUFFER_SUCCESS, executionResult);

  uint8_t entry = 0;
  executionResult = buffer_read(&buffer, &entry);
  ENUMS_EQUAL_INT(BUFFER_SUCCESS, executionResult);
  CHECK_EQUAL(firstEntry, entry);

  executionResult = buffer_read(&buffer, &entry);
  ENUMS_EQUAL_INT(BUFFER_SUCCESS, executionResult);
  CHECK_EQUAL(secondEntry, entry);

  executionResult = buffer_read(&buffer, &entry);
  ENUMS_EQUAL_INT(BUFFER_EMPTY, executionResult);
}

TEST(RingbufferTests, TryToOverflowMaxSize) {
  ring_buffer buffer = {{0}, 0, 0, INPUT_BUFFER_SIZE};
  buffer_action_result executionResult;

  for (int i = 0; i <= INPUT_BUFFER_SIZE + 1; i++) {
    executionResult = buffer_write(&buffer, i);
  }
  ENUMS_EQUAL_INT(BUFFER_FULL, executionResult);
}
