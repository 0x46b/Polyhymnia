#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include <avr/portpins.h>
#include <stdbool.h>
#include <util/delay.h>

#define BAUD 9600
// #define USE_2X

void serial_initialize(void);
char serial_receive(void);
void serial_send(char data, bool sendNewline);
void serial_send_string(char *msg, bool sendNewLine);

#endif // SERIAL_H
