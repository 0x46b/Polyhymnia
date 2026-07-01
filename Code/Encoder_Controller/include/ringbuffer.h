#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdint.h>

#define INPUT_BUFFER_SIZE 200
#define INDEX_BUFFER_SIZE 16
#define MASK (INPUT_BUFFER_SIZE - 1)

typedef enum {
  BUFFER_SUCCESS = 0,
  BUFFER_FULL = 1,
  BUFFER_EMPTY = 2
} buffer_action_result;

typedef struct {
  uint8_t data[INPUT_BUFFER_SIZE];
  uint8_t head;
  uint8_t tail;
  const uint8_t maxlen;
} RingBuffer;

buffer_action_result buffer_write(volatile RingBuffer *buffer, uint8_t entry);
buffer_action_result buffer_read(volatile RingBuffer *buffer, uint8_t *entry);

#endif
