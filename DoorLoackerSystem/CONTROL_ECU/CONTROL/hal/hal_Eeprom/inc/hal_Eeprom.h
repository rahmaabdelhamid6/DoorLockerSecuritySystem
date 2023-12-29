/*
 * hal_Eeprom.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#ifndef CONTROL_HAL_HAL_EEPROM_INC_HAL_EEPROM_H_
#define CONTROL_HAL_HAL_EEPROM_INC_HAL_EEPROM_H_
#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void HAL_EEPROM_init(void);

uint8 HAL_EEPROM_writeByte(uint16 ui16addr,uint8 ui8data);
uint8 HAL_EEPROM_readByte(uint16 ui16addr,uint8 *ui8data);


#endif /* CONTROL_HAL_HAL_EEPROM_INC_HAL_EEPROM_H_ */
