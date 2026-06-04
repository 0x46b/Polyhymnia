#ifndef ENCODER_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define XTAL 8e6

volatile int8_t enc_delta; // Drehgeberbewegung zwischen
                           // zwei Auslesungen im Hauptprogramm
                            
// Dekodertabelle für wackeligen Rastpunkt
// halbe Auflösung
//const int8_t table[16] PROGMEM = {0,0,-1,0,0,0,0,1,1,0,0,0,0,-1,0,0};    

// Dekodertabelle für normale Drehgeber
// volle Auflösung
const int8_t table[16] PROGMEM = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};

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

#define ENCODER_H
#endif
