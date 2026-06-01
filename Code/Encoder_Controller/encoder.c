#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
 
#define XTAL        8e6                 // 8MHz

#define ENCODER_PIN PINA                // an Pinbelegung anpassen
#define PHASE_A     (1<<PA1)
#define PHASE_B     (1<<PA3)
 
#define LEDS_DDR    DDRC
#define LEDS        PORTC               // LEDs gegen Vcc geschaltet
  
volatile int8_t enc_delta;              // Drehgeberbewegung zwischen
                                        // zwei Auslesungen im Hauptprogramm

// Dekodertabelle für wackeligen Rastpunkt
// halbe Auflösung
const int8_t table[16] PROGMEM = {0,0,-1,0,0,0,0,1,1,0,0,0,0,-1,0,0};    

// Dekodertabelle für normale Drehgeber
// volle Auflösung
//const int8_t table[16] PROGMEM = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};    
 
ISR( TIMER0_COMP_vect ) {           // 1ms fuer manuelle Eingabe
    static int8_t last=0;           // alten Wert speichern
    uint8_t tmp;

    tmp = ENCODER_PIN;
    last = (last << 2)  & 0x0F;
    if (tmp & PHASE_A) last |= 2;
    if (tmp & PHASE_B) last |= 1;
    enc_delta += pgm_read_byte(&table[last]);
}

void encode_init( void ) {            // nur Timer 0 initialisieren
  TCCR0 = (1<<WGM01) | (1<<CS01) | (1<<CS00);     // CTC, XTAL / 64
  OCR0 = (uint8_t)(XTAL / 64.0 * 1e-3 - 0.5);     // 1ms
  TIMSK |= 1<<OCIE0;
}
 
int8_t encode_read( uint8_t step ) {        // Encoder auslesen
  int8_t val;

  // atomarer Variablenzugriff  
  cli();
  val = enc_delta;
  enc_delta = 0;
  sei();
  return val >> (step / 2);
}

int main( void ) {
  int32_t val = 0;

  PORTA |= PHASE_A | PHASE_B;       // activate internal pull up resistors
  LEDS_DDR = 0xFF;
  encode_init();
  sei();
 
  while(1){
    val += encode_read(1);      
    LEDS = ~val;
  }
}
