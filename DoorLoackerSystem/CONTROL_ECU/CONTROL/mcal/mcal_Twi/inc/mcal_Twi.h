/*
 * mcal_Twi.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#ifndef CONTROL_MCAL_MCAL_TWI_INC_MCAL_TWI_H_
#define CONTROL_MCAL_MCAL_TWI_INC_MCAL_TWI_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	PRESCALE_1,PRESACLE_4,PRESCALE_16,PRESCALE_64
}TWI_Prescaler_et;

typedef struct
{
	TWI_Prescaler_et etPrescaler;
	uint8 ui8BitRate;            //This member configures the TWI communication baud rate
	uint8 ui8SlaveAddress;         //Specifies the address of the slave

}TWI_ConfigTypeDef_st;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void MCAL_TWI_init(TWI_ConfigTypeDef_st *stTwiConfig);
void MCAL_TWI_start(void);
void MCAL_TWI_stop(void);
void MCAL_TWI_writeByte(uint8 data);
uint8 MCAL_TWI_readByteWithACK(void);
uint8 MCAL_TWI_readByteWithNACK(void);
uint8 MCAL_TWI_getStatus(void);

#endif /* CONTROL_MCAL_MCAL_TWI_INC_MCAL_TWI_H_ */
