/*
 * mcal_Uart.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#include "mcal_Uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "std_types.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
/* Initialize UART with dynamic configuration*/
void MCAL_UART_init (UART_ConfigTypeDef_st *stUartConfig) {
	uint16 ubrr_value = (uint16)F_CPU / (16 * stUartConfig->ui32BaudRate) - 1;

	// Set baud rate
	UBRRH = (ubrr_value >> 8);
	UBRRL = ubrr_value;

	// Enable receiver and transmitter
	UCSRB = (1 << RXEN) | (1 << TXEN);

	// Enable receiver and transmitter interrupts
	UCSRB |= (1 << RXCIE) | (1 << TXCIE);

	// Set frame format: data bits, parity, and stop bits
	MCAL_UART_configure(stUartConfig->etWordLength, stUartConfig->etParity, stUartConfig->etStopBits, stUartConfig->etUartMode);
}

// Configure UART settings
void MCAL_UART_configure(uint8 data_bits, uint8 parity, uint8 stop_bits, uint8 mode)
{
	UCSRC = (1<<URSEL);
	// Set data bits
	if (data_bits == 6) {
		UCSRC = (1 << UCSZ0);
	} else if (data_bits == 7) {
		UCSRC = (1 << UCSZ1);
	} else if (data_bits == 8) {
		UCSRC = (1 << UCSZ0) | (1 << UCSZ1);
	}
	else if (data_bits == 8)
	{
		UCSRC = (1 << UCSZ0) | (1 << UCSZ1) | (1<<UCSZ2);
	}

	// Set parity
	if (parity == 1) {
		UCSRC |= (1 << UPM1) | (1 << UPM0);
	} else if (parity == 2) {
		UCSRC |= (1 << UPM1);
	}

	// Set stop bits
	if (stop_bits == 2) {
		UCSRC |= (1 << USBS);
	}
	else
	{
		UCSRC &= ~(1 << USBS); // Use 1 stop bit
	}

	//set Uart mode
	if (mode) //1 IF SYNCH
	{
		UCSRC |= ((mode) << 6);  // SYNCHRONOUS OPERATION

		UCSRC |= (1<<UCPOL); // DATA TRANSMITTED ON FALLING EDGE , AND SAMPLED ON POSITIVE EDGE
	}
	else
	{
		UCSRC |= ((mode) << 6);  // ASYNCHRONOUS OPERATION
	}
}

// Transmit a single character
void MCAL_UART_Transmit(uint8_t data) {
	// Wait for empty transmit buffer
	while (!(UCSRA & (1 << UDRE)));

	// Put data into buffer, sends the data
	UDR = data;
}

// Receive a single character
uint8_t MCAL_UART_Receive() {
	// Wait for data to be received
	while (!(UCSRA & (1 << RXC)));

	// Get and return received data from buffer
	return UDR;
}
/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void MCAL_UART_SendString(const uint8 *pStr)
{
	uint8 i = 0;

	/* Send the whole string */
	while(pStr[i] != '\0')
	{
		MCAL_UART_Transmit(pStr[i]);
		i++;
	}
	/************************* Another Method *************************
		while(*pStr != '\0')
		{
			UART_sendByte(*pStr);
			pStr++;
		}
	 *******************************************************************/
}


void MCAL_UART_ReceiveString(uint8 *pStr)
{
	uint8 i = 0;

	/* Receive the first byte */
	pStr[i] = MCAL_UART_Receive();

	/* Receive the whole string until the '#' */
	while(pStr[i] != '#')
	{
		i++;
		pStr[i] = MCAL_UART_Receive();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	pStr[i] = '\0';
}
