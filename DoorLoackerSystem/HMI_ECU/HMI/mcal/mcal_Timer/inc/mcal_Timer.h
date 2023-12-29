/*
 * hal_KeyPad.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#ifndef HMI_HAL_HAL_KEYPAD_INC_HAL_KEYPAD_H_
#define HMI_HAL_HAL_KEYPAD_INC_HAL_KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	OVERFLOW=0x80,PWM_PHASE_CORRECT=0x40,CTC=0x88,FAST_PWM=0x48

}TIMER02_Mode_et;

typedef enum
{
	OVERFLOW1=0x00,CTC1=0x08

}TIMER1_Mode_et;

typedef enum
{
	NO_CLK_SRC,CLK,CLK_8,CLK_64,CLK_256,CLK_1024,EXTERNAL_CLKT0_FALLING_EDGE,EXTERNAL_CLKT0_RISING_EDGE

}TIMER_Prescaler_et;

typedef enum
{
	NORMAL_OPERATION=0x00,TOGGLE=0x10,CLEAR=0x20,SET=0x30

}TIMER_CompareMode_NonPwm_et;

typedef enum
{
	NORMAL=0x00,RESEVED=0x10,CLEAR_NON_INVERTING=0x20,SET_INVERTING=0x30

}TIMER_CompareMode_FastPwm_et;

typedef struct{
	uint16 ui16IntialValue;
	uint16 ui16CompareValue;
	uint16 ui16TimerNumber;
	TIMER02_Mode_et etTimerMode;
	TIMER1_Mode_et etTimerMode1;
	TIMER_Prescaler_et etTimerPrescaler;
	TIMER_CompareMode_NonPwm_et etCompareMode;



}TIMER__ConfigTypeDef_st;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void MCAL_Timer_Init(TIMER__ConfigTypeDef_st *stTimerConfig, void (*pfnTimerCallback) (void));
void MCAL_Timer_Deinit(TIMER__ConfigTypeDef_st *stTimerConfig);
void MCAL_Timer_Stop(TIMER__ConfigTypeDef_st *stTimerConfig);


void MCAL_Timer_CallBack(void(*a_ptr)(void));



#endif /* HMI_HAL_HAL_KEYPAD_INC_HAL_KEYPAD_H_ */
