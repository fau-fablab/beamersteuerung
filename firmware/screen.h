#pragma once

#include <avr/io.h>
#include <util/delay.h>

uint8_t upCode[25];
uint8_t downCode[25];

void controlScreen(uint8_t direction);
void setupTransmitter(void);
void transmitCode(uint8_t* code, uint8_t length);
void transmit(uint8_t code);
