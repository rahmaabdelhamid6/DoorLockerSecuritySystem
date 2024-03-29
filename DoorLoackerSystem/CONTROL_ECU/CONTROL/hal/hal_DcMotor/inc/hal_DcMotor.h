/*
 * hal_DcMotor.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#ifndef CONTROL_HAL_HAL_DCMOTOR_INC_HAL_DCMOTOR_H_
#define CONTROL_HAL_HAL_DCMOTOR_INC_HAL_DCMOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* The Ports and Pins IDs for the DC-Motor two pins */
#define DC_MOTOR_PORT1_ID   PORTC_ID
#define DC_MOTOR_PORT2_ID   PORTC_ID

#define DC_MOTOR_PIN1_ID    PIN5_ID
#define DC_MOTOR_PIN2_ID    PIN6_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	DC_MOTOR_STOP,DC_MOTOR_CW,DC_MOTOR_ACW
}DcMotor_State_et;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize the DC Motor by:
 * 1. Setup the direction of the two motor pins as output by send the request to GPIO driver.
 * 2. Stop the motor at the beginning
 */
void HAL_DcMotor_Init(void);

/*
 * Description :
 * 1. Rotate  or Stop the motor according to the state input variable.
 * 2. Control the motor speed 0 --> 100% from its maximum speed by sending to PWM driver.
 */
void HAL_DcMotor_Rotate(DcMotor_State_et etstate);


#endif /* CONTROL_HAL_HAL_DCMOTOR_INC_HAL_DCMOTOR_H_ */
