#ifndef SERIAL_H
#define SERIAL_H

#include<avr/io.h>
#include<avr/portpins.h>
#include<util/delay.h>
#include<string.h>
#include<stdbool.h>

#define RXD PD0;
#define TXD PD1;
#define XCK PB0;
// Does not work, idk why
//#define BAUD_RATE 9600
//#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL)))) - 1


	void serial_initialize();
	unsigned char serial_receive();
	void serial_send(unsigned char data, bool sendNewline);
	void serial_send_string(char* msg, bool sendNewLine);

#endif // SERIAL_H