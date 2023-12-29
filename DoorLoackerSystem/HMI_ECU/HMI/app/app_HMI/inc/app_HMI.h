/*
 * app_HMI.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#ifndef HMI_APP_APP_HMI_INC_APP_HMI_H_
#define HMI_APP_APP_HMI_INC_APP_HMI_H_

#define DELAY_Keypad 2500
#define DELAY_UART 130

/*******************************************************************************
 *                      Functions Declaration                                   *
 *******************************************************************************/
void APP_EnterPassWord(uint8 PW[] );
void APP_HMIStart(void);

#endif /* HMI_APP_APP_HMI_INC_APP_HMI_H_ */
