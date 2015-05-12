#include "screen.h"
#include <avr/io.h>
#include <util/delay.h>

#define TXDDR DDRD
#define TXPORT PORTD
#define TXPIN 2



uint8_t upCode[25] = {2, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0};
uint8_t downCode[25] = {2, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0};
// uint8_t stopCode[25] = {2, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};



void setupTransmitter() {
  TXDDR |= (1<<TXPIN);
  TXPORT &= ~(1<<TXPIN);
}


void transmitCode(uint8_t* code, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
      transmit(code[i]);
    }
}

void transmit(uint8_t code) {
  if (code == 0) {
	TXPORT |= (1<<TXPIN);
    _delay_ms(0.275);
	TXPORT &= ~(1<<TXPIN);
    _delay_ms(0.825);
  } else if (code == 1) {
	TXPORT |= (1<<TXPIN);
    _delay_ms(0.825);
	TXPORT &= ~(1<<TXPIN);
    _delay_ms(0.275);
  } else if (code == 2) {
	TXPORT |= (1<<TXPIN);
    _delay_ms(0.275);
	TXPORT &= ~(1<<TXPIN);
    _delay_ms(8.525);
  }
}