#ifndef BEAMER_H
#define BEAMER_H

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include <stdlib.h>
#include <avr/interrupt.h>

#define POWER				0x0003	// 00 OFF; 01 ON; 02 SUSPEND; 10 DURING START; 11 COOLDOWN; 20 FAULT
#define KEY					0x000A	// 5 byte key code, see manual
#define	TEMPERATURE			0x000C	// see manual
#define INPUT_SOURCE		0x0100	// 10 PC1; 11 PC2; 21 RCA; 22 SVHS
#define INPUT_MODE			0x0101  // 00 NO MODE; 01 PC; E0 NTSC; E2 PAL; E5 PAL60; E6 SECAM
#define FREEZE				0x0102  // 00 OFF; 01 ON
#define AVMUTE				0x0103	// 00 OFF; 01 ON
#define VOLUME				0x0200	// one byte value
#define	BASS				0x0206	// one byte value
#define TREBLE				0x0207  // one byte value
#define PC_BRIGHTNESS		0x0300  // one byte value
#define PC_CONTRAST			0x0301  // one byte value
#define SYNC				0x0302	// one byte value
#define TRACKING			0x0303	// one byte value
#define TRCKBASE			0x0304  // Returns one byte value
#define	COLOR_RED			0x0306  // one byte value
#define COLOR_GREEN			0x0307  // one byte value
#define COLOR_BLUE			0x0308  // one byte value
#define GET_PC_FREQ			0x030A  // two 4-Bit values
#define GET_RESOLUTION		0x030B  // two word value
#define PC_SHARPNESS		0x030D	// one word value
#define RESOLUTION			0x030E	// one byte value
#define VIDEO_BRIGHTNESS	0x0400	// one byte value
#define VIDEO_CONTRAST		0x0401	// one byte value
#define VIDEO_SHARPNESS		0x0402	// one byte value
#define VIDEO_SATURATION	0x0403	// one byte value
#define VIDEO_TINT 			0x0404	// one byte value
#define HOR_POSITION		0x0500	// one word value
#define VERT_POSITION		0x0501	// one word value
#define REAR_PROJECTION		0x0502	// 00 OFF; 01 ON
#define CEILING				0x0503	// 00 OFF; 01 ON
#define COLOR_TEMP			0x0504	// one byte value
#define BLACK_LEVEL			0x0508	// one byte value
#define WHITE_LEVEL			0x0509	// one byte value
#define AUTO_COL_TEMP		0x050A	// 00 AUTO; 01 MANUAL
#define LANGUAGE			0x0600	// 01 ENGLISH; 03 GERMAN; ...
#define POWERSAVE			0x0601	// 00 NO PS; 05 - 3C SET PS
#define SOURCE_PROMPT		0x0603	// 00 OFF; 01 ON
#define BLANK				0x0604	// 00 OFF; 01 ON
#define KEYSTONE			0x060F	// one byte value
#define STARTUP_SCREEN		0x0610	// 00 OFF; 01 ON

void setupProjector(void);
uint8_t setProjectorValue(uint16_t type, uint8_t value);
uint8_t getProjectorValue(uint16_t type);

#endif