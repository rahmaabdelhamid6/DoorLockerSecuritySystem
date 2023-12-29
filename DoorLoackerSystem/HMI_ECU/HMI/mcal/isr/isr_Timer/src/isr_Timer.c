/*
 * isr_Timer.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */


#include "isr_Timer.h"
#include <avr/interrupt.h>
#include "common_macros.h"
#include "std_types.h"





 void  (*g_pfnTimer0Callback) (void)= NULL;

 void (*g_pfnTimer1Callback) (void)= NULL;

 void (*g_pfnTimer2Callback) (void)= NULL;




ISR(TIMER0_OVF_vect)
{

	if(g_pfnTimer0Callback != NULL)
	{
		g_pfnTimer0Callback();
	}
}

ISR(TIMER0_COMP_vect)
{
    if (g_pfnTimer0Callback != NULL)
    {
    	g_pfnTimer0Callback();
    }
}

ISR(TIMER1_OVF_vect)
{
	if(g_pfnTimer1Callback != NULL)
	{
		g_pfnTimer1Callback();
	}
}

ISR(TIMER1_COMPA_vect)
{
    if (g_pfnTimer1Callback != NULL)
    {
    	g_pfnTimer1Callback();
    }
}


ISR(TIMER2_OVF_vect)
{
	if(g_pfnTimer2Callback != NULL)
	{
		g_pfnTimer2Callback();
	}
}

ISR(TIMER2_COMP_vect)
{
    if (g_pfnTimer2Callback != NULL)
    {
    	g_pfnTimer2Callback();
    }
}
