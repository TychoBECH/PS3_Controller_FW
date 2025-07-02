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
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BQ27427_H
#define	BQ27427_H



#include <xc.h> // include processor files - each processor file is guarded.  

#include "i2c_driver.h"

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

//<editor-fold desc="BQ27427 definitions">
#define BQ27427_ADDRESS							0x55

#define BQ27427_CMD_Control							0x00 //Commands are always 2 requential addresses. so for COntrol() 0x00 and 0x01
#define BQ27427_CMD_CNTL							0x00 //Some often used have a short name in the datasheet
#define BQ27427_CMD_Temperature						0x02
#define BQ27427_CMD_TEMP							0x02
#define BQ27427_CMD_Voltage							0x04
#define BQ27427_CMD_VOLT							0x04
#define BQ27427_CMD_Flags							0x06
#define BQ27427_CMD_NominalAvailableCapacity		0x08
#define BQ27427_CMD_FullAvailableCapacity			0x0A
#define BQ27427_CMD_RemainingCapacity				0x0C
#define BQ27427_CMD_RM								0x0C
#define BQ27427_CMD_FullChargeCapacity				0x0E
#define BQ27427_CMD_FCC								0x0E
#define BQ27427_CMD_AverageCurrent					0x10
#define BQ27427_CMD_AveragePower					0x18
#define BQ27427_CMD_StateOfCharge					0x1C
#define BQ27427_CMD_SOC								0x1C
#define BQ27427_CMD_InternalTemperature				0x1E
#define BQ27427_CMD_RemainingCapacityUnfiltered		0x28
#define BQ27427_CMD_RemainingCapacityFiltered		0x2A
#define BQ27427_CMD_FullChargeCapacityUnfiltered	0x2C
#define BQ27427_CMD_FullChargeCapacityFiltered		0x2E
#define BQ27427_CMD_StateOfChargeUnfiltered			0x30

#define BQ27427_CTL_CONTROL_STATUS					0x0000 //The controll comand requires another 2 bytes sub comand after
#define BQ27427_CTL_DEVICE_TYPE						0x0001
#define BQ27427_CTL_FW_VERSION						0x0002
#define BQ27427_CTL_DM_CODE							0x0004
#define BQ27427_CTL_PREV_MACWRITE					0x0007
#define BQ27427_CTL_CHEM_ID							0x0008
#define BQ27427_CTL_BAT_INSERT						0x000C
#define BQ27427_CTL_BAT_REMOVE						0x000D
#define BQ27427_CTL_SET_CFGUPDATE					0x0013
#define BQ27427_CTL_SMOOTH_SYNC						0x0019
#define BQ27427_CTL_SHUTDOWN_ENABLE					0x001B
#define BQ27427_CTL_SHUTDOWN						0x001C
#define BQ27427_CTL_SEALED							0x0020
#define BQ27427_CTL_PULSE_SOC_INT					0x0023
#define BQ27427_CTL_CHEM_A							0x0030
#define BQ27427_CTL_CHEM_B							0x0031
#define BQ27427_CTL_CHEM_C							0x0032
#define BQ27427_CTL_RESET							0x0041
#define BQ27427_CTL_SOFT_RESET						0x0042
//</editor-fold>

//<editor-fold desc="BQ27427 status type">
typedef struct {
    uint16_t voltage;
    int16_t current;
    uint16_t soc;
    uint16_t temperature;
    uint16_t full_capacity;
    uint16_t remaining_capacity;
} bq27427_status_t;
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


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

	// TODO If C++ is being used, regular C code needs function names to have C 
	// linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* BQ27427_H */

