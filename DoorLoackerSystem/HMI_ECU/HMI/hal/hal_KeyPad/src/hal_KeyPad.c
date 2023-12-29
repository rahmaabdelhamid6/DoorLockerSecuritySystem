/*
 * hal_KeyPad.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */


/*
 * hal_KeyPad.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Rahma
 */


#include "common_macros.h" /* To use the macros like SET_BIT */
#include "hal_KeyPad.h"
#include "mcal_Gpio.h"

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#if (KEYPAD_NUM_COLS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 HAL_KEYPAD_4x3_adjustKeyNumber(uint8 ui8button_number);
#elif (KEYPAD_NUM_COLS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 HAL_KEYPAD_4x4_adjustKeyNumber(uint8 ui8button_number);
#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
uint8 HAL_KEYPAD_getPressedKey(void)
{
	uint8 ui8col,ui8row;
	uint8 ui8keypad_port_value = 0;
	while(1)
	{
		for(ui8col=0;ui8col<KEYPAD_NUM_COLS;ui8col++) /* loop for columns */
		{
			/*
			 * Each time setup the direction for all keypad port as input pins,
			 * except this column will be output pin
			 */
			MCAL_GPIO_setupPortDirection(KEYPAD_PORT_ID,PORT_INPUT);
			MCAL_GPIO_setupPinDirection(KEYPAD_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+ui8col,PIN_OUTPUT);

#if(KEYPAD_BUTTON_PRESSED == LOGIC_LOW)
			/* Clear the column output pin and set the rest pins value */
			ui8keypad_port_value = ~(1<<(KEYPAD_FIRST_COLUMN_PIN_ID+ui8col));
#else
			/* Set the column output pin and clear the rest pins value */
			ui8keypad_port_value = (1<<(KEYPAD_FIRST_COLUMN_PIN_ID+ui8col));
#endif
			MCAL_GPIO_writePort(KEYPAD_PORT_ID,ui8keypad_port_value);

			for(ui8row=0;ui8row<KEYPAD_NUM_ROWS;ui8row++) /* loop for rows */
			{
				/* Check if the switch is pressed in this row */
				if(MCAL_GPIO_readPin(KEYPAD_PORT_ID,ui8row+KEYPAD_FIRST_ROW_PIN_ID) == KEYPAD_BUTTON_PRESSED)
				{
					#if (KEYPAD_NUM_COLS == 3)
						return HAL_KEYPAD_4x3_adjustKeyNumber((ui8row*KEYPAD_NUM_COLS)+ui8col+1);
					#elif (KEYPAD_NUM_COLS == 4)
						return HAL_KEYPAD_4x4_adjustKeyNumber((ui8row*KEYPAD_NUM_COLS)+ui8col+1);
					#endif
				}
			}
		}
	}
}

#if (KEYPAD_NUM_COLS == 3)

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static uint8 HAL_KEYPAD_4x3_adjustKeyNumber(uint8 ui8button_number)
{
	uint8 ui8keypad_button = 0;
	switch(ui8button_number)
	{
		case 10: ui8keypad_button = '*'; // ASCII Code of *
				 break;
		case 11: ui8keypad_button = 0;
				 break;
		case 12: ui8keypad_button = '#'; // ASCII Code of #
				 break;
		default: ui8keypad_button = ui8button_number;
				break;
	}
	return ui8keypad_button;
}

#elif (KEYPAD_NUM_COLS == 4)

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8 HAL_KEYPAD_4x4_adjustKeyNumber(uint8 ui8button_number)
{
	uint8 ui8keypad_button = 0;
	switch(ui8button_number)
	{
		case 1: ui8keypad_button = 7;
				break;
		case 2: ui8keypad_button = 8;
				break;
		case 3: ui8keypad_button = 9;
				break;
		case 4: ui8keypad_button = '%'; // ASCII Code of %
				break;
		case 5: ui8keypad_button = 4;
				break;
		case 6: ui8keypad_button = 5;
				break;
		case 7: ui8keypad_button = 6;
				break;
		case 8: ui8keypad_button = '*'; /* ASCII Code of '*' */
				break;
		case 9: ui8keypad_button = 1;
				break;
		case 10: ui8keypad_button = 2;
				break;
		case 11: ui8keypad_button = 3;
				break;
		case 12: ui8keypad_button = '-'; /* ASCII Code of '-' */
				break;
		case 13: ui8keypad_button = 13;  /* ASCII of Enter */
				break;
		case 14: ui8keypad_button = 0;
				break;
		case 15: ui8keypad_button = '='; /* ASCII Code of '=' */
				break;
		case 16: ui8keypad_button = '+'; /* ASCII Code of '+' */
				break;
		default: ui8keypad_button = ui8button_number;
				break;
	}
	return ui8keypad_button;
}

#endif
