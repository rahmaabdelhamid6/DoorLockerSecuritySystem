/*
 * mcal_Gpio.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */


/*
 * mcal_Gpio.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Rahma
 */


#include "mcal_Gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */
/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void MCAL_GPIO_setupPinDirection(uint8 ui8port_num, uint8 ui8pin_num, GPIO_PinDirection_et etdirection)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((ui8pin_num >= NUM_OF_PINS_PER_PORT) || (ui8port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(ui8port_num)
		{
		case PORTA_ID:
			if(etdirection == PIN_OUTPUT)
			{
				SET_BIT(DDRA,ui8pin_num);
			}
			else
			{
				CLEAR_BIT(DDRA,ui8pin_num);
			}
			break;
		case PORTB_ID:
			if(etdirection == PIN_OUTPUT)
			{
				SET_BIT(DDRB,ui8pin_num);
			}
			else
			{
				CLEAR_BIT(DDRB,ui8pin_num);
			}
			break;
		case PORTC_ID:
			if(etdirection == PIN_OUTPUT)
			{
				SET_BIT(DDRC,ui8pin_num);
			}
			else
			{
				CLEAR_BIT(DDRC,ui8pin_num);
			}
			break;
		case PORTD_ID:
			if(etdirection == PIN_OUTPUT)
			{
				SET_BIT(DDRD,ui8pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD,ui8pin_num);
			}
			break;
		}
	}
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void MCAL_GPIO_writePin(uint8 ui8port_num, uint8 ui8pin_num, uint8 ui8value)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((ui8pin_num >= NUM_OF_PINS_PER_PORT) || (ui8port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the pin value as required */
		switch(ui8port_num)
		{
		case PORTA_ID:
			if(ui8value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,ui8pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,ui8pin_num);
			}
			break;
		case PORTB_ID:
			if(ui8value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,ui8pin_num);
			}
			else
			{
				CLEAR_BIT(PORTB,ui8pin_num);
			}
			break;
		case PORTC_ID:
			if(ui8value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,ui8pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,ui8pin_num);
			}
			break;
		case PORTD_ID:
			if(ui8value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,ui8pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,ui8pin_num);
			}
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 MCAL_GPIO_readPin(uint8 ui8port_num, uint8 ui8pin_num)
{
	uint8 ui8pin_value = LOGIC_LOW;

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((ui8pin_num >= NUM_OF_PINS_PER_PORT) || (ui8port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the pin value as required */
		switch(ui8port_num)
		{
		case PORTA_ID:
			if(BIT_IS_SET(PINA,ui8pin_num))
			{
				ui8pin_value = LOGIC_HIGH;
			}
			else
			{
				ui8pin_value = LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PINB,ui8pin_num))
			{
				ui8pin_value = LOGIC_HIGH;
			}
			else
			{
				ui8pin_value = LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(PINC,ui8pin_num))
			{
				ui8pin_value = LOGIC_HIGH;
			}
			else
			{
				ui8pin_value = LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(PIND,ui8pin_num))
			{
				ui8pin_value = LOGIC_HIGH;
			}
			else
			{
				ui8pin_value = LOGIC_LOW;
			}
			break;
		}
	}

	return ui8pin_value;
}

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void MCAL_GPIO_setupPortDirection(uint8 ui8port_num, GPIO_PortDirection_et etdirection)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(ui8port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch(ui8port_num)
		{
		case PORTA_ID:
			DDRA = etdirection;
			break;
		case PORTB_ID:
			DDRB = etdirection;
			break;
		case PORTC_ID:
			DDRC = etdirection;
			break;
		case PORTD_ID:
			DDRD = etdirection;
			break;
		}
	}
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void MCAL_GPIO_writePort(uint8 ui8port_num, uint8 ui8value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(ui8port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the port value as required */
		switch(ui8port_num)
		{
		case PORTA_ID:
			PORTA = ui8value;
			break;
		case PORTB_ID:
			PORTB = ui8value;
			break;
		case PORTC_ID:
			PORTC = ui8value;
			break;
		case PORTD_ID:
			PORTD = ui8value;
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 MCAL_GPIO_readPort(uint8 ui8port_num)
{
	uint8 ui8value = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(ui8port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the port value as required */
		switch(ui8port_num)
		{
		case PORTA_ID:
			ui8value = PINA;
			break;
		case PORTB_ID:
			ui8value = PINB;
			break;
		case PORTC_ID:
			ui8value = PINC;
			break;
		case PORTD_ID:
			ui8value = PIND;
			break;
		}
	}

	return ui8value;
}
