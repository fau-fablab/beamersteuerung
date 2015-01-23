#ifndef CONTROLS_H
#define CONTROLS_H

#include <avr/io.h>
#include <util/delay.h>

uint8_t getPinValue(uint8_t a);
void setupControls(void);
uint8_t getButtonState(void);
void setLeds(uint8_t ledState);

#endif