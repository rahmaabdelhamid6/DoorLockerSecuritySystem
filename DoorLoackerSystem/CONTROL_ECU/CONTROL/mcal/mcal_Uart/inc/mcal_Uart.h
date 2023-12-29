/*
 * mcal_Uart.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#ifndef CONTROL_MCAL_MCAL_UART_INC_MCAL_UART_H_
#define CONTROL_MCAL_MCAL_UART_INC_MCAL_UART_H_
#include "std_types.h"


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum {
	Async, Sync
}UART_ModeTypeDef_et;

typedef enum
{
	DISABLED,RESERVED,ENABLED_EVEN,ENABLED_ODD
}UART_ParityModeTypeDef_et;

typedef enum {
	BIT_5,BIT_6,BIT_7,BIT_8,RESERVED1,RESERVED2,RESERVED3,BIT_9

}UART_DataSizeTypeDef_et;
typedef enum
{
	BIT_1,BIT_2
}UART_StopBitTypeDef_et;

typedef struct
{
	uint32 ui32BaudRate;            //This member configures the UART communication baud rate
	UART_DataSizeTypeDef_et etWordLength;         //Specifies the number of data bits transmitted or received in a frame
	UART_ParityModeTypeDef_et etParity;            // Specifies the parity mode
	UART_StopBitTypeDef_et etStopBits;
	UART_ModeTypeDef_et etUartMode;//Specifies the number of stop bits transmitted

}UART_ConfigTypeDef_st;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void MCAL_UART_init (UART_ConfigTypeDef_st *stUartConfig);

/*
 * Description :
 * Functional responsible for Configure the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits .
 */
void MCAL_UART_configure(uint8 data_bits, uint8 parity, uint8 stop_bits, uint8 mode);
/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void MCAL_UART_Transmit(uint8 ui8data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 MCAL_UART_Receive() ;

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void MCAL_UART_SendString(const uint8 *pStr);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void MCAL_UART_ReceiveString(uint8 *pStr); // Receive until #



#endif /* CONTROL_MCAL_MCAL_UART_INC_MCAL_UART_H_ */
