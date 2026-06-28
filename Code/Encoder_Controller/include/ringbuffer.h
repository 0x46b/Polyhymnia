#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdint.h>

#define INPUT_BUFFER_SIZE 200
#define INDEX_BUFFER_SIZE 16
#define MASK (INPUT_BUFFER_SIZE - 1)

typedef struct {
  uint8_t data[INPUT_BUFFER_SIZE];
  uint8_t head;
  uint8_t tail;
  const uint8_t maxlen;
} RingBuffer;

int8_t buffer_write(volatile RingBuffer *buffer, uint8_t entry);
uint8_t buffer_read(volatile RingBuffer *buffer);

#endif
