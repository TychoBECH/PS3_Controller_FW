/* 
 * File:   pps_driver.h
 * Author: Tycho Kropf
 * Created on: 2024-12-31
 *
 * Description:
 * TODO
 *
 * Revision History:
 * TODO
 * Version 0.0.1: 
 *
 */

#include "pps_driver.h"

void PPS_Init(void) {
	//Unlock PPS Datasheet P.171 Example 18-4
	GIE = 0; //Suspend interrupts
	PPSLOCK = 0x55; //Required sequence
	PPSLOCK = 0xAA; //Required sequence
	PPSLOCKbits.PPSLOCKED = 0; //Clear PPSLOCKED bit
	GIE = 1; //Restore interrupts

	//Pins for UART
	//TX -> RC,7 RX-> RB0
	RX1PPS = 0b001000;
	RC7PPS = 0x0E;

	//Pins for SPI
	//CLK -> RC5, DO -> RC6, Di -> RC4, SS -> RC1
	RC5PPS = 0x15; //0x15 -> SCL1/SCK1
	SSP1CLKPPS = 0b010101;
	RC6PPS = 0x16; //0x16 -> SDA1/SDO1
	SSP1DATPPS = 0b010100; //0b010000-> PORTC, 0b100 pin Nr4 -> RC4
	SSP1SSPPS = 0b010001; // Same explalnation as above ie: RC1

	//Pins for i2c
	//SCL -> RB1, SDA -> RB3;
	SSP2CLKPPS = 0b001001;
	RB1PPS = 0x17;
	SSP2DATPPS = 0b001011;
	RB3PPS = 0x18;

	//maybe pins for Timer / PWM


	//Lock PPS
	GIE = 0; //Suspend interrupts
	PPSLOCK = 0x55; //Required sequence
	PPSLOCK = 0xAA; //Required sequence
	PPSLOCKbits.PPSLOCKED = 1; //Set PPSLOCKED bit
	GIE = 1; //Restore interrupts
}