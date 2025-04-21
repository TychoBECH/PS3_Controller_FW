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
 * File:   io_driver.h
 * Author: Tycho Kropf
 * Comments:
 * Revision history: 0.0.1
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef IO_DRIVER_H
#define IO_DRIVER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

#define IO_RA0 0
#define IO_RA1 1
#define IO_RA2 2
#define IO_RA3 3
#define IO_RA4 4
#define IO_RA5 5
#define IO_RA6 6
#define IO_RA7 7

#define IO_RB0 8
#define IO_RB1 9
#define IO_RB2 10
#define IO_RB3 11
#define IO_RB4 12
#define IO_RB5 13
#define IO_RB6 14
#define IO_RB7 15

#define IO_RC0 16
#define IO_RC1 17
#define IO_RC2 18
#define IO_RC3 19
#define IO_RC4 20
#define IO_RC5 21
#define IO_RC6 22
#define IO_RC7 23

//IO_RD is not available on the selected MCU case

#define IO_RE0 32
#define IO_RE1 33
#define IO_RE2 34
#define IO_RE3 35


/**
    <p><b>Function prototype:</b></p>
    void IO_Init(void);

    <p><b>Summary:</b></p>
    Initializes the IO pins for the microcontroller.

    <p><b>Description:</b></p>
    Configures all necessary pins for the application, setting directions, initial states,
    and any special functionalities like pull-up or pull-down resistors if required.

    <p><b>Precondition:</b></p>
    None.

    <p><b>Parameters:</b></p>
    None.

    <p><b>Returns:</b></p>
    None.

    <p><b>Example:</b></p>
    <code>
    IO_Init();
    </code>

    <p><b>Remarks:</b></p>
    Ensure that any external devices connected to IO pins are in a safe state before calling this function.
 */
void IO_Init(void);

/**
    <p><b>Function prototype:</b></p>
    void IO_Deinit(void);

    <p><b>Summary:</b></p>
    Deinitializes the IO pins, resetting them to their default state.

    <p><b>Description:</b></p>
    Resets all configured pins to their power-on default state, such as setting pins to inputs
    and disabling any special functionalities.

    <p><b>Precondition:</b></p>
    IO_Init must have been called previously.

    <p><b>Parameters:</b></p>
    None.

    <p><b>Returns:</b></p>
    None.

    <p><b>Example:</b></p>
    <code>
    IO_Deinit();
    </code>

    <p><b>Remarks:</b></p>
    Use this function to safely shut down IO configurations before powering down the system or resetting.
 */
void IO_Deinit(void);

/**
    <p><b>Function prototype:</b></p>
    void IO_SetPinDirection(uint8_t pin, bool direction);

    <p><b>Summary:</b></p>
    Sets the direction of a specific IO pin.

    <p><b>Description:</b></p>
    Configures the specified pin as an input or output, depending on the provided direction.

    <p><b>Precondition:</b></p>
    IO_Init must have been called previously.

    <p><b>Parameters:</b></p>
    <ul>
        <li>uint8_t pin - The pin number to configure.</li>
        <li>bool direction - The desired direction (true for output, false for input).</li>
    </ul>

    <p><b>Returns:</b></p>
    None.

    <p><b>Example:</b></p>
    <code>
    IO_SetPinDirection(5, true); // Set pin 5 as output
    </code>

    <p><b>Remarks:</b></p>
    Ensure that the pin number is valid and within the range of available IO pins.
 */
void IO_SetPinDirection(uint8_t pin, bool direction);

/**
    <p><b>Function prototype:</b></p>
    void IO_WritePin(uint8_t pin, bool value);

    <p><b>Summary:</b></p>
    Writes a digital value to a specific IO pin.

    <p><b>Description:</b></p>
    Sets the specified pin to the given digital value (high or low).

    <p><b>Precondition:</b></p>
    The pin must be configured as an output using IO_SetPinDirection.

    <p><b>Parameters:</b></p>
    <ul>
        <li>uint8_t pin - The pin number to set.</li>
        <li>bool value - The digital value to write (true for high, false for low).</li>
    </ul>

    <p><b>Returns:</b></p>
    None.

    <p><b>Example:</b></p>
    <code>
    IO_WritePin(5, true); // Set pin 5 to high
    </code>

    <p><b>Remarks:</b></p>
    Writing to a pin configured as input may have no effect or cause undefined behavior.
 */
void IO_WritePin(uint8_t pin, bool value);

/**
    <p><b>Function prototype:</b></p>
    bool IO_ReadPin(uint8_t pin);

    <p><b>Summary:</b></p>
    Reads the digital value of a specific IO pin.

    <p><b>Description:</b></p>
    Returns the current digital value (high or low) of the specified pin.

    <p><b>Precondition:</b></p>
    The pin must be configured as an input using IO_SetPinDirection.

    <p><b>Parameters:</b></p>
    <ul>
        <li>uint8_t pin - The pin number to read.</li>
    </ul>

    <p><b>Returns:</b></p>
    <ul>
        <li>bool - The digital value of the pin (true for high, false for low).</li>
    </ul>

    <p><b>Example:</b></p>
    <code>
    bool pinState = IO_ReadPin(5); // Read the state of pin 5
    </code>

    <p><b>Remarks:</b></p>
    Ensure that the pin number is valid and within the range of available IO pins.
 */
bool IO_ReadPin(uint8_t pin);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif // IO_DRIVER_H

