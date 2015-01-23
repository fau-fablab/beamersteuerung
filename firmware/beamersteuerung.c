#include "screen.h"
#include "controls.h"
#include "beamer.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define downButton 0x01
#define srcButton 0x02
#define upButton 0x04
#define offButton 0x08
#define onButton 0x20


void setNextSource(void) {
	uint8_t currentSource = getProjectorValue(INPUT_SOURCE);
	if(currentSource == 10) {
		setProjectorValue(INPUT_SOURCE, 11);
	} else if(currentSource == 11) {
		setProjectorValue(INPUT_SOURCE, 21);
	} else if(currentSource == 21) {
		setProjectorValue(INPUT_SOURCE, 22);
	} else if(currentSource == 22) {
		setProjectorValue(INPUT_SOURCE, 10);
	}
}



void getProjectorState(void) {
	uint8_t projectorState = getProjectorValue(POWER);
	if(projectorState == 0x01) {
		setLeds(1);
	} else if(projectorState == 0x10) {
		setLeds(2);
	} else if(projectorState == 0x11) {
		setLeds(3);
	} else {
		setLeds(0);
	}
}

int main(void) {

	setupControls();
	
	setupTransmitter();
	
	setupProjector();
	
	sei();
	
	setLeds(1);
	_delay_ms(1000);
	setLeds(0);

  
	while(1) {
	if(getButtonState() & downButton) {
		transmitCode(downCode, 25);
	} else if(getButtonState() & upButton) {
			transmitCode(upCode, 25);
	} else if(getButtonState() & srcButton) {
		setNextSource();
	} else if(getButtonState() & onButton) {
		setProjectorValue(POWER, 1);
	} else if(getButtonState() & offButton) {
		setProjectorValue(POWER, 0);
	}
	getProjectorState();
	_delay_ms(500);
	
}
}
