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

/* Initializes the internal data-structures, configures SPI and sets the correct
 *  data-direction-registers
 */
void spi_initialize(void);

/* Used in the SPI-ISR to handle the incoming data.
 * Internally a state-machine is handled, so what this method will do is
 * dependend of the current state in the "workflow", we are in.
 * An "happy-path" example would be:
 * 1) The master sends the first byte, which is the actual command, that gets
 *    stored internally
 * (see spi_commands.h for further info)
 * 2) The master will send a payload (e.g. an id) for the previous command,
 *    which gets also stored internally
 * Since the whole command is transferred now, is_command_ready() will return
 * true and the command should get handled from the "outside".
 * This means: the function will now send MODULE_BUSY to the master on the next
 * calls until set_transfer_ready() or set_ready_for_next_cmd() gets called
 * 3a)  set_transfer_ready() called:
 *      if something got pushed into the transfer-buffer via
 *      write_to_transfer_buffer(uint8_t) any data sent from the master will get
 *      ignored and bytes from the transfer-buffer will get send until nothing
 *      is left to send
 * 3b) set_ready_for_next_cmd() called:
 *     every buffer will get reset and we start back at  1)
 */
void handle_received_byte(uint8_t byte);

/* Writes the given byte to the transfer-buffer, so it gets send to the master
 * via handle_received_byte() after calling set_transfer_ready()
 *
 * NOTE: The buffer is locked in any state except CMD_EXEC. You SHOULD check
 *       is_command_ready() and/or the return value of every write to make sure
 *       it succeeded
 *
 * Returns:
 * BUFFER_SUCCESS: Data successfully written to the buffer
 * BUFFER_FULL: The buffer is full
 * BUFFER_LOCKED: The buffer could only get written to, if an unexecuted command
 * was received
 */
buffer_action_result write_to_transfer_buffer(uint8_t byte);
/* Indicates, if a command was fully received
 * Returns:
 * 0 = no command ready for execution
 * 1 = command ready for execution
 */
int is_command_ready(void);

/* Gets the last received command */
spi_command get_command(void);

/* Gets the last payload */
uint8_t get_payload(void);

/* Indicates, that everything is written in the transfer-buffer and should get
 * send out at the next cycle via handle_received_bytes(). If the current
 * command has nothing to return use set_ready_for_next_command() instead */
void set_transfer_ready(void);

/* Resets the state-machine and should be used for "read-only" commands, where
 * no answer to the master is required*/
void set_ready_for_next_cmd(void);

#endif
