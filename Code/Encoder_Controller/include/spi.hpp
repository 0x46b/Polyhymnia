#ifndef _SPI_H
#define _SPI_H

#include <avr/io.h>
#include <avr/portpins.h>
#include <inttypes.h>

#define MISO 6
#define MOSI 5
#define SCK 3

class SPIConnection {
private:
  uint8_t _lastMessage;

public:
  void Initialize(bool isMaster);
  uint8_t Read();
  uint8_t Send(uint8_t data);
  void AssertCS();
  void DeassertCS();
};

#endif // _SPI_H
