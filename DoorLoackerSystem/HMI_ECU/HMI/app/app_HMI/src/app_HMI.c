/*
 * app_HMI.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "std_types.h"
#include <util/delay.h>
#include "app_HMI.h"
#include "appcb_Timer.h"
#include "mcal_Timer.h"
#include "mcal_Uart.h"
#include "hal_KeyPad.h"
#include "hal_LCD.h"
#include "mcal_Gpio.h"


/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
void APP_EnterPassWord(uint8 PW[] )
{
	HAL_LCD_moveCursor(1, 5);
	for (uint8 i = 0; i < 5; i++) {
		while ((HAL_KEYPAD_getPressedKey() != 13) && (i == 4));  // POLLING UNTIL ON BUTTON PRESSED

		PW[i] = HAL_KEYPAD_getPressedKey();
		_delay_ms(DELAY_Keypad);				//DELAY SO KEYPAD DOESN'T REPEAT
		HAL_LCD_displayCharacter('*');
	}
	_delay_ms(DELAY_Keypad);
}

void APP_SendPW_UART( uint8 PW[] )
{
	for (uint8 i=0 ; i<4 ; i++)
	{
		MCAL_UART_Transmit( PW[i] );
		_delay_ms(DELAY_UART);
	}

}

void APP_HMIStart()
{
	uint8 aui8Pw[4];
	uint8 aui8confirm_pw[4];
	uint8 ui8CheckPw;
	uint8 ui8PressedKey;
	uint8 ui8count;
	TIMER__ConfigTypeDef_st stTimer0Config ={0,7812,0,OVERFLOW,0,CLK_1024,0};
	UART_ConfigTypeDef_st stUartConfig ={9600,BIT_8,ENABLED_EVEN,BIT_1,Async};
	HAL_LCD_init();
	HAL_LCD_clearScreen();
	MCAL_Timer_Init(&stTimer0Config, APPCB_TIMER0_OverFlowMode);
	MCAL_UART_init (&stUartConfig);
	SREG |= (1<<7);
	/*******************************************************************************
	 *                       For First Time                          *
	 *******************************************************************************/
	do{
		HAL_LCD_clearScreen();
		HAL_LCD_displayString(" Please Enter the Password ");
		APP_EnterPassWord(aui8Pw);
		_delay_ms(DELAY_UART);
		APP_SendPW_UART (aui8Pw);

		HAL_LCD_clearScreen();
		HAL_LCD_displayString("RE-Enter PW");
		APP_EnterPassWord(aui8confirm_pw);
		_delay_ms(DELAY_UART);
		APP_SendPW_UART(aui8confirm_pw);


		ui8CheckPw = MCAL_UART_Receive();
		if(ui8CheckPw == 0)
		{
			HAL_LCD_clearScreen();
			HAL_LCD_displayStringRowColumn(0,4,"INVALID");
			_delay_ms(DELAY_Keypad);
		}



	}while (ui8CheckPw== 0);
	HAL_LCD_clearScreen();
	HAL_LCD_displayString("Correct");
	_delay_ms(DELAY_Keypad);

	/*******************************************************************************
	 *                      Change password (-)  or open the door (+)                      *
	 *******************************************************************************/
	while(1)
	{
		HAL_LCD_clearScreen();
		HAL_LCD_displayStringRowColumn(0, 0, "- :Change PW");
		HAL_LCD_displayStringRowColumn(1, 0, "+ :open");

		ui8PressedKey = HAL_KEYPAD_getPressedKey();
		_delay_ms(DELAY_Keypad);
		MCAL_UART_Transmit(ui8PressedKey);
		_delay_ms(DELAY_UART);

		if (ui8PressedKey == '+')
		{
			do{
				ui8count ++;

				HAL_LCD_clearScreen();
				HAL_LCD_displayString(" Please Enter the Password ");
				APP_EnterPassWord(aui8Pw);
				_delay_ms(DELAY_UART);
				APP_SendPW_UART (aui8Pw);


				ui8CheckPw = MCAL_UART_Receive();
				_delay_ms(DELAY_UART);
				if(ui8CheckPw == 0)
				{
					HAL_LCD_clearScreen();
					HAL_LCD_displayStringRowColumn(0,4,"INVALID");
					_delay_ms(DELAY_Keypad);
				}
			}while(ui8CheckPw==0 && ui8count <3);
			/* DOOR OPENS IN 15 SECONDS AND STAYS OPENED FOR 3 SECONDS AND STARTS*/
			/*  CLOSING AGAIN IN 15 SECONDS */

			if(ui8CheckPw)
			{
				HAL_LCD_clearScreen();
				HAL_LCD_displayStringRowColumn(0,4,"Door is Opening");
				HAL_LCD_displayString("Opening Door");
				while ( g_SECONDS_T0_MC1 <= 15);
				HAL_LCD_clearScreen();
				HAL_LCD_displayString("Door Open");
				while ( g_SECONDS_T0_MC1 <= 18);
				HAL_LCD_clearScreen();
				HAL_LCD_displayString("Closing Door");
				while ( g_SECONDS_T0_MC1 <= 33);
				g_SECONDS_T0_MC1=0; // to make variable start from 0 again

			}
			else if(ui8CheckPw==0)
			{
				HAL_LCD_clearScreen();
				HAL_LCD_displayStringRowColumn(0,5,"ALARM");
				g_SECONDS_T0_MC1 = 0;
				while ( g_SECONDS_T0_MC1 < 60);       // LOCK MC1 FOR 60 SECONDS
				g_SECONDS_T0_MC1 = 0;
			}
		}

		else if (ui8PressedKey == '-')
		{
			do{
				ui8count ++;

				HAL_LCD_clearScreen();
				HAL_LCD_displayString(" Please Enter the Password ");
				APP_EnterPassWord(aui8Pw);
				_delay_ms(DELAY_UART);
				APP_SendPW_UART (aui8Pw);

				HAL_LCD_clearScreen();
				HAL_LCD_displayString("RE-Enter PW");
				APP_EnterPassWord(aui8confirm_pw);
				_delay_ms(DELAY_UART);
				APP_SendPW_UART(aui8confirm_pw);

				ui8CheckPw = MCAL_UART_Receive();
				_delay_ms(DELAY_UART);
				if(ui8CheckPw == 0)
				{
					HAL_LCD_clearScreen();
					HAL_LCD_displayStringRowColumn(0,4,"INVALID");
					_delay_ms(DELAY_Keypad);
				}

			}while(ui8CheckPw == 0);
			if (ui8CheckPw == 1)
			{
				HAL_LCD_clearScreen();
				HAL_LCD_displayString("Password Changed");
				_delay_ms(DELAY_Keypad);
			}
		}
	}
}
