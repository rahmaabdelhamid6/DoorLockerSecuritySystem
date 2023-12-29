/*
 * isr_Timer.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#ifndef HMI_MCAL_ISR_ISR_TIMER_INC_ISR_TIMER_H_
#define HMI_MCAL_ISR_ISR_TIMER_INC_ISR_TIMER_H_

extern void (*g_pfnTimer0Callback) (void);

extern void (*g_pfnTimer1Callback) (void);

extern void (*g_pfnTimer2Callback) (void);

//extern void (*g_pfnTimer2COMPCallback) (void);

#endif /* HMI_MCAL_ISR_ISR_TIMER_INC_ISR_TIMER_H_ */
