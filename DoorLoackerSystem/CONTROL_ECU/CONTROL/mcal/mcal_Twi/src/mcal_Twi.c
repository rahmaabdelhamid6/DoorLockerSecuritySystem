/*
 * mcal_Twi.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#include "mcal_Twi.h"
#include "avr/io.h"/* To use the UART Registers */
#include "common_macros.h"  /* To use the macros like SET_BIT */


/* Initialize TWI with dynamic configuration*/
void MCAL_TWI_init(TWI_ConfigTypeDef_st *stTwiConfig)
{
    /* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
//    TWBR = 0x02;
//	TWSR = 0x00;
	// Set baud rate

	TWBR = stTwiConfig->ui8BitRate;
    TWSR |= ( (TWSR & ~ 0X03) | stTwiConfig->etPrescaler );			 //ADJUSTS PRESCALE

	   // TWBR = ((F_CPU / stTwiConfig->ui32BitRate) - 16) / 2;
    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */

    TWAR = (stTwiConfig->ui8SlaveAddress << 1);   // my address = 0x01 :)

    TWCR = (1<<TWEN); /* enable TWI */
    // Enable I2C interrupts
//       TWCR |= (1 << TWIE);
}


void MCAL_TWI_start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void MCAL_TWI_stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void MCAL_TWI_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 MCAL_TWI_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 MCAL_TWI_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 MCAL_TWI_getStatus(void)
{
    uint8 ui8status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
   ui8status = TWSR & 0xF8;
    return ui8status;
}

