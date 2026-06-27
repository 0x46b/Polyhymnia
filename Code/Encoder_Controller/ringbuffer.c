#include "ringbuffer.h"

void buffer_write(volatile RingBuffer *buffer, uint8_t entry) {
  if (buffer->tail == buffer->head) {
    // TODO Handle somehow
  }

  buffer->data[buffer->tail] = entry;
  buffer->tail++;
}

uint8_t buffer_read(volatile RingBuffer *buffer) {
  if (buffer->head == buffer->tail) {
  }

  uint8_t data = buffer->data[buffer->head];
  buffer->head++;

  return data;
}
