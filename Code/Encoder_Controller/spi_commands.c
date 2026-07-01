#include "spi_commands.h"

uint8_t is_byte_valid_command(uint8_t byte) {
  switch (byte) {
  case ReadOSC:
  case ReadEnvelope:
  case ReadFilter:
  case ReadLFO:
  case SetWaveformSaw:
  case SetWaveformSine:
  case SetWaveformSquare:
  case SetWaveformTriangle:
  case SetEnvelope:
  case SetLFO:
  case SetFilter:
    return 1;
  default:
    return 0;
  };
}
