/*
 * hal_Buzzer.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#include "hal_Buzzer.h"
#include "mcal_gpio.h"


void HAL_Buzzer_init(void)
{
	MCAL_GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_OUTPUT);
	MCAL_GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);									//PD6 AND PD7 OUTPUT PINS FOR THE BUZZER
	MCAL_GPIO_writePin(PORTD_ID, PIN6_ID, LOGIC_LOW);
	MCAL_GPIO_writePin(PORTD_ID, PIN7_ID, LOGIC_LOW);											// BY DEFAULT OUTPUT PINS ARE 0
}


void HAL_Buzzer_Start(void)
{
	MCAL_GPIO_writePin(PORTD_ID, PIN6_ID, LOGIC_HIGH);
	MCAL_GPIO_writePin(PORTD_ID, PIN7_ID, LOGIC_LOW);
}


void HAL_Buzzer_Stop(void)
{
	MCAL_GPIO_writePin(PORTD_ID, PIN6_ID, LOGIC_LOW);
}
