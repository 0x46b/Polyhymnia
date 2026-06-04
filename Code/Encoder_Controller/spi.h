// spi.h
//
// SPI master routines were pulled from the Atmel ATMega168 datasheet.

#ifndef _SPI_H
#define _SPI_H

#include <inttypes.h>
#include <avr/io.h>

void spi_init() {
  SPCR = 
}
void spi_read();
void spi_send();

#endif // _SPI_H
