/*
 * sevenSegment.c
 *
 *  Created on: Aug 20, 2019
 *      Author: Abd Elrahman
*/

#include "sevenSegment.h"
#include "GPIO_driver.h"



typedef struct
{
	genum_ports port ;
	genum_type_t type ;
}gstr_data_t;


gstr_data_t garr_dataBuffer[MAX_DEVICES] ;
static ecore_u8 handler = 0 ;
ecore_u8 pattern[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};


bool_t init(genum_ports port , genum_type_t type)
{
	bool_t ret_val = E_TRUE ;
	if((port>=D && port<=A )&&( (type==COMMON_ANODE) ||(type==COMMON_CATHODE) ) )
	{
		if( handler < MAX_DEVICES )
		{
			garr_dataBuffer[handler].port = port ;
			garr_dataBuffer[handler].type = type ;
			portMode(port,OUTPUT);              //make it output
			while ( garr_dataBuffer[++handler].port && handler < MAX_DEVICES );  // to set the new handler and the remaining setting in deinit

		}
		else
		{
			ret_val = E_FALSE ;
		}

	}
	else
	{
		ret_val = E_FALSE ;
	}
	return ret_val ;
}


bool_t display(genum_ports port , ecore_u8 number)
{
	bool_t ret_val = E_TRUE ;
	if( number >= 0 && number < 10 )
	{
		ecore_u8 i ;
		for(i=0 ; i<MAX_DEVICES ; i++)
		{
			if((garr_dataBuffer[i].port == port) && (garr_dataBuffer[i].type == COMMON_CATHODE)  )
			{
				portWrite( port , pattern[number]) ;
				break ;
			}
			else if((garr_dataBuffer[i].port == port) && (garr_dataBuffer[i].type == COMMON_ANODE) )
			{
				portWrite(port , ~pattern[number]) ;
				break ;
			}
			else
			{
				ret_val = E_FALSE ;
			}
		}

	}
	else
	{
		ret_val = E_FALSE ;
	}
	return ret_val ;
}



bool_t deintit(genum_ports port)
{
	bool_t ret_val = E_TRUE ;

	ecore_u8 i ;
	for(i=0 ; i<MAX_DEVICES ; i++)
	{
		if(garr_dataBuffer[i].port==port)
		{
			portWrite(port , 0x00 )  ;  // for the hw output
			garr_dataBuffer[i].port = 0 ;                       // deinit sw buffer
			garr_dataBuffer[i].type = 0 ;                       // deinit sw buffer
			if (handler > i)                                    // to handle the handler
				handler=i  ;

			break ;
		}
		else
		{
			//do nothing
		}
	}
	if( i == MAX_DEVICES)
		ret_val = E_FALSE ;

	return ret_val ;
}



bool_t reset(genum_ports port)
{
	bool_t ret_val = E_TRUE ;

	ecore_u8 i ;
	for(i=0 ; i<MAX_DEVICES ; i++)
	{
		if(garr_dataBuffer[i].port==port && garr_dataBuffer[i].type==COMMON_CATHODE)
		{
			portWrite( port , pattern[0] ) ;
			ret_val = E_TRUE ;
			break ;
		}
		else if(garr_dataBuffer[i].port==port && garr_dataBuffer[i].type==COMMON_ANODE)
		{
			portWrite( port , ~pattern[0] );
			ret_val = E_TRUE ;
			break ;
		}
		else
		{
			//do nothing
		}
	}
	if( i == MAX_DEVICES )          // port didn't initialized
		ret_val = E_FALSE ;
	return ret_val ;

}
