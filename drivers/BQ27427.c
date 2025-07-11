/* 
 * File:   BQ27427.c
 * Author: Tycho Kropf
 * Created on: 2025-07-03
 *
 * Description:
 * TODO
 *
 * Revision History:
 * TODO
 * Version 0.0.1: 
 *
 */

#include "BQ27427.h"

static bq27427_status_t bq27427Status;

void bq27427_send_subcomand(uint16_t subcmd) {
	//Prepair the package to be sent over i2c
	uint8_t data[3];
	data[0] = 0x00;
	data[1] = subcmd & 0xFF;
	data[2] = subcmd >> 8;

	I2C_Write(BQ27427_ADDRESS, data, sizeof (data));
	while (I2C_isBusy()) {
		I2C_Service();
	}
}

void bq27427_send_subcomand_with_data(uint16_t subcmd, uint8_t *data, uint8_t length) {

}

void bq27427_write_word(uint8_t reg, uint16_t data) {
	uint8_t intermidiate[3];
	intermidiate[0] = reg;
	intermidiate[1] = (uint8_t)(data & 0xFF);
	intermidiate[2] = (uint8_t)data>>8;
	I2C_Write(BQ27427_ADDRESS, intermidiate, sizeof (intermidiate));
	while (I2C_isBusy()) {
		I2C_Service();
	}
}

void bq27427_send_command(uint8_t command) {

}

uint16_t bq27427_read_word(uint8_t reg) {
	uint8_t intermediat[2];
	I2C_WriteRead(BQ27427_ADDRESS, &reg, 1, intermediat, 2); // &reg instead of reg
	while (I2C_isBusy()) {
		I2C_Service();
	}
	return (uint16_t)(intermediat[0] | (intermediat[1] << 8)); // LSB first
}

uint16_t bq27427_get_voltage(void) { //in mV
	uint16_t voltage = 0;
	voltage = bq27427_read_word(BQ27427_CMD_Voltage);
	return voltage;
}

int16_t bq27427_get_current(void) { //in mA
	int16_t current = 0;
	current = (int16_t)bq27427_read_word(BQ27427_CMD_AverageCurrent);
	return current;
}

uint16_t bq27427_get_temperature(void) { //in 0.1°C
	uint16_t temperature = 0;
	temperature = bq27427_read_word(BQ27427_CMD_Temperature)-2731;
	return temperature;
}

uint8_t bq27427_get_state_of_charge(void) { //in %
	uint8_t state_of_charge = 0;
	state_of_charge = (uint8_t)bq27427_read_word(BQ27427_CMD_StateOfCharge);
	return state_of_charge;
}

void bq27427_update_status(void){
	bq27427Status.voltage = bq27427_get_voltage();
	bq27427Status.temperature = bq27427_get_temperature();
	bq27427Status.soc = bq27427_get_state_of_charge();
}

void bq27427_unseal(void){
	uint8_t data[]={0x00,0x00,0x80};
	I2C_Write(BQ27427_ADDRESS,data, 3);
	while (I2C_isBusy()) {
		I2C_Service();
	}
	I2C_Write(BQ27427_ADDRESS,data, 3);
	while (I2C_isBusy()) {
		I2C_Service();
	}
}

void bq27427_enter_config_update(void){
	uint16_t temp_flags = 0;
	bq27427_send_subcomand(BQ27427_CTL_SET_CFGUPDATE);
	do{
		temp_flags = bq27427_read_word(BQ27427_CMD_Flags);
		__delay_ms(10);
	}while((temp_flags & 0b10000) == 0);
	NOP();
}

void bq27427_set_design_capatity(uint16_t capacity){
	uint8_t data[]= {0x61,0x00};
	//enable block data memory control
	I2C_Write(BQ27427_ADDRESS,data,2);
	while (I2C_isBusy()) {
		I2C_Service();
	}
	
	// access the State subclass (82 decimal, 0x52 hex) containing the Design Capacity
	data[0] = 0x3E;
	data[1] = 0x52;
	I2C_Write(BQ27427_ADDRESS,data,2);
	while (I2C_isBusy()) {
		I2C_Service();
	}
	
	//block offset location using DataBlock() command (0x3F)
	data[0] = 0x3F;
	data[1] = 0x00;
	I2C_Write(BQ27427_ADDRESS,data,2);
	while (I2C_isBusy()) {
		I2C_Service();
	}
	
	//read back old checksum
	uint8_t OLD_Csum = 0;
	uint8_t temp = 0x60;
	I2C_WriteRead(BQ27427_ADDRESS,&temp,1,&OLD_Csum,1);
	while (I2C_isBusy()) {
		I2C_Service();
	}
	
	//read back design capacity
	uint8_t OLD_DesCap[2];
	temp = 0x46;
	I2C_WriteRead(BQ27427_ADDRESS,&temp,1,OLD_DesCap,2);
	while (I2C_isBusy()) {
		I2C_Service();
	}
			
	uint8_t capacity_array[3];
	capacity_array[0]=0x46;
	capacity_array[1] = (uint8_t)(capacity & 0xFF);
	capacity_array[2] = (uint8_t)(capacity>>8);
	I2C_Write(BQ27427_ADDRESS,capacity_array,3);
	while (I2C_isBusy()) {
		I2C_Service();
	}
	
	temp = ((255-OLD_Csum-OLD_DesCap[0]-OLD_DesCap[1])%256);
	uint8_t NEW_Csum = 255- ((temp+0x04+0xb0)%256);
	
	data[0] = 0x60;
	data[1] = NEW_Csum;
	I2C_Write(BQ27427_ADDRESS,data,2);
	while (I2C_isBusy()) {
		I2C_Service();
	}
	
	capacity_array[0] = 0x00;
	capacity_array[1] = 0x42;
	capacity_array[2] = 0x00;
	I2C_Write(BQ27427_ADDRESS,capacity_array,3);
	while (I2C_isBusy()) {
		I2C_Service();
	}
	NOP();
}

