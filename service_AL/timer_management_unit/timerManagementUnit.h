
/*
                                                       THIS MODULE USES TIMER0 
*/

#ifndef timerManagementUnit.h
#define timerManagementUnit.h

#include <avr/io.h>
#include "common.h"

#define MAX_TIMERS 10

typedef enum
{
	MICRO_SEC ,
	MILLI_SEC ,
		
} genum_resolution_t;

typedef enum
{
	PERIODIC ,
	ONE_SHOT ,
	
} genum_typeCalling_t;

typedef struct                  // just create it where you want and give me  the address (user has the buffer)
{
	ecore_u16 time ;
	ecore_s16 remaining_time ;
	void(*ptr_cb)(void);
	genum_typeCalling_t type_calling ;
	
} gstr_info_t ;         



bool_t init_timer0(genum_resolution_t resolution );
bool_t deinit_timer0();

bool_t start_timer(gstr_info_t * info , ecore_u16 time , void(*ptr)(void) , genum_typeCalling_t type_calling );
bool_t stop_timer(gstr_info_t * info);

bool_t dispatch();




#endif