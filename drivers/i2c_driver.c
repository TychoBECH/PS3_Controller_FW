/* 
 * File:   i2c_driver.c
 * Author: Tycho Kropf
 * Created on: 2025-04-22
 *
 * Description:
 * TODO
 *
 * Revision History:
 * TODO
 * Version 0.0.1: 
 *
 */

#include "i2c_driver.h"

#define _XTAL_FREQ 64000000

static I2C_Transaction_t i2cTransaction;

void I2C_Init(void) {
	//Code From MCC
	/* CSTR Enable clocking; S Cleared by hardware after Start; MODE 7-bit address; EN disabled; RSEN disabled;  */
	I2C1CON0 = 0x4;
	/* TXU No underflow; CSD Clock Stretching enabled; RXO No overflow; P Cleared by hardware after sending Stop; ACKDT Acknowledge; ACKCNT Not Acknowledge;  */
	I2C1CON1 = 0x80;
	/* ABD enabled; GCEN disabled; ACNT disabled; SDAHT 30 ns hold time; BFRET 8 I2C Clock pulses;  */
	I2C1CON2 = 0x18;
	/* ACNTMD 8 bits are loaded into I2CxCNTL; FME Standard Mode; Address buffers disabled */
	I2C1CON3 = 0x0;
	/* CLK Fosc;  */
	I2C1CLK = 0x1;
	/* WRIF Data byte not detected; CNTIF Byte count is not zero; RSCIF Restart condition not detected; PCIF Stop condition not detected; ACKTIF Acknowledge sequence not detected; ADRIF Address not detected; SCIF Start condition not detected;  */
	I2C1PIR = 0x0;
	/* CNTIE disabled; RSCIE disabled; ACKTIE disabled; SCIE disabled; PCIE disabled; ADRIE disabled; WRIE disabled;  */
	I2C1PIE = 0x0;
	/* BTOIE disabled; BTOIF No bus timeout; NACKIF No NACK/Error detected; BCLIE disabled; BCLIF No bus collision detected; NACKIE disabled;  */
	I2C1ERR = 0x0;
	/* Count register */
	I2C1CNTL = 0x0;
	I2C1CNTH = 0x0;
	/* BAUD 127;  */
	I2C1BAUD = 0x7F;
	/* BTOC Reserved;  */
	I2C1BTOC = 0x0;

	/* Silicon-Errata: Section: 1.3.2 */
	// Refer to erratum DS80000870F: https://www.microchip.com/content/dam/mchp/documents/MCU08/ProductDocuments/Errata/PIC18F27-47-57Q43-Silicon-Errata-and-Datasheet-Clarifications-80000870J.pdf
	I2C1CON0bits.EN = 1;
	__delay_us(1);
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	I2C1PIRbits.SCIF = 0;
	I2C1PIRbits.PCIF = 0;
}

void I2C_Deinit(void) {
	I2C1CON0 = 0x00;
	I2C1CON1 = 0x00;
	I2C1CON2 = 0x00;
	I2C1CON3 = 0x00;
	I2C1CLK = 0x00;
	I2C1PIR = 0x00;
	I2C1PIE = 0x00;
	I2C1ERR = 0x00;
	I2C1CNTL = 0x00;
	I2C1CNTH = 0x00;
	I2C1BAUD = 0x00;
}

I2C_Result_t I2C_Start(void) {
	//Check if buss is in use
	if (i2cTransaction.busy) {
		return I2C_ERROR_BUSY;
	}
	
	i2cTransaction.busy = true;
	//check if it is a TX or RX start
	if(i2cTransaction.txLength > 0){
		I2C1CNT = i2cTransaction.txLength;
	}else if(i2cTransaction.rxLength > 0){
		I2C1CNT = i2cTransaction.rxLength;
	}
	
	//write slave address and read write bit
	I2C1TXB = (i2cTransaction.address << 1) | i2cTransaction.read;
	
	return I2C_OK;
}

void I2C_Stop(void) {

}

void I2C_RepeatedStart(void) {

}

bool I2C_WriteByte(uint8_t data) {

}

uint8_t I2C_ReadByte(bool ack) {

}

void I2C_Service(void){
	
}

