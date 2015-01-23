#include "beamer.h"
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include <stdlib.h>
#include <avr/interrupt.h>

#define BEAMER_BAUD_RATE      9600



void setupProjector(void) {
	uart_init(UART_BAUD_SELECT(BEAMER_BAUD_RATE,F_CPU)) ;
}

uint8_t setProjectorValue(uint16_t type, uint8_t value) {
	uart_flush();
  uint8_t checksum = 0;
  uart_putc(0x1B);
  uart_putc(0x07);
  checksum += 0x07;
  uart_putc(0x01);
  checksum += 0x01;
  uart_putc(type >> 8);
  checksum += (type >> 8);
  uart_putc(type & 0xFF);
  checksum += (type & 0xFF);
  uart_putc(value);
  checksum += value;
  checksum = 0xFF - checksum + 1;
  uart_putc(checksum);
  
  _delay_ms(50);
  
  uint8_t counter = 0;
  uint8_t retValue = 0;
  
  while(uart_available()) {
    uint8_t readValue = uart_getc();
    if(readValue == 0x1B) {
      counter = 0;
	  checksum = 0;
    }
	if(counter != 5) {
	
	checksum += readValue;
}
    if(counter == 5) {
		checksum = 0xFF - checksum + 1;
		if(readValue == checksum) {
			
    	uart_putc(0x06);
	}
    }
	counter++;
  }
  
  return retValue;
}

uint8_t getProjectorValue(uint16_t type) {
	uart_flush();
  uint8_t checksum = 0;
  uart_putc(0x1B);
  uart_putc(0x06);
  checksum += 0x06;
  uart_putc(0x02);
  checksum += 0x02;
  uart_putc(type >> 8);
  checksum += (type >> 8);
  uart_putc(type & 0xFF);
  checksum += (type & 0xFF);
  checksum = 0xFF - checksum + 1;
  uart_putc(checksum);
  
  _delay_ms(50);
  
  uint8_t counter = 0;
  uint8_t retValue = 0;
  
  while(uart_available()) {
    uint8_t readValue = uart_getc();
    if(readValue == 0x1B) {
      counter = 0;
	  checksum = 0;
    }
	if(counter != 7) {
	
	checksum += readValue;
}
    if(counter == 6) {
      retValue = readValue;   
    } else if(counter == 7) {
		checksum = 0xFF - checksum + 1;
		if(readValue == checksum) {
			
    	uart_putc(0x06);
	}
    }
	counter++;
  }
  

  
  return retValue;
}