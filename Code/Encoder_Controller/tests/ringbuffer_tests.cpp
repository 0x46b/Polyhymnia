#include <CppUTest/TestHarness.h>
#include <stdint.h>
extern "C" {
#include "../include/ringbuffer.h"
}

TEST_GROUP(RingbufferTests){};

TEST(RingbufferTests, StoringAndRetrivingSingleEntry) {
  RingBuffer buffer = {{0}, 0, 0, INPUT_BUFFER_SIZE};
  uint8_t firstEntry = 10;
  int executionResult = buffer_write(&buffer, firstEntry);
  uint8_t result = buffer_read(&buffer);
  CHECK_EQUAL(result, firstEntry);
  CHECK_EQUAL(executionResult, 0);
}

TEST(RingbufferTests, StoringAndRetrivingMultipleEntries) {
  RingBuffer buffer = {{0}, 0, 0, INPUT_BUFFER_SIZE};
  uint8_t firstEntry = 10;
  uint8_t secondEntry = 12;
  uint8_t thirdEntry = 15;

  int executionResult = buffer_write(&buffer, firstEntry);
  CHECK_EQUAL(executionResult, 0);

  executionResult = buffer_write(&buffer, secondEntry);
  CHECK_EQUAL(executionResult, 0);

  executionResult = buffer_write(&buffer, thirdEntry);
  CHECK_EQUAL(executionResult, 0);

  uint8_t result = buffer_read(&buffer);
  CHECK_EQUAL(result, firstEntry);
  result = buffer_read(&buffer);
  CHECK_EQUAL(result, secondEntry);
  result = buffer_read(&buffer);
  CHECK_EQUAL(result, thirdEntry);
}

TEST(RingbufferTests, TryToReadMoreThanStored) {
  RingBuffer buffer = {{0}, 0, 0, INPUT_BUFFER_SIZE};
  uint8_t firstEntry = 10;
  uint8_t secondEntry = 12;

  int executionResult = buffer_write(&buffer, firstEntry);
  CHECK_EQUAL(executionResult, 0);

  executionResult = buffer_write(&buffer, secondEntry);
  CHECK_EQUAL(executionResult, 0);

  int result = buffer_read(&buffer);
  CHECK_EQUAL(result, firstEntry);

  result = buffer_read(&buffer);
  CHECK_EQUAL(result, secondEntry);

  result = buffer_read(&buffer);
  CHECK_EQUAL(result, -1);
}

TEST(RingbufferTests, TryToOverflowMaxSize) {
  RingBuffer buffer = {{0}, 0, 0, INPUT_BUFFER_SIZE};
  int result = 0;

  for (int i = 0; i <= INPUT_BUFFER_SIZE + 1; i++) {
    result = buffer_write(&buffer, i);
  }
  CHECK_EQUAL(result, -1);
}
