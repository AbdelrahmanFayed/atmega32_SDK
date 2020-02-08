




#include <avr/io.h>
#include <avr/interrupt.h>
#include "timerManagementUnit.h"

// Asume oscillator is 8 MHz

//volatile ecore_u32 current_time = 0 ;

static gstr_info_t * objects_reference [MAX_TIMERS] ;    // internal buffer 
static ecore_u8 handler = 0 ;                            // handler of buffer

ISR(TIMER0_COMP_vect)
{
	ecore_u8 i ;
	for(i=0 ; i < MAX_TIMERS ; i++ )   //
	{
		if(objects_reference[i]  )
		{
			(*(objects_reference[i])).remaining_time -- ;
		}
	}
}



bool_t init_timer0(genum_resolution_t resolution )
{
	bool_t ret_val = E_TRUE ;
	
	if( (resolution == MICRO_SEC) )
	{
		TCNT0 = 0x00 ;  // initial value for the timer
		TCCR0 = 0x09 ;  // open ctc mode and connect clock without Prescaling   
		OCR0 = 0x07 ;   // the number which timer reach 1 micro sec
		sei ();         // enable global interrupts		
		TIMSK &= (1 << OCIE0 );  
		
			
	}
	else if ( (resolution == MILLI_SEC) )
	{
		TCNT0 = 0x00 ;  // initial value for the timer
		TCCR0 = 0x0B ;  // open ctc mode and connect Prescaling / 64
		OCR0 = 0x7C ;   // the number which timer reach 1 milli sec
		sei ();         // enable global interrupts
		TIMSK = 2 ;
	}
	else
	{
		ret_val = E_FALSE ;
	}
	
	return ret_val ;
}

bool_t deinit_timer0()
{
	
	bool_t ret_val = E_TRUE ;
	
	TCCR0 = 0x00 ;       // disconnect timer  
	
	return ret_val ;
	
}

bool_t start_timer(gstr_info_t * info , ecore_u16 time , void(*ptr)(void) , genum_typeCalling_t type_calling )
{
	
	bool_t ret_val = E_TRUE ;
	
	if( (info != NULL) && (time > 0) && (ptr != NULL) && (type_calling == PERIODIC || type_calling == ONE_SHOT) && (handler < MAX_TIMERS) )
	{
		// intit the empty object with parameters
		info ->time = time  ; 
		info ->remaining_time = time ;
		info ->ptr_cb = ptr ;
		info ->type_calling = type_calling ;
		
		// handle the internal buffer and handeller
		objects_reference[handler] = info ;
		for(  ; handler < MAX_TIMERS ; handler++)
		{
			if(objects_reference[handler] == 0 )
				break;
		}
	}
	else
	{
		ret_val = E_FALSE ;
	}
	
	return ret_val ;
	
}


bool_t stop_timer(gstr_info_t * info)
{
	
	bool_t ret_val = E_TRUE ;
	if( info != NULL)
	{
		ecore_u8 i ;
		for(i=0 ; i < MAX_TIMERS ; i++ )   // loop for find the address and clear it && not the best solution
		{
			if(objects_reference[i] == info )
			{
				objects_reference[i] = 0 ;
				if(i < handler)
					handler = i ;
				break;
			}	 
		}
		
	}
	else
	{
		ret_val = E_FALSE ;
	}
	
	return ret_val ;
	
}

bool_t dispatch()
{
	
	bool_t ret_val = E_TRUE ;
	ecore_u8 i ;
	for(i=0 ; i < MAX_TIMERS ; i++ )   // 
	{
		if(objects_reference[i]  )
		{
			if( (*(objects_reference[i])).remaining_time <= 0 )
			{
				if((*(objects_reference[i])).type_calling == ONE_SHOT)
				{
					stop_timer(objects_reference[i]) ;
				}
				else
				{
					(*(objects_reference[i])).remaining_time = (*(objects_reference[i])).time ;
				}
					
				((*(objects_reference[i])).ptr_cb)() ;          // call cb func.
			}
		}
	}
	
	return ret_val ;
	
}