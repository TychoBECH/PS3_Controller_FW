/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   i2c_driver.h
 * Author: Tycho Kropf
 * Comments: TODO
 * Revision history: TODO
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef I2C_DRIVER_H
#define	I2C_DRIVER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

//<editor-fold desc="I2C definitions">
//Defines for CON0
#define I2C_EN 0x80

#define I2C_Mode_Multi_Host 0b111
#define I2C_Mode_Master_10bit 0b101
#define I2C_Mode_Master_7bit 0b101
//There are other definitions missing here. But for this Project this shall sufice.

//</editor-fold>

//<editor-fold desc="I2C type definitions for I2C transaction object and errors">

typedef enum {
	I2C_STATE_IDLE,
	I2C_STATE_START,
	I2C_STATE_SEND_ADDRESS,
	I2C_STATE_SEND_DATA,
	I2C_STATE_RECEIVE_DATA,
	I2C_STATE_RESTART,
	I2C_STATE_SEND_ACK,
	I2C_STATE_SEND_NACK,
	I2C_STATE_STOP,
	I2C_STATE_COMPLETE,
	I2C_STATE_ERROR
} I2C_State_t;

typedef enum {
	I2C_OK = 0,
	I2C_ERROR_BUSY,
	I2C_ERROR_NACK,
	I2C_ERROR_COLLISION,
	I2C_ERROR_TIMEOUT,
	I2C_ERROR_INVALID_STATE,
	I2C_ERROR_UNKNOWN
} I2C_Result_t;

typedef struct {
	I2C_State_t state;
	uint8_t address;
	uint8_t *txBuffer;
	uint8_t *rxBuffer;
	uint16_t txLength;
	uint16_t rxLength;
	uint16_t txIndex;
	uint16_t rxIndex;
	bool read; // 1 for read operation, 0 for write
	bool busy; // 1 for is busy
	I2C_Result_t result;
} I2C_Transaction_t;

//</editor-fold>

// Comment a function and leverage automatic documentation with slash star star
/**
	<p><b>Function prototype:</b></p>
  
	<p><b>Summary:</b></p>

	<p><b>Description:</b></p>

	<p><b>Precondition:</b></p>

	<p><b>Parameters:</b></p>

	<p><b>Returns:</b></p>

	<p><b>Example:</b></p>
	<code>
 
	</code>

	<p><b>Remarks:</b></p>
 */
void I2C_Init(void);

void I2C_Deinit(void);

I2C_Result_t I2C_Write(uint8_t address, uint8_t *txBuffer, uint8_t txLength);

I2C_Result_t I2C_Read(uint8_t address, uint8_t *rxBuffer, uint8_t rxLength);

I2C_Result_t I2C_WriteRead(uint8_t address, uint8_t *txBuffer, uint8_t txLength, uint8_t *rxBuffer, uint8_t rxLength);

I2C_Result_t I2C_Service(void);

bool I2C_isBusy(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

	// TODO If C++ is being used, regular C code needs function names to have C 
	// linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* I2C_DRIVER_H */

