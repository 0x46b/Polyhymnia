#ifndef MOCK_AVR_IO_H
#define MOCK_AVR_IO_H
/* Fake implementation of avr/io.h to mock the registers in the test */
#include <stdint.h>

extern volatile uint8_t mock_PORTB;
extern volatile uint8_t mock_DDRB;
extern volatile uint8_t mock_PINB;
extern volatile uint8_t mock_SPCR;
extern volatile uint8_t mock_SPDR;

#define PORTB mock_PORTB
#define DDRB mock_DDRB
#define PINB mock_PINB
#define SPCR mock_SPCR
#define SPDR mock_SPDR

#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7

#define SPE 1
#define SPIE 2
#define SPI 3
#define DORD 4
#endif
