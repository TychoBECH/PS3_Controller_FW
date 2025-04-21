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
	//Unlock PPS Datasheet P.380 Example 23-8
	GIE = 0; //Suspend interrupts
	PPSLOCK = 0x55; //Required sequence
	PPSLOCK = 0xAA; //Required sequence
	PPSLOCKbits.PPSLOCKED = 0; //Clear PPSLOCKED bit
	GIE = 1; //Restore interrupts

	//Pins for UART
	//TX -> RC6 RX-> RC7
	U1RXPPS = 0b010111; // RC7 to UART RX Port C = 0b010000 & Pin 7 = 0b111
	RC6PPS = 0x15; //UART1 TX to RC6

	//Pins for SPI
	//CLK -> RB1, DO -> RB2, DI -> RB3, SS -> RB0
	RB1PPS = 0x1D; //0x1D -> SPI1 SCK
	SPI1SCKPPS = 0b001001;
	RB2PPS = 0x1E; //0x1E -> SPI1 SDO
	SPI1SDIPPS = 0b001011; //0b010000-> PORTC, 0b100 pin Nr4 -> RC4
	SPI1SSPPS = 0b001000; // Only needed if the MCU is a SPI Slave
	RB0PPS = 0x1F;

	//Pins for i2c
	//SCL -> RC3, SDA -> RC4;
	I2C1SCLPPS = 0b010011;
	RC3PPS = 0x20;
	I2C1SDAPPS = 0b010100;
	RC4PPS = 0x21;

	//Lock PPS
	GIE = 0; //Suspend interrupts
	PPSLOCK = 0x55; //Required sequence
	PPSLOCK = 0xAA; //Required sequence
	PPSLOCKbits.PPSLOCKED = 1; //Set PPSLOCKED bit
	GIE = 1; //Restore interrupts
}