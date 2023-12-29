/*
 * mcal_Timer.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#include "mcal_Timer.h"
#include "isr_Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_types.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
/* Initialize Timer with dynamic configuration*/
void MCAL_Timer_Init(TIMER__ConfigTypeDef_st *stTimerConfig, void (*pfnTimerCallback) (void))
{
	// Disable interrupt
	cli();

	switch (stTimerConfig->ui16TimerNumber) {
	case 0:
		// Set Timer 0 mode
		TCCR0 = ((TCCR0 & ~0xC8) | stTimerConfig->etTimerMode);  //ADJUSTS MODE (FOC0,WGM00,WGM01 bits)
		// Set Timer 0 Prescaler
		TCCR0 = (TCCR0 & ~0x07) | ((stTimerConfig->etTimerPrescaler ) & 0x07);

		// Set Timer 0 initial value
		TCNT0 = stTimerConfig->ui16IntialValue;

		// Set Timer 0 compare value and compare mode
		if (stTimerConfig->etTimerMode == CTC) {

			TCCR0 = ((TCCR0 &~ 0x30 ) | stTimerConfig ->etCompareMode);  // set compare mode (normal, toggle, clear,set)

			OCR0 = stTimerConfig->ui16CompareValue;  //set compare value

			TIMSK |= (1 << OCIE0);  // Enable Timer 0 compare match interrupt

			// Set Timer 0 callback
			g_pfnTimer0Callback = pfnTimerCallback;

		}
		else if (stTimerConfig->etTimerMode == OVERFLOW) {
			TIMSK |= (1 << TOIE0);  // Enable Timer 0 overflow interrupt
			// Set Timer 0 callback
			g_pfnTimer0Callback = pfnTimerCallback;
		}

		break;


	case 1:
		// Set Timer 0 mode
		TCCR1A = ((TCCR1A & ~0x0B) | (1<<FOC1A));  //ADJUSTS MODE (FOC0,WGM10,WGM11 bits)
		// Set Timer 0 prescaler
		TCCR1B = (TCCR1B & ~0x07) | ((stTimerConfig->etTimerPrescaler ) & 0x07);

		TCCR1B = (TCCR1B &~ 0X18) |(stTimerConfig->etTimerMode1 );  //ADJUSTS MODE (WGM13,WGM12 bits)

		// Set Timer 0 initial value
		TCNT1 = stTimerConfig->ui16IntialValue;

		// Set Timer 0 compare value and compare mode
		if (stTimerConfig->etTimerMode1 == CTC1) {

			TCCR1A = ((TCCR1A &~ 0xC0 ) | stTimerConfig ->etCompareMode);  // set compare mode (normal, toggle, clear,set)

			OCR1A = stTimerConfig->ui16CompareValue;  //set compare value

			TIMSK |= (1 << OCIE1A);  // Enable Timer 0 compare match interrupt
			// Set Timer 0 callback
			g_pfnTimer1Callback = pfnTimerCallback;

		}
		else if (stTimerConfig->etTimerMode1 == OVERFLOW1) {
			TIMSK |= (1 << TOIE1);  // Enable Timer 0 overflow interrupt
			// Set Timer 0 callback
			g_pfnTimer1Callback = pfnTimerCallback;

		}


		break;
	case 2:
		// Set Timer 0 mode
		TCCR2 = ((TCCR2 & ~0xC8) | stTimerConfig->etTimerMode);  //ADJUSTS MODE (FOC0,WGM00,WGM01 bits)
		// Set Timer 0 prescaler
		TCCR2 = (TCCR2 & ~0x07) | ((stTimerConfig->etTimerPrescaler ) & 0x07);

		// Set Timer 0 initial value
		TCNT2 = stTimerConfig->ui16IntialValue;

		// Set Timer 0 compare value and compare mode
		if (stTimerConfig->etTimerMode == CTC) {

			TCCR2 = ((TCCR2 &~ 0x30 ) | stTimerConfig ->etCompareMode);  // set compare mode (normal, toggle, clear,set)

			OCR2 = stTimerConfig->ui16CompareValue;  //set compare value

			TIMSK |= (1 << OCIE2);  // Enable Timer 0 compare match interrupt
			// Set Timer 0 callback
			g_pfnTimer2Callback = pfnTimerCallback;

		}
		else if (stTimerConfig->etTimerMode == OVERFLOW) {
			TIMSK |= (1 << TOIE2);  // Enable Timer 0 overflow interrupt
			// Set Timer 0 callback
			g_pfnTimer2Callback = pfnTimerCallback;
		}

		//	            // Set Timer 0 callback
		//	            timer0Callback = stTimerConfig->timerCallback;

		break;
		// Enable interrupt
		sei();
	}
}
void MCAL_Timer_Deinit(TIMER__ConfigTypeDef_st *stTimerConfig)
{
	// Disable interrupt
	cli();

	switch (stTimerConfig->ui16TimerNumber) {
	case 0:
		TIMSK &= ~(1 << OCIE0);  // Disable Timer 0 compare match interrupt
		TIMSK &= ~(1 << TOIE0);  // Disable Timer 0 overflow interrupt
		//	            timer0Callback = NULL;
		break;

	case 1:
		TIMSK &= ~(1 << OCIE1A);  // Disable Timer 1 compare match A interrupt
		TIMSK &= ~(1 << TOIE1);  // Disable Timer 1 overflow interrupt
		//	            timer1Callback = NULL;
		break;

	case 2:
		TIMSK &= ~(1 << OCIE2);  // Disable Timer 2 compare match interrupt
		TIMSK &= ~(1 << TOIE2);  // Disable Timer 2 overflow interrupt
		//	            timer2Callback = NULL;
		break;
	}

	// Enable interrupt
	sei();
}


void MCAL_Timer_Stop(TIMER__ConfigTypeDef_st *stTimerConfig)
{
	switch (stTimerConfig->ui16TimerNumber) {
	case 0:
		//	            TCCR0 &= ~0x07;
		TCCR0 = stTimerConfig->etTimerPrescaler;// Set Timer 0 mode to stop = NO_CLK_SRC
		break;

	case 1:
		TCCR1B = stTimerConfig->etTimerPrescaler;  // Set Timer 1 mode to stop = NO_CLK_SRC
		break;

	case 2:
		TCCR2 = stTimerConfig->etTimerPrescaler;  // Set Timer 2 mode to stop = NO_CLK_SRC
		break;
	}
}
