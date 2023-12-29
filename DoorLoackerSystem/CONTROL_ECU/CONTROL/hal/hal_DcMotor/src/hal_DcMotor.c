/*
 * hal_DcMotor.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */


#include "hal_DcMotor.h"
#include "mcal_Gpio.h"
//#include "pwm_timer0.h"

/*
 * Description :
 * Initialize the DC Motor by:
 * 1. Setup the direction of the two motor pins as output by send the request to GPIO driver.
 * 2. Stop the motor at the beginning
 */
void HAL_DcMotor_Init(void)
{
	/* Setup the two motor pins as output pins */
	MCAL_GPIO_setupPinDirection(DC_MOTOR_PORT1_ID,DC_MOTOR_PIN1_ID,PIN_OUTPUT);
	MCAL_GPIO_setupPinDirection(DC_MOTOR_PORT2_ID,DC_MOTOR_PIN2_ID,PIN_OUTPUT);

	/* Motor is stopped at the beginning */
	MCAL_GPIO_writePin(DC_MOTOR_PORT1_ID,DC_MOTOR_PIN1_ID,LOGIC_LOW);
	MCAL_GPIO_writePin(DC_MOTOR_PORT2_ID,DC_MOTOR_PIN2_ID,LOGIC_LOW);
}

/*
 * Description :
 * 1. Rotate  or Stop the motor according to the state input variable.
 * 2. Control the motor speed 0 --> 100% from its maximum speed by sending to PWM driver.
 */
void HAL_DcMotor_Rotate(DcMotor_State_et etstate)
{
	if(etstate == DC_MOTOR_CW)
	{
		/* Rotates the Motor CW */
		MCAL_GPIO_writePin(DC_MOTOR_PORT1_ID,DC_MOTOR_PIN1_ID,LOGIC_LOW);
		MCAL_GPIO_writePin(DC_MOTOR_PORT2_ID,DC_MOTOR_PIN2_ID,LOGIC_HIGH);

//		PWM_Timer0_Start(speed);
	}
	else if(etstate == DC_MOTOR_ACW)
	{
		/* Rotates the Motor A-CW */
		MCAL_GPIO_writePin(DC_MOTOR_PORT1_ID,DC_MOTOR_PIN1_ID,LOGIC_HIGH);
		MCAL_GPIO_writePin(DC_MOTOR_PORT2_ID,DC_MOTOR_PIN2_ID,LOGIC_LOW);

//		PWM_Timer0_Start(speed);
	}
	else if(etstate == DC_MOTOR_STOP)
	{
		/* Stop the Motor */
		MCAL_GPIO_writePin(DC_MOTOR_PORT1_ID,DC_MOTOR_PIN1_ID,LOGIC_LOW);
		MCAL_GPIO_writePin(DC_MOTOR_PORT2_ID,DC_MOTOR_PIN2_ID,LOGIC_LOW);

//		PWM_Timer0_Start(speed);
	}
	else
	{
		/* Invalid Input State - Do Nothing */
	}
}
