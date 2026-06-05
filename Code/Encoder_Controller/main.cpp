#include "spi.hpp"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#define F_CPU 2000000UL
#include "encoder.hpp"
#include <util/delay.h>

#define XTAL 8e6
#define LEDS1_DDR DDRD
#define LEDS1 PORTD

Encoder encoders[8];
SPIConnection spi;

ISR(TIMER0_COMP_vect) {
  encoders[0].Tick();
  encoders[1].Tick();
  // for(Encoder currentEncoder : encoders){
  //  currentEncoder.Tick();
  // }
}

ISR(SPI_STC_vect) { spi.Read(); }

void InitializeEncoderTimer(void) { // nur Timer 0 initialisieren
  TCCR0 = (1 << WGM01) | (1 << CS01) | (1 << CS00); // CTC, XTAL / 64
  OCR0 = (uint8_t)20;                               // 1ms
  TIMSK |= 1 << OCIE0;
}

// Just to be sure we're ready :)
void StartNiceLittleLEDShow() {
  LEDS1 = 0x00;
  for (int i = 0; i < 8; i++) {
    LEDS1 = ~(1 << i);
    _delay_ms(100);
  }
  LEDS1 = 0xFF;
}

void setup() {
  encoders[0].Initialize(1, &PINA, &PORTA, (1 << PA1), (1 << PA3));
  encoders[1].Initialize(2, &PINA, &PORTA, (1 << PA4), (1 << PA5));
  DDRA &= (0 << PA1) | (0 << PA3) | (0 << PA4) | (0 << PA5);

  LEDS1_DDR = 0xFF;
  StartNiceLittleLEDShow();
  InitializeEncoderTimer();
  // spi.Initialize(false);
}

int main(void) {
  setup();
  sei();

  int32_t val1 = 0;
  int32_t val2 = 0;

  while (1) {
    cli();
    val1 += encoders[0].Read(1);
    val2 += encoders[1].Read(1);
    sei();
    LEDS1 = ~val2;
  }
}
