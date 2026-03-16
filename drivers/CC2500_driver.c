/* 
 * File:   CC2500_driver.c
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
#include "CC2500_driver.h"

void CC2500_init(void) {
	CC2500_WriteRegister(CC2500_IOCFG0, 0x06); //Set GDO0 to Asserts when sync word has been sent / received, and de-asserts at the end of the packet.
	CC2500_WriteRegister(CC2500_PKTCTRL0, 0x05); //Variable packet length mode, CRC calculation in TX and RX enabled
	CC2500_WriteRegister(CC2500_CHANNR, 0x03); //Set to Channel 3
	CC2500_WriteRegister(CC2500_FSCTRL1, 0x08); //intermideat frequency of 203.125 kHz -> No idea what this does...
	CC2500_WriteRegister(CC2500_FREQ2, 0x5D); //set carrier frequency to 2.425 GHz
	CC2500_WriteRegister(CC2500_FREQ1, 0x44); //
	CC2500_WriteRegister(CC2500_MDMCFG4, 0x86); //
	CC2500_WriteRegister(CC2500_MDMCFG3, 0x83);
	CC2500_WriteRegister(CC2500_MDMCFG2, 0x03);
	CC2500_WriteRegister(CC2500_MDMCFG1, 0x23);
	CC2500_WriteRegister(CC2500_MDMCFG0, 0x3B);
	CC2500_WriteRegister(CC2500_DEVIATN, 0x44);
	CC2500_WriteRegister(CC2500_MCSM0, 0x18);
	CC2500_WriteRegister(CC2500_FOCCFG, 0x16);
	CC2500_WriteRegister(CC2500_FSCAL1, 0x00);
	CC2500_WriteRegister(CC2500_FSCAL0, 0x11);
}

void CC2500_WriteRegister(uint8_t reg, uint8_t value) {
	MSSP1_SPI_Start();
	MSSP1_SPI_WriteByte(reg | CC2500_SingleWrite);
	MSSP1_SPI_WriteByte(value);
	MSSP1_SPI_Stop();
}

uint8_t CC2500_GetState(void) {
	MSSP1_SPI_Start();
	uint8_t state = MSSP1_SPI_TransferByte(CC2500_Command_SNOP);
	MSSP1_SPI_Stop();
	state = (state >> 4) & 0x07; // Move bits 6:4 to 3:0 and mask them -> These are the state of the chip
	return state;
}

uint8_t CC2500_GetRxFifoSpace(void) {
	MSSP1_SPI_Start();
	uint8_t space = MSSP1_SPI_TransferByte(CC2500_Command_SNOP);
	MSSP1_SPI_Stop();
	space = space & 0x07;
	return space;
}

uint8_t CC2500_GetTxFifoSpace(void) {
	MSSP1_SPI_Start();
	uint8_t space = MSSP1_SPI_TransferByte(CC2500_Command_SNOP);
	MSSP1_SPI_Stop();
	space = space & 0x07;
	return space;
}

void CC2500_SetMode(CC2500_Command_t mode) {
	MSSP1_SPI_Start();
	MSSP1_SPI_WriteByte(mode);
	MSSP1_SPI_Stop();
}

void MSSP1_SPI_Start(void) {
	SPI1_Open(HOST_CONFIG);
	IO_RB0_SetLow();
}

void MSSP1_SPI_Stop(void){
	IO_RB0_SetHigh();
	SPI1_Close();
}