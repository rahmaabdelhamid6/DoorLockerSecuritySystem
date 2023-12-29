/*
 * hal_LCD.h
 *
 *  Created on: Dec 29, 2023
 *      Author: Rahma
 */

#ifndef HMI_HAL_HAL_LCD_INC_HAL_LCD_H_
#define HMI_HAL_HAL_LCD_INC_HAL_LCD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTD_ID
#define LCD_RS_PIN_ID                  PIN4_ID

#define LCD_RW_PORT_ID                 PORTD_ID
#define LCD_RW_PIN_ID                  PIN5_ID

#define LCD_E_PORT_ID                  PORTD_ID
#define LCD_E_PIN_ID                   PIN6_ID

#define LCD_DATA_PORT_ID               PORTC_ID

/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void HAL_LCD_init(void);

/*
 * Description :
 * Send the required command to the screen
 */
void HAL_LCD_sendCommand(uint8 ui8command);

/*
 * Description :
 * Display the required character on the screen
 */
void HAL_LCD_displayCharacter(uint8 ui8data);

/*
 * Description :
 * Display the required string on the screen
 */
void HAL_LCD_displayString(const char *pStr);

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void HAL_LCD_moveCursor(uint8 ui8row,uint8 ui8col);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void HAL_LCD_displayStringRowColumn(uint8 ui8row,uint8 ui8col,const char *pStr);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void HAL_LCD_intgerToString(int in32data);

/*
 * Description :
 * Send the clear screen command
 */
void HAL_LCD_clearScreen(void);



#endif /* HMI_HAL_HAL_LCD_INC_HAL_LCD_H_ */
