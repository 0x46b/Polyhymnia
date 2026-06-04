#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "encoder.h"

#define XTAL        8e6                 // 8MHz
#define ENCODER_PIN PINA                // an Pinbelegung anpassen
#define PHASE_A     (1<<PA1)
#define PHASE_B     (1<<PA3)
 
#define LEDS_DDR    DDRD
#define LEDS        PORTD               // LEDs gegen Vcc geschaltet
     
 
ISR( TIMER0_COMP_vect ) {           // 1ms fuer manuelle Eingabe
    static int8_t last=0;           // alten Wert speichern
    uint8_t tmp;

    tmp = ENCODER_PIN;
    last = (last << 2)  & 0x0F;
    if (tmp & PHASE_A) last |= 2;
    if (tmp & PHASE_B) last |= 1;
    enc_delta += pgm_read_byte(&table[last]);
}


int main( void ) {
  int32_t val = 0;

  PORTA |= PHASE_A | PHASE_B;       // activate internal pull up resistors
  LEDS_DDR = 0xFF;
  LEDS = 0x00;
  _delay_ms(5000);
  encode_init();
  sei();
 
  while(1){
    val += encode_read(1);      
    LEDS = ~val;
  }
}
