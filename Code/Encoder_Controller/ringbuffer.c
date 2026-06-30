#include "ringbuffer.h"

int8_t buffer_write(volatile RingBuffer *buffer, uint8_t entry) {
  int next;

  next = buffer->head + 1; // next is where head will point to after this write.
  if (next >= buffer->maxlen)
    next = 0;

  if (next == buffer->tail) // if the head + 1 == tail, circular buffer is full
    return -1;

  buffer->data[buffer->head] = entry; // Load data and then move
  buffer->head = next;                // head to next data offset.
  return 0; // return success to indicate successful push.
}

int8_t buffer_read(volatile RingBuffer *buffer) {
  int next;

  if (buffer->head ==
      buffer->tail) // if the head == tail, we don't have any data
    return -1;

  next = buffer->tail + 1; // next is where tail will point to after this read.
  if (next >= buffer->maxlen)
    next = 0;

  uint8_t data = buffer->data[buffer->tail]; // Read data and then move
  buffer->tail = next;                       // tail to next offset.

  return data;
}
