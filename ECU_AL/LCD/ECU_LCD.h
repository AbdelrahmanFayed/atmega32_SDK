/*
 * ECU_LCD.h
 *
 *  Created on: Sep 29, 2019
 *      Author: Abd Elrahman
 */

/*
 *                                             IMPORTANT NOTES
 *
 * 1- delay times are left to the user of that module except the most important ones .
 * 2- there is some constrains you should be careful about while using this module .
 * 3- there is no enough safety mechanisms to handle users faults , So follow the instructions carefully .
 */


#ifndef ECU_LCD_H_
#define ECU_LCD_H_

#include "common.h"
#include "GPIO_driver.h"


#define RS     0
#define W_R    1
#define Enable 2


typedef enum
{
	CLR_DISP             = 0x01  ,    
	RETURN_HOME          = 0x02  ,
	SL_CURSOR            = 0x04  ,
	SR_CURSOR            = 0x06  ,
	SR_DISP              = 0x05  ,
	SL_DISP              = 0x07  ,
	DISP_OFF_CURSOR_OFF  = 0x08  ,
	DISP_OFF_CURSOR_ON   = 0x0A  ,
	DISP_ON_CURSOR_OFF   = 0x0C  ,
	DISP_ON_CURSOR_ON    = 0x0E  ,
	MODE_4_CMD           = 0x28 ,
	MODE_8_CMD           = 0x38 ,
}genum_Commands_t;

typedef enum
{
	MODE_8 ,
	MODE_4 ,
}genum_Mode_t;


typedef struct
{
	genum_Mode_t mode;
	genum_ports control_pins_port;   // use what is defined above at the macros for RS , W/A , Enable respectively.
	genum_ports data_port;           // use the first 4 pins in case of Mode_4

}genum_LCD_Config_t;



bool_t LCD_init(genum_LCD_Config_t * cfg);
/*
 * should wait about 15ms before calling this function .
 */

bool_t LCD_display(genum_LCD_Config_t * cfg , ecore_u8  character );
/*
 *
 */

bool_t LCD_cmd( genum_LCD_Config_t * cfg , genum_Commands_t command );
/*
 * after each command you should wait about 100 µs.
 * After the "CLR_DISP" and "RETURN_HOME" commands you should wait for about 2 ms.
 */


#endif /* ECU_LCD_H_ */
