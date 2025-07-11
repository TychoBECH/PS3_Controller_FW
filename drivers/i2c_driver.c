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
	I2C1CON2 = 0x08;
	/* ACNTMD 8 bits are loaded into I2CxCNTL; FME Standard Mode*/
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

I2C_Result_t I2C_Write(uint8_t address, uint8_t *txBuffer, uint8_t txLength) {
	//Check if busy:
	if (0 != i2cTransaction.busy) {
		return I2C_ERROR_BUSY;
	}

	i2cTransaction.busy = 1;
	i2cTransaction.address = address;
	i2cTransaction.read = 0;
	i2cTransaction.txBuffer = txBuffer;
	i2cTransaction.txLength = txLength;
	i2cTransaction.txIndex = 0;
	
	i2cTransaction.rxBuffer = NULL;
	i2cTransaction.rxIndex = 0;
	i2cTransaction.rxLength = 0;

	I2C1CON1bits.ACKCNT = 0;

	i2cTransaction.state = I2C_STATE_START;
	return I2C_OK;
}

I2C_Result_t I2C_Read(uint8_t address, uint8_t *rxBuffer, uint8_t rxLength) {
	//Check if busy:
	if (0 != i2cTransaction.busy) {
		return I2C_ERROR_BUSY;
	}

	i2cTransaction.busy = 1;
	i2cTransaction.address = address;
	i2cTransaction.read = 1;
	i2cTransaction.rxBuffer = rxBuffer;
	i2cTransaction.rxLength = rxLength;
	i2cTransaction.rxIndex = 0;

	i2cTransaction.txLength = 0;

	I2C1CON1bits.ACKCNT = 0;

	i2cTransaction.state = I2C_STATE_START;
	return I2C_OK;
}

I2C_Result_t I2C_WriteRead(uint8_t address, uint8_t *txBuffer, uint8_t txLength, uint8_t *rxBuffer, uint8_t rxLength) {
	//Check if busy:
	if (0 != i2cTransaction.busy) {
		return I2C_ERROR_BUSY;
	}

	i2cTransaction.busy = 1;
	i2cTransaction.address = address;
	i2cTransaction.read = 0; //WriteRead starts with Write
	i2cTransaction.rxBuffer = rxBuffer;
	i2cTransaction.rxLength = rxLength;
	i2cTransaction.rxIndex = 0;
	i2cTransaction.txBuffer = txBuffer;
	i2cTransaction.txLength = txLength;
	i2cTransaction.txIndex = 0;

	i2cTransaction.state = I2C_STATE_START;

	I2C1CON1bits.ACKCNT = 0;
	return I2C_OK;
}

I2C_Result_t I2C_Service(void) {
	//Check if action is needed and return if not
	if (!i2cTransaction.busy) {
		return I2C_OK;
	}

	//actions are needed -> Lets see what
	switch (i2cTransaction.state) {
		case I2C_STATE_START:
			//-> ADB is enabled -> Load address
			I2C1ADB1 = (uint8_t) (i2cTransaction.address << 1) | i2cTransaction.read;
			//Check if pure read
			if (i2cTransaction.txLength > 0) {
				//load number of bits to be transmitted
				I2C1CNTH = (i2cTransaction.txLength >> 8);
				I2C1CNTL = (i2cTransaction.txLength & 0xFF);
				//Load first byte
				I2C1TXB = i2cTransaction.txBuffer[i2cTransaction.txIndex++];
				i2cTransaction.state = I2C_STATE_SEND_DATA;
			} else if (i2cTransaction.rxLength > 0) {
				//only load how much data should be read
				I2C1CNTH = (i2cTransaction.rxLength >> 8);
				I2C1CNTL = (i2cTransaction.rxLength & 0xFF);
				i2cTransaction.state = I2C_STATE_RECEIVE_DATA;
			}
			//send start and address
			I2C1CON0bits.S = 1;
			break;

		case I2C_STATE_SEND_DATA:
			//Check for ACK
			if (I2C1ERRbits.NACKIF) {
				//Terminate Transmission
				I2C1ERRbits.NACKIF = 0;
				I2C1CON1bits.ACKCNT = 1;
				i2cTransaction.state = I2C_STATE_STOP;
				return I2C_ERROR_NACK; //No more actions needed in this transmission
			}

			//Check if buffer empty
			if (I2C1STAT1bits.TXBE) {
				//Check if more data needs to be sent
				if (0 != I2C1CNT) {
					//Load new data
					I2C1TXB = i2cTransaction.txBuffer[i2cTransaction.txIndex++];
				} else {
					/* last data byte has already been loaded & CNT is counting down */
					if (i2cTransaction.rxLength > 0U) /* Write?Read combined ? */ {
						/* wait for byte?counter to hit zero */
						if (I2C1PIRbits.CNTIF) {
							I2C1CON0bits.RSEN = 1;
							I2C1PIRbits.CNTIF = 0;
							I2C1PIRbits.SCIF = 0;
							i2cTransaction.state = I2C_STATE_RESTART;
						}
					} else {
						I2C1CON1bits.P = 1;
						I2C1CON1bits.ACKCNT = 1;
						i2cTransaction.state = I2C_STATE_STOP;
					}
				}
			}
			break;
		case I2C_STATE_RESTART:
			if ((I2C1PIRbits.RSCIF) || (I2C1CON0bits.RSEN == 0)) {
				I2C1PIRbits.RSCIF = 0; 

				I2C1ADB1 = (uint8_t) (i2cTransaction.address << 1) | 1U; //Load address with read bit
				I2C1CNTH = (uint8_t) (i2cTransaction.rxLength >> 8);
				I2C1CNTL = (uint8_t) i2cTransaction.rxLength;

				I2C1CON1bits.ACKCNT = 0;

				I2C1CON0bits.S = 1;

				i2cTransaction.state = I2C_STATE_RECEIVE_DATA;
			}
			break;
		case I2C_STATE_RECEIVE_DATA:

			if (I2C1PIRbits.CNTIF) {
				I2C1PIRbits.CNTIF = 0;
				I2C1CON1bits.P = 1;
				i2cTransaction.state = I2C_STATE_STOP;
				break;
			}

			if (PIR7bits.I2C1RXIF) {
				i2cTransaction.rxBuffer[i2cTransaction.rxIndex++] = I2C1RXB;
				PIR7bits.I2C1RXIF = 0;
			}

			if ((I2C1CNTH == 0) && (I2C1CNTL == 1)) {
				I2C1CON1bits.ACKCNT = 1;
			}
			break;
		case I2C_STATE_STOP:
			if (I2C1PIRbits.PCIF) {
				I2C1PIRbits.PCIF = 0;
				i2cTransaction.busy = 0;
				i2cTransaction.state = I2C_STATE_IDLE;
			}
			break;
		default: //Catch all if someting has gone wrong
			return I2C_ERROR_UNKNOWN;
			break;
	}
	return I2C_OK;
}

bool I2C_isBusy(void) {
	return i2cTransaction.busy;
}

