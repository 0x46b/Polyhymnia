#include "serial.h"

void serial_initialize(){
	uint8_t baud = 51;
	UBRRH = (uint8_t) (baud>>8);
	UBRRL = (uint8_t) baud;
	UCSRB = (1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(0<<USBS)|(1<<UCSZ0)|(1<<UCSZ1);
}

unsigned char serial_receive(){
	while(!(UCSRA & (1 << RXC)));
	
	return UDR;
}

void serial_send(unsigned char data, bool sendNewline){
	// Wait for empty transmit buffer
	while(!(UCSRA & (1 << UDRE)));
	
	UDR = data;
	if(sendNewline){
		serial_send('\r', false);
		serial_send('\n', false);
	}
}

void serial_send_string(char* msg, bool sendNewline){
	for (int i = 0; i < strlen(msg); i++){
		serial_send(msg[i], false);
	}
	if(sendNewline){
	serial_send('\r', false);
	serial_send('\n', false);
	}
}