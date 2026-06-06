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
  for (Encoder currentEncoder : encoders) {
    currentEncoder.Tick();
  }
}

ISR(SPI_STC_vect) { spi.Read(); }

void InitializeEncoderTimer(void) { // nur Timer 0 initialisieren
  TCCR0 = (1 << WGM01) | (1 << CS01) | (1 << CS00); // CTC, prescaler 64
  OCR0 = (uint8_t)(XTAL / 64.0 * 1e-3 - 0.5);       // 1ms // 1ms
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
  // Filter Cutoff
  encoders[0].Initialize(1, &PINA, &PORTA, (1 << PA0), (1 << PA1));
  // Filter Resonance
  encoders[1].Initialize(2, &PINA, &PORTA, (1 << PA2), (1 << PA3));

  // OSC1 Type
  encoders[2].Initialize(2, &PINC, &PORTC, (1 << PC0), (1 << PC1));
  // OSC1 Detune
  encoders[3].Initialize(2, &PINC, &PORTC, (1 << PC2), (1 << PC3));

  // OSC2 Type
  encoders[4].Initialize(2, &PINC, &PORTC, (1 << PC4), (1 << PC5));
  // OSC2 Detune
  encoders[5].Initialize(2, &PINC, &PORTC, (1 << PC6), (1 << PC7));

  // OSC3 Type
  // encoders[6].Initialize(2, &PIND, &PORTD, (1 << PD0), (1 << PD1));
  // OSC3 Detune
  // encoders[7].Initialize(2, &PIND, &PORTD, (1 << PD2), (1 << PD3));

  // Set data directory registers
  DDRA &= ~(1 << PA0) | ~(1 << PA1) | ~(1 << PA2) | ~(1 << PA3);
  DDRC &= 0;
  // DDRD &= ~(1 << PD0) | ~(1 << PD1) | ~(1 << PD2) | ~(1 << PD3);

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
    LEDS1 = ~val1;
  }
}
