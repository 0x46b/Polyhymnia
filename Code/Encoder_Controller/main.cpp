#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#define F_CPU 2000000UL
#include <util/delay.h>
#include "include/encoder.h"


#define XTAL 8e6 
#define LEDS_DDR    DDRD
#define LEDS        PORTD

Encoder encoders[8];

ISR( TIMER0_COMP_vect ) {     
	encoders[0].Tick();      
	//for(Encoder currentEncoder : encoders){
		//currentEncoder.Tick();
	//}
}

void InitializeEncoderTimer( void ) {            // nur Timer 0 initialisieren
	TCCR0 = (1<<WGM01) | (1<<CS01) | (1<<CS00);     // CTC, XTAL / 64
	OCR0 = (uint8_t)77;     // 1ms
	TIMSK |= 1<<OCIE0;
}

int main(void)
{
	encoders[0].Initialize(1, &PINA, &PORTA, (1<<PA1), (1<<PA3));
	DDRA &= (0<<PA1) | (0<<PA3);
    LEDS_DDR = 0xFF;
    LEDS = 0x00;
    _delay_ms(5000);
    InitializeEncoderTimer();
    sei();
	
    int32_t val = 0;
    while(1){
		cli();
	    val += encoders[0].Read(1);
		sei();
	    LEDS = ~val;
    }
}

