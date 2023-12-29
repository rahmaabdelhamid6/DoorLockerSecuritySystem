/*
 * app_ECU.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#ifndef CONTROL_APP_APP_ECU_INC_APP_ECU_H_
#define CONTROL_APP_APP_ECU_INC_APP_ECU_H_

#define DELAY_Keypad 2500
#define DELAY_UART 130
/*******************************************************************************
 *                      Functions Declaration                                   *
 *******************************************************************************/
void APP_RecievePW_UART( uint8 PW[] );
uint8 APP_VerifyPW_UART( uint8 PW[], uint8 RePw[] );
void APP_ECUStart(void);

#endif /* CONTROL_APP_APP_ECU_INC_APP_ECU_H_ */
