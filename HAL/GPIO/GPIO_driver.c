/*
 * GPIO_driver.c
 *
 * Created: 2/4/2020 2:02:04 PM
 *  Author: Abd Elrahman
 */ 



#include "GPIO_driver.h"



bool_t pinMode( genum_ports port , ecore_u8 pinNum , genum_Direction direction)
{
	bool_t ret_val= E_TRUE ;
	if( (pinNum >= 0) && (pinNum < 8) && (port >= D && port <= A ) )
	{
		if( direction == OUTPUT )
		{
			(*(volatile ecore_u8 *)(port+DIR_OFFSET)) |= ( 1 << pinNum ) ;
		}
		else if( direction == INPUT )
		{
			(*(volatile ecore_u8 *)(port+DIR_OFFSET)) &= ~( 1 << pinNum ) ;
		}
		else
		{
			ret_val= E_FALSE ;	
		}
	}
	else
	{
		ret_val= E_FALSE ;
	}
	return ret_val ;
}



bool_t digitalWrite(genum_ports port , ecore_u8 pinNum , genum_pinState state)
{
	bool_t ret_val= E_TRUE ;
	if( (pinNum >= 0) && (pinNum < 8) && (port >= D && port <= A ) )            // check parameters
	{
		if( (((*(volatile ecore_u8 *)(port+DIR_OFFSET)) >> pinNum) &  1) == 1    )     // check if the mode is output
		{
			if( state == HIGH )
			{
				(*(volatile ecore_u8 *)(port+PORT_OFFSET)) |= ( 1 << pinNum ) ;
			}
			else if( state == LOW )
			{
				(*(volatile ecore_u8 *)(port+PORT_OFFSET)) &= ~( 1 << pinNum ) ;
			}
			else
			{
				ret_val= E_FALSE ;
			}	
		}
		else
		{
			ret_val= E_FALSE ;
		}
	}
	else
	{
		ret_val= E_FALSE ;
	}
	return ret_val ;
}



bool_t digitalRead(genum_ports port , ecore_u8 pinNum , ecore_u8 * state)
{
	bool_t ret_val= E_TRUE ;
	if( (pinNum >= 0) && (pinNum < 8) && (port >= D && port <= A ) && (state != NULL) )   //check for parameters.
	{
		if( (((*(volatile ecore_u8 *)(port+DIR_OFFSET)) >> pinNum) &  1) == 0 )           //check if mode is input .
		{
			* state = ((*(volatile ecore_u8 *)(port)) >> pinNum) & 1 ;                    // put the red value at state varriable .
		}
		else
		{
			ret_val= E_FALSE ;
		}
	}
	else
	{
		ret_val= E_FALSE ;
	}
	return ret_val ;
}



bool_t internal_PullUp( genum_ports port , ecore_u8 pinNum)
{
	bool_t ret_val= E_TRUE ;
	if( (pinNum > 0) && (pinNum < 8)  )
	{
		if( (((*(volatile ecore_u8 *)(port+DIR_OFFSET)) >> pinNum) &  1) == 0 ) //check if mode is input 
		{
			*(volatile ecore_u8 *)(port+PORT_OFFSET) |= ( 1 << pinNum ) ;
		}
		else
		{
			ret_val= E_FALSE ;
		}
	}
	else
	{
		ret_val= E_FALSE ;
	}
	return ret_val ;
}





bool_t portMode(genum_ports port  ,genum_Direction direction)
{
	bool_t ret_val = E_TRUE;
	if( (port >= D && port <= A ) )
	{
		if( direction == OUTPUT )
		{
			(*(volatile ecore_u8 *)(port+DIR_OFFSET)) = 0xff ;
		}
		else if( direction == INPUT )
		{
			(*(volatile ecore_u8 *)(port+DIR_OFFSET)) = 0x00 ;
		}
		else
		{
			ret_val= E_FALSE ;
		}
	}
	else
	{
		ret_val = E_FALSE ;
	}
	return ret_val ;
}


bool_t portWrite( genum_ports port  , ecore_u8 write_value)
{
	
	bool_t ret_val = E_TRUE;
	if( (port >= D && port <= A ) )
	{
		(*(volatile ecore_u8 *)(port+PORT_OFFSET)) = write_value ;
	}
	else
	{
		ret_val = E_FALSE ;
	}
	return ret_val ;
	
}


bool_t portRead( genum_ports port  , ecore_u8 * red_value)
{
	
	bool_t ret_val = E_TRUE;
	if( (port >= D && port <= A ) && (red_value!=NULL) )
	{
		* red_value = (*(volatile ecore_u8 *)(port)) & (0xff) ;
	}
	else
	{
		ret_val = E_FALSE ;
	}
	return ret_val ;
	
}




