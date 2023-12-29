/*
 * hal_Eeprom.c
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#include "mcal_Twi.h"
#include "hal_Eeprom.h"


void HAL_EEPROM_init(void)
{
	TWI_ConfigTypeDef_st stTwiConfig= { PRESCALE_1, 2 , 2 }; 					//TWBR =2 AND ADDRESS = 2
	MCAL_TWI_init( &stTwiConfig );
}
uint8 HAL_EEPROM_writeByte(uint16 ui16addr, uint8 ui8data)
{
	/* Send the Start Bit */
	MCAL_TWI_start();
    if (MCAL_TWI_getStatus() != TWI_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    MCAL_TWI_writeByte((uint8)(0xA0 | ((ui16addr & 0x0700)>>7)));
    if (MCAL_TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    MCAL_TWI_writeByte((uint8)(ui16addr));
    if (MCAL_TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* write byte to eeprom */
    MCAL_TWI_writeByte(ui8data);
    if (MCAL_TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    MCAL_TWI_stop();

    return SUCCESS;
}

uint8 HAL_EEPROM_readByte(uint16 ui16addr, uint8 *ui8data)
{
	/* Send the Start Bit */
	MCAL_TWI_start();
    if (MCAL_TWI_getStatus() != TWI_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    MCAL_TWI_writeByte((uint8)((0xA0) | ((ui16addr & 0x0700)>>7)));
    if (MCAL_TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    MCAL_TWI_writeByte((uint8)(ui16addr));
    if ( MCAL_TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* Send the Repeated Start Bit */
    MCAL_TWI_start();
    if ( MCAL_TWI_getStatus() != TWI_REP_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    MCAL_TWI_writeByte((uint8)((0xA0) | ((ui16addr & 0x0700)>>7) | 1));
    if ( MCAL_TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *ui8data =  MCAL_TWI_readByteWithNACK();
    if ( MCAL_TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    MCAL_TWI_stop();

    return SUCCESS;
}



