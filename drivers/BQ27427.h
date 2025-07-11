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

#define _XTAL_FREQ 64000000

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

/**
	<p><b>Function prototype:</b></p>
	<code>void bq27427_send_subcomand(uint16_t subcmd);</code>

	<p><b>Summary:</b></p>
	<p>Sends a 2-byte subcommand to the BQ27427 Control() command interface.</p>

	<p><b>Description:</b></p>
	<p>
	This function writes a subcommand to the Control() register (0x00) of the BQ27427 fuel gauge, allowing control over various internal operations such as unsealing, resetting, or switching modes.
	</p>

	<p><b>Precondition:</b></p>
	<p>I2C must be initialized and the BQ27427 must be powered.</p>

	<p><b>Parameters:</b></p>
	<ul>
		<li><b>subcmd</b> - 16-bit subcommand to be sent (e.g., 0x0013 for SET_CFGUPDATE).</li>
	</ul>

	<p><b>Returns:</b></p>
	<p>None.</p>
 */
void bq27427_send_subcomand(uint16_t subcmd);

/**
	<p><b>Function prototype:</b></p>
	<code>void bq27427_send_subcomand_with_data(uint16_t subcmd, uint8_t *data, uint8_t length);</code>

	<p><b>Summary:</b></p>
	<p>Sends a subcommand followed by additional data to the BQ27427 fuel gauge.</p>

	<p><b>Description:</b></p>
	<p>
	Used for commands that require additional payload data beyond the 2-byte subcommand. This function writes the subcommand first, followed by the user-supplied data buffer.
	</p>

	<p><b>Precondition:</b></p>
	<p>I2C must be initialized and the device must be in a mode that allows writes.</p>

	<p><b>Parameters:</b></p>
	<ul>
		<li><b>subcmd</b> - The subcommand opcode to send.</li>
		<li><b>data</b> - Pointer to a buffer of bytes to follow the subcommand.</li>
		<li><b>length</b> - Number of bytes in the data buffer.</li>
	</ul>

	<p><b>Returns:</b></p>
	<p>None.</p>
 */
void bq27427_send_subcomand_with_data(uint16_t subcmd, uint8_t *data, uint8_t length);

/**
	<p><b>Function prototype:</b></p>
	<code>void bq27427_write_word(uint8_t reg, uint16_t data);</code>

	<p><b>Summary:</b></p>
	<p>Writes a 16-bit word to a standard command register on the BQ27427.</p>

	<p><b>Description:</b></p>
	<p>
	This function performs a 2-byte write to a specific register address. It is used for writing standard command values or updating memory.
	</p>

	<p><b>Precondition:</b></p>
	<p>I2C must be initialized and communication with the BQ27427 must be functioning.</p>

	<p><b>Parameters:</b></p>
	<ul>
		<li><b>reg</b> - The register address to write to.</li>
		<li><b>data</b> - The 16-bit value to write.</li>
	</ul>

	<p><b>Returns:</b></p>
	<p>None.</p>
 */
void bq27427_write_word(uint8_t reg, uint16_t data);

/**
	<p><b>Function prototype:</b></p>
	<code>void bq27427_send_command(uint8_t command);</code>

	<p><b>Summary:</b></p>
	<p>Sends a one-byte command to the BQ27427.</p>

	<p><b>Description:</b></p>
	<p>
	This function is used to initiate a single-byte command on the BQ27427, typically used in extended data commands or control procedures.
	</p>

	<p><b>Precondition:</b></p>
	<p>The I2C interface must be initialized.</p>

	<p><b>Parameters:</b></p>
	<ul>
		<li><b>command</b> - The 8-bit command value to send.</li>
	</ul>

	<p><b>Returns:</b></p>
	<p>None.</p>
 */
void bq27427_send_command(uint8_t command);

