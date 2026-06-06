#include "encoder.hpp"

const int8_t Encoder::STATETABLE[] =
    // Gray-table for all possible combinations of A and B
    // 1 = CW-turn
    // -1 = CCW-turn
    // 00 01 11 10
    {0,  1,  -1, 0,  // 00
     -1, 0,  0,  1,  // 01
     1,  0,  0,  -1, // 11
     0,  -1, 1,  0}; // 10

void Encoder::Initialize(uint8_t encoderId, volatile uint8_t *pin,
                         volatile uint8_t *port, uint8_t phaseA,
                         uint8_t phaseB) {
  _config.encoderId = encoderId;
  _config.phaseA = phaseA;
  _config.phaseB = phaseB;
  _config.port = port;
  _config.pin = pin;

  *port |= phaseA | phaseB;
}

int Encoder::Read(uint8_t step) {
  int8_t currentOffsetBuff = _currentOffset;
  _currentOffset = 0;

  return currentOffsetBuff;
}

void Encoder::Tick() {
  // Shift old-state 2 to the right and trim first byte
  // e.g. old-state = 00001010 => <<2 => 00101000 => &0x0F => 00001000
  _oldState = (_oldState << 2) & 0x0F;
  // Check, if A is HIGH, if so set second last bit to 1
  if (*_config.pin & _config.phaseA) {
    _oldState |= 2;
  }
  // Check, if B is HIGH, if so set last bit to 1
  if (*_config.pin & _config.phaseB) {
    _oldState |= 1;
  }

  // Get value from our gray-table
  int8_t movement = STATETABLE[_oldState];
  if (movement == 1 || movement == -1) {
    _currentOffset += movement;
  }
}
