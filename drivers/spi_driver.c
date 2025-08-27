/* 
 * File:   spi_driver.c
 * Author: Tycho Kropf
 * Created on: 2025-08-27
 *
 * Description:
 * TODO
 *
 * Revision History:
 * TODO
 * Version 0.0.1: 
 *
 */

void SPI_Init(void) {
	SPI1CON0 = 0b00000011;
	SPI1CON1 = 0b01000100;
	SPI1CON2 = 0b00000000;
	SPI1CLK = 0x01; // Use HFINTOSC 64MHz
	SPI1BAUD = 31;  //Approx 1MHz -> 64MHz/(2*(n+1)))-> n=31
	SPI1TCNT = 0; // no data jet to send
	SPI1TWIDTH = 0; //Use default 8 bit size per transmission
	//SPI1STATUS does not get touched -> Read only for most information
	SPI1INTE = 0x00; // No interupts needed
	SPI1INTF = 0x00; //No interupts hapend yet
	
}

void SPI_DeInit(void) {
	//TODO Write als register definitions according to datasheet
}

void SPI_Start(void) {

}

void SPI_Stop(void) {

}

void SPI_WriteByte(uint8_t data) {

}

void SPI_WriteNByte(uint8_t *data_array, uint8_t size) {

}

uint8_t SPI_TransferByte(uint8_t data) {


}

void SPI_TransferNByte(uint8_t *buffer, uint8_t size) {

}