/**
	<p><b>Function prototype:</b></p>
	<code>uint16_t bq27427_read_word(uint8_t reg);</code>

	<p><b>Summary:</b></p>
	<p>Reads a 16-bit word from a register on the BQ27427.</p>

	<p><b>Description:</b></p>
	<p>
	This function reads two bytes from the specified standard command register and returns the result as a 16-bit value.
	</p>

	<p><b>Precondition:</b></p>
	<p>The I2C interface must be active and functioning correctly.</p>

	<p><b>Parameters:</b></p>
	<ul>
		<li><b>reg</b> - The register address to read from.</li>
	</ul>

	<p><b>Returns:</b></p>
	<p>16-bit value read from the device.</p>
 */
uint16_t bq27427_read_word(uint8_t reg);

/**
	<p><b>Function prototype:</b></p>
	<code>uint16_t bq27427_get_voltage(void);</code>

	<p><b>Summary:</b></p>
	<p>Reads the battery voltage from the BQ27427.</p>

	<p><b>Description:</b></p>
	<p>
	This function reads the voltage value from the BQ27427 using the <code>Voltage()</code> command (0x04) and returns the value in millivolts.
	</p>

	<p><b>Precondition:</b></p>
	<p>The fuel gauge must be powered and initialized.</p>

	<p><b>Parameters:</b></p>
	<p>None.</p>

	<p><b>Returns:</b></p>
	<p>Battery voltage in millivolts.</p>
 */
uint16_t bq27427_get_voltage(void);	//in mV

/**
	<p><b>Function prototype:</b></p>
	<code>int16_t bq27427_get_current(void);</code>

	<p><b>Summary:</b></p>
	<p>Reads the average current from the BQ27427 fuel gauge.</p>

	<p><b>Description:</b></p>
	<p>
	This function reads the average battery current (signed) using the <code>AverageCurrent()</code> command (0x10) and returns it in milliamps.
	</p>

	<p><b>Precondition:</b></p>
	<p>The BQ27427 must be active and able to respond to I2C queries.</p>

	<p><b>Parameters:</b></p>
	<p>None.</p>

	<p><b>Returns:</b></p>
	<p>Current in milliamps (positive for charging, negative for discharging).</p>
 */
int16_t bq27427_get_current(void);	//in mA

/**
	<p><b>Function prototype:</b></p>
	<code>uint16_t bq27427_get_temperature(void);</code>

	<p><b>Summary:</b></p>
	<p>Retrieves the battery temperature from the BQ27427.</p>

	<p><b>Description:</b></p>
	<p>
	Reads the internal or external temperature measurement and returns it in tenths of degrees Celsius (0.1°C resolution).
	</p>

	<p><b>Precondition:</b></p>
	<p>Temperature source must be configured in the OpConfig.</p>

	<p><b>Parameters:</b></p>
	<p>None.</p>

	<p><b>Returns:</b></p>
	<p>Temperature in 0.1°C units (e.g., 250 = 25.0°C).</p>
 */
uint16_t bq27427_get_temperature(void); //in 0.1°C

/**
	<p><b>Function prototype:</b></p>
	<code>uint8_t bq27427_get_state_of_charge(void);</code>

	<p><b>Summary:</b></p>
	<p>Returns the remaining state of charge (SOC) of the battery.</p>

	<p><b>Description:</b></p>
	<p>
	This function queries the <code>StateOfCharge()</code> command (0x1C) and returns the battery SOC in percent.
	</p>

	<p><b>Precondition:</b></p>
	<p>Device must be in NORMAL or SLEEP mode and actively gauging.</p>

	<p><b>Parameters:</b></p>
	<p>None.</p>

	<p><b>Returns:</b></p>
	<p>State of charge in percent (0?100).</p>
 */
uint8_t bq27427_get_state_of_charge(void); //in %

