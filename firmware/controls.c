#include "controls.h"
#include <avr/io.h>
#include <util/delay.h>

#define BTNPIN1  3;
#define BTNPIN2  4;
#define BTNPIN3  5;


uint8_t getPinValue(uint8_t a) {

	return ((~PIND >> a) & 1);
}


void setupControls(void) {
	 // LED Outputs
  
	 DDRC |= 0x0F;
     PORTC &= ~(1<<3);
}



uint8_t getButtonState(void) {
	
	// Button panel is charlieplexed so reading buttons is a little difficult
	
  uint8_t buttonState = 0x00;

  DDRD |= (1<<3);
  DDRD &= ~((1<<4) | (1<<5));
  PORTD |= (1<<4) | (1<<5);
  PORTD &= ~(1<<3);

  _delay_ms(1);

  buttonState |= getPinValue(4);
  buttonState <<= 1;
  buttonState |= getPinValue(5);
  buttonState <<= 1;

  _delay_ms(1);
  
  DDRD |= (1<<4);
  DDRD &= ~((1<<3) | (1<<5));
  PORTD |= (1<<3) | (1<<5);
  PORTD &= ~(1<<4);

  _delay_ms(1);

  buttonState |= getPinValue(3);
  buttonState <<= 1;
  buttonState |= getPinValue(5);
  buttonState <<= 1;

  _delay_ms(1);
  
  DDRD |= (1<<5);
  DDRD &= ~((1<<3) | (1<<4));
  PORTD |= (1<<3) | (1<<4);
  PORTD &= ~(1<<5);
  _delay_ms(1);

  buttonState |= getPinValue(3);
  buttonState <<= 1;
  buttonState |= getPinValue(4);
  
 
  
  return buttonState;

}

void setLeds(uint8_t ledState) {
	PORTC &= 0xF8;
  if((ledState < 4) && (ledState > 0)) {
	  PORTC |= (0x04 >> (ledState-1));
  }

}
