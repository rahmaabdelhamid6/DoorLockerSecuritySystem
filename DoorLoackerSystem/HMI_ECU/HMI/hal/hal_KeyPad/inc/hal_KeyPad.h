/*
 * hal_KeyPad.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */
//
//#ifndef HMI_HAL_HAL_KEYPAD_INC_HAL_KEYPAD_H_
//
//#define HMI_HAL_HAL_KEYPAD_INC_HAL_KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                  4
#define KEYPAD_NUM_ROWS                  4

/* Keypad Port Configurations */
#define KEYPAD_PORT_ID                   PORTA_ID

#define KEYPAD_FIRST_ROW_PIN_ID           PIN0_ID
#define KEYPAD_FIRST_COLUMN_PIN_ID        PIN4_ID

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 HAL_KEYPAD_getPressedKey(void);


//#endif /* HMI_HAL_HAL_KEYPAD_INC_HAL_KEYPAD_H_ */