/**
	<p><b>Function prototype:</b></p>
	<code>void bq27427_unseal(void);</code>

	<p><b>Summary:</b></p>
	<p>Sends the unseal key to the BQ27427 to allow configuration changes.</p>

	<p><b>Description:</b></p>
	<p>
	If the BQ27427 is sealed, this function sends the appropriate unseal key (typically 0x8000 twice) to allow access to protected commands and configuration memory.
	</p>

	<p><b>Precondition:</b></p>
	<p>Gauge must be sealed. I2C communication must be working.</p>

	<p><b>Parameters:</b></p>
	<p>None.</p>

	<p><b>Returns:</b></p>
	<p>None.</p>
 */
void bq27427_unseal(void);

/**
	<p><b>Function prototype:</b></p>
	<code>void bq27427_enter_config_update(void);</code>

	<p><b>Summary:</b></p>
	<p>Puts the fuel gauge into CONFIG UPDATE mode.</p>

	<p><b>Description:</b></p>
	<p>
	This function sends the <code>SET_CFGUPDATE</code> subcommand to place the device in CONFIG UPDATE mode, which allows changes to data flash parameters.
	</p>

	<p><b>Precondition:</b></p>
	<p>The device must be unsealed.</p>

	<p><b>Parameters:</b></p>
	<p>None.</p>

	<p><b>Returns:</b></p>
	<p>None.</p>
 */
void bq27427_enter_config_update(void);

/**
	<p><b>Function prototype:</b></p>
	<code>void bq27427_set_design_capatity(uint16_t capacity);</code>

	<p><b>Summary:</b></p>
	<p>Updates the design capacity parameter in the fuel gauge.</p>

	<p><b>Description:</b></p>
	<p>
	Changes the Design Capacity in the State subclass of Data Memory to match the battery's actual capacity. This involves entering CONFIG UPDATE mode, modifying the data block, and writing a new checksum.
	</p>

	<p><b>Precondition:</b></p>
	<p>The device must be unsealed and in CONFIG UPDATE mode.</p>

	<p><b>Parameters:</b></p>
	<ul>
		<li><b>capacity</b> - Design capacity in mAh (e.g., 1200 for 1200mAh).</li>
	</ul>

	<p><b>Returns:</b></p>
	<p>None.</p>
 */
void bq27427_set_design_capatity(uint16_t capacity);


/**
	<p><b>Function prototype:</b></p>
	<code>void bq27427_update_status(bq27427_status_t *status);</code>
  
	<p><b>Summary:</b></p>
	<p>Reads key battery status values from the BQ27427 fuel gauge and stores them in a status structure.</p>

	<p><b>Description:</b></p>
	<p>
	This function communicates with the BQ27427 battery fuel gauge over I2C and retrieves several standard command values,
	including voltage, state of charge (SOC), temperature, and current. These values are stored in a user-provided 
	<b>bq27427_status_t</b> structure. This function is typically called periodically in the main loop to keep battery 
	monitoring data up to date.
	</p>

	<p><b>Precondition:</b></p>
	<p>
	The I2C interface must be initialized with <code>I2C_Init()</code>, and the <b>status</b> pointer must point to a valid
	<b>bq27427_status_t</b> structure. The fuel gauge must be properly powered and initialized.
	</p>

	<p><b>Parameters:</b></p>
	<ul>
		<li><b>status</b> - Pointer to a <code>bq27427_status_t</code> structure that will be filled with the latest battery readings.</li>
	</ul>

	<p><b>Returns:</b></p>
	<p>
	None. This function updates the fields of the provided <code>bq27427_status_t</code> struct directly.
	</p>

	<p><b>Example:</b></p>
	<code>
	bq27427_status_t batteryStatus;
	bq27427_update_status(&batteryStatus);

	printf("Voltage: %umV\n", batteryStatus.voltage);
	printf("SOC: %u%%\n", batteryStatus.soc);
	</code>

	<p><b>Remarks:</b></p>
	<p>
	This function may block briefly while waiting for I2C transactions to complete. If more advanced non-blocking behavior is needed,
	consider integrating the I2C_Service() calls into a task loop or scheduler.
	</p>
 */
void bq27427_update_status(void);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

	// TODO If C++ is being used, regular C code needs function names to have C 
	// linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* BQ27427_H */

