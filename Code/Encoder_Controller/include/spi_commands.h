#ifndef SPI_COMMANDS_H
#define SPI_COMMANDS_H
/*
  Commands are one byte, the first 4 bits are the command, the last 4 bits the
  "data"
  e.g.
  |0001 |0001|
  ^read ^ encoder-id 1
 */
// Commands (first 4 bits)
#include <inttypes.h>

#define READ 0x1

uint8_t GenerateReadCommand(uint8_t encoderId) {
  return (READ << 4) | encoderId;
}

uint8_t DecodeCommand(uint8_t msg) { return (msg & 0xF0) >> 4; }
uint8_t DecodeData(uint8_t msg) { return msg & 0xF;}

#endif
