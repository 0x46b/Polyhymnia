#include "spi.hpp"

void SPIConnection::Initialize(bool isMaster) {
  if (isMaster) {
    // MOSI and SCK as Output
    DDRB |= (1 << MOSI) | (1 << SCK);
    // SPIE = Enable interrupts
    // SPE = Enable SPI
    // MSTR = master
    SPCR = (1 << SPIE) | (1 << SPE) | (1 << MSTR);
  }
  // MISO as Output
  DDRB |= (1 << MISO);

  // SPIE = Enable interrupts
  // SPE = Enable SPI
  SPCR |= (1 << SPIE) | (1 << SPE);
}

uint8_t SPIConnection::Read() {
  while (!(SPSR & (1 << SPIF))) {
    // Wait
  }

  this->_lastMessage = SPDR;

  return this->_lastMessage;
}

uint8_t SPIConnection::Send(uint8_t data) {
  // Load data into the buffer
  SPDR = data;

  // Wait for transmission complete
  while (!(SPSR & (1 << SPIF)))
    ;

  return SPDR;
}

// Assert the SS line
void SPIConnection::AssertCS() {
  //  SPI_PORT &= ~(1 << SPI_CS);
}

// Deassert the SS line
void SPIConnection::DeassertCS() {
  //  SPI_PORT |= (1 << SPI_CS);
}
