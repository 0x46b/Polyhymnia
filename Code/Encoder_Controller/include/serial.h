#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include <avr/portpins.h>
#include <stdbool.h>
#include <util/delay.h>

#define BAUD 9600
#define RXD PD0;
#define TXD PD1;
#define XCK PB0;

void serial_initialize(void);
unsigned char serial_receive(void);
void serial_send(unsigned char data, bool sendNewline);
void serial_send_string(char *msg, bool sendNewLine);

#endif // SERIAL_H
