/*
 * File:   main.c
 * Author: s1uty
 *
 * Created on 21. April 2025, 18:27
 */


#include <xc.h>
#include "system.h"
#include "i2c_driver.h"

uint8_t data[]={0x01,0b00100001,0b00011111,0b1,0b0,0b0,0b0,0b00100000};

void main(void) {
	System_Init();
	I2C_Init();
	while(1 == 1){
		I2C_Write(0b1110100,data,8);
		while (I2C_isBusy()) {
			I2C_Service();
		}
	}
	return;
}
