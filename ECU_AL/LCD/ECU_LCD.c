/*
 * ECU_LCD.c
 *
 *  Created on: Sep 29, 2019
 *      Author: Abd Elrahman
 */


#include "ECU_LCD.h"
#include "GPIO_driver.h"
#include <util/delay.h>

bool_t LCD_init(genum_LCD_Config_t * cfg)
{
	bool_t ret_val = E_TRUE ;
	if( cfg != NULL )
	{
		_delay_ms(2000);
		//make the control pins output
		pinMode( cfg->control_pins_port , RS , OUTPUT );
		pinMode( cfg->control_pins_port , W_R , OUTPUT );
		pinMode( cfg->control_pins_port , Enable , OUTPUT );

		//make the data port output depends on the the mode
		if( cfg->mode == MODE_8)
		{
			portMode(cfg->data_port , OUTPUT);
			LCD_cmd( cfg , MODE_8_CMD );  
			_delay_us(150);
		}
		else if ( cfg->mode == MODE_4 )
		{
			pinMode( cfg->data_port , 0 , OUTPUT );
			pinMode( cfg->data_port , 1 , OUTPUT );
			pinMode( cfg->data_port , 2 , OUTPUT );
			pinMode( cfg->data_port , 3 , OUTPUT );

			LCD_cmd( cfg , MODE_4_CMD);
			_delay_us(150);
		}
		else
		{
			ret_val = E_FALSE;
		}
		// initialization commands
		LCD_cmd( cfg , CLR_DISP);            
		_delay_ms(15);
		LCD_cmd( cfg , DISP_ON_CURSOR_ON);
		_delay_ms(15);
		
	}
	else
	{
		ret_val = E_FALSE ;
	}
	return ret_val;
}

bool_t LCD_display(genum_LCD_Config_t * cfg , ecore_u8  character )
{
	bool_t ret_val = E_TRUE ;
	if( cfg != NULL )
	{
		digitalWrite( cfg->control_pins_port , RS , HIGH );
		digitalWrite( cfg->control_pins_port , W_R , LOW );
		if( cfg->mode == MODE_8 )
		{
			portWrite( cfg->data_port , character );
			digitalWrite(cfg->control_pins_port,Enable,HIGH);    //generate pulse on enable pin  -3 lines follow-
			_delay_us (10);
			digitalWrite(cfg->control_pins_port,Enable,LOW);
			_delay_us(150);
		}
		else if( cfg->mode == MODE_4 )
		{

		}
		else
		{
			//do nothing
		}
	}
	else
	{
		ret_val = E_FALSE ;
	}
	return ret_val;
}

bool_t LCD_cmd( genum_LCD_Config_t * cfg , genum_Commands_t command )
{
	bool_t ret_val = E_TRUE ;
	if( cfg != NULL && command > 0x0 && command <= 0x38 )
	{
		digitalWrite( cfg->control_pins_port , RS , LOW );
		digitalWrite( cfg->control_pins_port , W_R , LOW );
		if( cfg->mode == MODE_8 )
		{
			portWrite( cfg->data_port , command );
			digitalWrite(cfg->control_pins_port,Enable,HIGH);    //generate pulse on enable pin  -3 lines follow-
			_delay_us (10);
			digitalWrite(cfg->control_pins_port,Enable,LOW);
		}
		else if( cfg->mode == MODE_4 )
		{

		}
		else
		{
			//do nothing
		}

	}
	else
	{
		ret_val = E_FALSE ;
	}
	return ret_val;
}
