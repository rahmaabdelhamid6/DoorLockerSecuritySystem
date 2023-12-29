/*
 * hal_LCD.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#include <util/delay.h> /* For the delay functions */
#include "common_macros.h"
#include "hal_LCD.h"
#include "mcal_Gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void HAL_LCD_init(void)
{
	/* Configure the direction for RS, RW and E pins as output pins */
	MCAL_GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	MCAL_GPIO_setupPinDirection(LCD_RW_PORT_ID,LCD_RW_PIN_ID,PIN_OUTPUT);
	MCAL_GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);

	/* Configure the data port as output port */
	MCAL_GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);

	HAL_LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */

	HAL_LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */

	HAL_LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}

/*
 * Description :
 * Send the required command to the screen
 */
void HAL_LCD_sendCommand(uint8 ui8command)
{
	MCAL_GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW); /* Instruction Mode RS=0 */
	MCAL_GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	MCAL_GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	MCAL_GPIO_writePort(LCD_DATA_PORT_ID,ui8command); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	MCAL_GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
}

/*
 * Description :
 * Display the required character on the screen
 */
void HAL_LCD_displayCharacter(uint8 ui8data)
{
	MCAL_GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH); /* Data Mode RS=1 */
	MCAL_GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	MCAL_GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	MCAL_GPIO_writePort(LCD_DATA_PORT_ID,ui8data); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	MCAL_GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
}

/*
 * Description :
 * Display the required string on the screen
 */
void HAL_LCD_displayString(const char *pStr)
{
	uint8 i = 0;
	while(pStr[i] != '\0')
	{
		HAL_LCD_displayCharacter(pStr[i]);
		i++;
	}
	/***************** Another Method ***********************
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}
	*********************************************************/
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void HAL_LCD_moveCursor(uint8 ui8row,uint8 ui8col)
{
	uint8 ui8lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(ui8row)
	{
		case 0:
			ui8lcd_memory_address = ui8col;
				break;
		case 1:
			ui8lcd_memory_address = ui8col+0x40;
				break;
		case 2:
			ui8lcd_memory_address = ui8col+0x10;
				break;
		case 3:
			ui8lcd_memory_address = ui8col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	HAL_LCD_sendCommand(ui8lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void HAL_LCD_displayStringRowColumn(uint8 ui8row,uint8 ui8col,const char *pStr)
{
	HAL_LCD_moveCursor(ui8row,ui8col); /* go to to the required LCD position */
	HAL_LCD_displayString(pStr); /* display the string */
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void HAL_LCD_intgerToString(int in32data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(in32data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   HAL_LCD_displayString(buff); /* Display the string */
}

/*
 * Description :
 * Send the clear screen command
 */
void HAL_LCD_clearScreen(void)
{
	HAL_LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}
