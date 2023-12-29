/*
 * app_ECU.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */


#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "std_types.h"
#include "app_ECU.h"
 #include <util/delay.h>
#include "mcal_Gpio.h"
#include "mcal_Uart.h"
#include "mcal_Twi.h"
#include "appcb_Timer.h"
#include "mcal_Timer.h"
#include "isr_Timer.h"
#include "hal_Eeprom.h"
#include "hal_Buzzer.h"
#include "hal_DcMotor.h"




/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

void APP_RecievePW_UART( uint8 PW[] )
{
	for (uint8 i=0 ; i<4 ; i++)
	{
		PW[i] = MCAL_UART_Receive();
	}
	_delay_ms(DELAY_UART);

}
uint8 APP_VerifyPW_UART( uint8 PW[], uint8 RePw[] )
{
	uint8 ui8VerifyPw = 0;
	uint8 ui8Count = 0;

	for (int i = 0 ; i < 4 ; i++)
	{
		if (PW[i] == RePw[i])
		{
			ui8Count++;
		}
	}
	if (ui8Count == 4)
	{
		ui8VerifyPw= 1;
	}
	else
	{
		ui8VerifyPw= 0;
	}

	return ui8VerifyPw;

}
void APP_ECUStart()
{
	uint8 aui8ECUPw[4];
	uint8 aui8ECUconfirm_pw[4];
	uint8 ui8CheckPw;
	uint8 ui8count=0;
	uint8 ui8KeyPadCommand;
	uint8 ui8PwEeprom ;


	TIMER__ConfigTypeDef_st stTimer0Config ={0,7812,0,OVERFLOW,0,CLK_1024,0};
	UART_ConfigTypeDef_st stUartConfig ={9600,BIT_8,ENABLED_EVEN,BIT_1,Async};

	MCAL_Timer_Init(&stTimer0Config, APPCB_TIMER0_OverFlowMode);
	MCAL_UART_init (&stUartConfig);
	HAL_EEPROM_init();
	HAL_Buzzer_init();
	HAL_DcMotor_Init();
	SREG |= (1<<7);

	do{

		//Receive the first password entered by the user
		APP_RecievePW_UART(aui8ECUPw);
		//_delay_ms(DELAY_UART);

		//Receive the confirmation password entered by the user
		APP_RecievePW_UART(aui8ECUconfirm_pw);
		//		_delay_ms(DELAY_UART);

		// verify if the two password are identical
		ui8CheckPw = APP_VerifyPW_UART(aui8ECUPw ,aui8ECUconfirm_pw);

		//send the result to the HMI
		MCAL_UART_Transmit(ui8CheckPw);
		_delay_ms(DELAY_UART);

		//save the password in the eeprom if correct
		if (ui8CheckPw == 1)
		{
			for(uint8 i=0;i<4;i++)
			{
				HAL_EEPROM_writeByte((0X0090+i), aui8ECUPw[i]);
				_delay_ms(DELAY_UART);
			}
		}


	}while(ui8CheckPw==0);

	while(1)
	{
		ui8KeyPadCommand = MCAL_UART_Receive();

		if(ui8KeyPadCommand =='+')
		{
			//read the saved password from eeprom
			for (int i = 0 ; i < 4 ; i ++)
			{
				HAL_EEPROM_readByte((uint16)(0X0090+i), &aui8ECUconfirm_pw[i]);
				_delay_ms(DELAY_UART);
			}
			// the user 3 chance for password

			do{
				ui8count++;
				// RECIEVE PW USER SENDS WE WANT TO CHECK
				APP_RecievePW_UART(aui8ECUPw);

				//CHECK IF PW USER SENT IS CORRECT
				ui8CheckPw = APP_VerifyPW_UART(aui8ECUPw , aui8ECUconfirm_pw);

			} while(ui8CheckPw == 0 && ui8count<3);


			if (ui8CheckPw == 1)
			{
				HAL_DcMotor_Rotate(DC_MOTOR_CW );
				while ( g_SECONDS_T0_MC2 <= 15);
				HAL_DcMotor_Rotate(DC_MOTOR_STOP );
				while ( g_SECONDS_T0_MC2 <= 18);
				HAL_DcMotor_Rotate(DC_MOTOR_ACW );
				while ( g_SECONDS_T0_MC2 <= 33);
				g_SECONDS_T0_MC2=0;  // to make variable start from 0 again
			}
			else if (ui8CheckPw == 0)
			{
				HAL_Buzzer_Start();
				g_SECONDS_T0_MC2 = 0;
				while ( g_SECONDS_T0_MC2 < 60);
				HAL_Buzzer_Stop();
				g_SECONDS_T0_MC2=0;  // to make variable start from 0 again
				//				break;
			}

		}
		else if (ui8KeyPadCommand == '-')
		{

			do{
				APP_RecievePW_UART(aui8ECUPw);        	// RECIEVE FIRST PW USER SENDS
				APP_RecievePW_UART(aui8ECUconfirm_pw);       // RECIEVE VERIFYING PW USER SENDS
				ui8PwEeprom = APP_VerifyPW_UART(aui8ECUPw ,aui8ECUconfirm_pw);		//CHECK IF PW'S SENT FROM THE HMI MATCH
			}while (ui8PwEeprom == 0);
		}

		// SAVE PASS IN EEPROM
		for(uint8 i=0;i<4;i++)
		{
			HAL_EEPROM_writeByte((0X0090+i), aui8ECUPw[i]);
			_delay_ms(DELAY_UART);
		}

	}
}
