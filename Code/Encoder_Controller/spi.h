#ifndef _SPI_H
#define _SPI_H

#include <inttypes.h>
#include <avr/io.h>
#include <avr/portpins.h>

#define MISO 6
#define MOSI 5
#define SCK 3

void spi_slave_init() {
	// MISO as Output
	DDRB=(1<<MISO);
	
	// SPIE = Enable interrupts
	// SPE = Enable SPI
	SPCR = (1<<SPIE)|(1<<SPE);
}

void spi_master_init() {
	// MOSI and SCK as Output
	DDRB=(1<<MOSI)|(1<<SCK);
	// SPIE = Enable interrupts
	// SPE = Enable SPI
	// MSTR = master
	SPCR = (1<<SPIE)|(1<<SPE)|(1<<MSTR);
}

unsigned char spi_read(){
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}

unsigned char spi_send(unsigned char data){
	// Load data into the buffer
	SPDR = data;
	
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}

#endif // _SPI_H
