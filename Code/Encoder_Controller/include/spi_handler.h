#ifndef SPI_HANDLER_H
#define SPI_HANDLER_H
#include "ringbuffer.h"
#include "spi_commands.h"
#include <avr/io.h>
#include <stdint.h>

#define SS PB4
#define MOSI PB5
#define MISO PB6
#define SCK PB7

void spi_initialize(void);
void handle_received_byte(uint8_t byte);
buffer_action_result write_to_transfer_buffer(uint8_t byte);
int is_command_ready(void);
spi_command get_command(void);
uint8_t get_payload(void);
void set_transfer_ready(void);
void set_ready_for_next_cmd(void);

#endif
