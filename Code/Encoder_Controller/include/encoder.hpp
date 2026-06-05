#ifndef ENCODER_H
#define ENCODER_H
#include <inttypes.h>
#include <avr/pgmspace.h>

struct EncoderConfiguration {
	uint8_t encoderId;
	uint8_t phaseA;
	uint8_t phaseB;
	volatile uint8_t *port;
	volatile uint8_t *pin;
};

class Encoder {
	private:
		static const int8_t STATETABLE[16];
		EncoderConfiguration _config;
	
		int _currentOffset;
		volatile uint8_t _oldState;
			
	public:
		void Initialize(uint8_t encoderId, volatile uint8_t *pin, volatile uint8_t *port, uint8_t phaseA, uint8_t phaseB);
		int Read(uint8_t step);
		void Tick();
};

#endif