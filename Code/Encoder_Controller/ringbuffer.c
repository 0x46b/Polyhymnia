#include "ringbuffer.h"

buffer_action_result buffer_write(volatile ring_buffer *buffer, uint8_t entry) {
  uint8_t next;

  next = buffer->head + 1; // next is where head will point to after this write.
  if (next >= buffer->maxlen)
    next = 0;

  if (next == buffer->tail) // if the head + 1 == tail, circular buffer is full
    return BUFFER_FULL;

  buffer->data[buffer->head] = entry; // Load data and then move
  buffer->head = next;                // head to next data offset.
  return BUFFER_SUCCESS; // return success to indicate successful push.
}

buffer_action_result buffer_read(volatile ring_buffer *buffer, uint8_t *entry) {
  int next;

  if (buffer->head ==
      buffer->tail) // if the head == tail, we don't have any data
    return BUFFER_EMPTY;

  next = buffer->tail + 1; // next is where tail will point to after this read.
  if (next >= buffer->maxlen)
    next = 0;

  *entry = buffer->data[buffer->tail]; // Read data and then move
  buffer->tail = next;                 // tail to next offset.

  return BUFFER_SUCCESS;
}

void buffer_reset(volatile ring_buffer *buffer) {
  buffer->head = 0;
  buffer->tail = 0;
}
