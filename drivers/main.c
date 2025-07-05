/*
 * File:   main.c
 * Author: s1uty
 *
 * Created on 21. April 2025, 18:27
 */


#include <xc.h>
#include "system.h"
#include "i2c_driver.h"
#include "BQ27427.h"

uint8_t data[] = {
	0x01, //Adress to write to
	0x81, //SSD=1 -> Normal operation									01
	0b00011111, //Output EN1-EN5 = 1 -> Enabled							02
	0b1, //Output EN6 = 1 -> Enabled									03
	0b00101010, //Mode -> Current Controll								04
	0b00101010, //Mode -> Current controll								05
	0b0, //No Function
	0b00000001, //Full current -> 10mA?
	0b00000000, //Hold Function
	0x00, //V_BM default no Idea what this does...
	0x00, //No Function
	0x00, //Unlock Register -> needs 0xA5 to unlock
	0x00, //PWM correction -> Non applied
	0x00, //Pattern State 1
	0x00, //Pattern State 2
	0x00, //Pattern State 3												0F
	0x7F,0x7F,0x7F,0x7F,0x7F,0x7F, //OUT1 Full current					10 - 15										
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //				16 - 1F
	//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //Color 1 Setting Register  -> Not needed due to mode Current
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //Color 2 Setting Register		20 - 25
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //				26 - 2F
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //Color 3 Setting Register		30 - 35
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //				36 - 3F
	0xFF, 0x07, //PWM to 50% OUT 1										40 - 41
	0xFF, 0x07, //PWM to 50% OUT 2										
	0xFF, 0x07, //PWM to 50% OUT 3
	0xFF, 0x07, //PWM to 50% OUT 4
	0xFF, 0x07, //PWM to 50% OUT 5
	0xFF, 0x07, //PWM to 50% OUT 6										4A - 4B
	0x00,0x00,0x00,0x00,0x00,0x00,//									4C - 51
	0xC5,//Update Collor
	0xC5 //Update PWM
	
};
uint8_t is31fl3296_init_data[] = {
	0x01, //Start adress to write to
	0x01, // 0x00: Shutdown (Normal mode)
	0xFF, // 0x01: Enable LEDs 1?6
	0xFF, // 0x02: Enable LEDs 7?12
	0x3F, // 0x03: Enable LEDs 13?18

	// 0x04?0x23: Reserved (32 bytes)
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	// 0x24?0x35: PWM values (all = 0x1A = ~10% brightness)
	0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A,
	0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A,
	0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A,

	0x00 // 0x36: Update register
};

void main(void) {
	System_Init();
	I2C_Init();
	LATAbits.LATA1 = 1;
	static uint16_t asdf = 0;
	while (1) {
		asdf = bq27427_get_voltage();
		__delay_ms(1);
		NOP();
	}
	return;
}
