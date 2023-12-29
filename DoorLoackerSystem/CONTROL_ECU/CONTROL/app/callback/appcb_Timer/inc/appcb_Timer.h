/*
 * appcb_Timer.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#ifndef CONTROL_APP_CALLBACK_APPCB_TIMER_INC_APPCB_TIMER_H_
#define CONTROL_APP_CALLBACK_APPCB_TIMER_INC_APPCB_TIMER_H_

extern volatile uint32 g_SECONDS_T0_MC1 ;
extern volatile uint32 g_SECONDS_T0_MC2 ;
extern volatile uint8 g_ui8TimerQuarterSec ;

/*******************************************************************************
 *                      Functions Declaration                                   *
 *******************************************************************************/
void APPCB_TIMER0_OverFlowMode (void);
void APPCB_TIMER0_CompareMode (void);
void APPCB_TIMER1_OverFlowMode (void);
void APPCB_TIMER1_CompareMode (void);
void APPCB_TIMER2_OverFlowMode (void);
void APPCB_TIMER2_CompareMode (void);

#endif /* CONTROL_APP_CALLBACK_APPCB_TIMER_INC_APPCB_TIMER_H_ */
