/*
 * appcb_Timer.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#include "mcal_Timer.h"
#include "isr_Timer.h"
#include "avr/io.h" /* To use the UART Registers */
#include "appcb_Timer.h"
/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

volatile uint32 g_SECONDS_T0_MC1 ;
volatile uint32 g_SECONDS_T0_MC2 ;
volatile uint8 g_ui8TimerQuarterSec ;

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

void APPCB_TIMER0_OverFlowMode (void)
{
	g_ui8TimerQuarterSec++;
			if(g_ui8TimerQuarterSec==4)
			{
				g_SECONDS_T0_MC1++;
				g_SECONDS_T0_MC2++;
				g_ui8TimerQuarterSec=0;
			}
}

void APPCB_TIMER0_CompareMode (void)
{

}
void APPCB_TIMER1_OverFlowMode (void)
{

}

void APPCB_TIMER1_CompareMode (void)
{

}

void APPCB_TIMER2_OverFlowMode (void)
{

}

void APPCB_TIMER2_CompareMode (void)
{

}
