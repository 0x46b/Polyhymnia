#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#define INPUT_BUFFER_SIZE 200
#define INDEX_BUFFER_SIZE 16
#define MASK (INPUT_BUFFER_SIZE - 1)

typedef struct {
	uint8_t data[INPUT_BUFFER_SIZE];
	uint8_t head;
	uint8_t tail;
} RingBuffer;

void buffer_write(RingBuffer* buffer, uint8_t entry){
	if(buffer->tail+1 > INPUT_BUFFER_SIZE){
		if()
	}
	
	buffer->data[buffer->tail] = entry;
	buffer->tail++;
}

uint8_t buffer_read(RingBuffer* buffer){
	if(buffer->head > buffer->tail){
		
	}
	
	uint8_t data = buffer->data[buffer->head];
	buffer->head++;
	
	return data;
}
#endif