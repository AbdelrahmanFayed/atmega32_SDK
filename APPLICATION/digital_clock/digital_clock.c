/*
 * digital_clock.c
 *
 * Created: 2/8/2020 8:10:23 PM
 *  Author: Abd Elrahman
 */ 


#include <avr/io.h>
#include "common.h"
#include "GPIO_driver.h"
#include "sevenSegment.h"
#include "timerManagementUnit.h"


void clock_func();

int main(void)
{
	init( A , COMMON_CATHODE );
	init( B , COMMON_CATHODE );
	init( C , COMMON_CATHODE );
	init( D , COMMON_CATHODE );
	
	reset(A);
	reset(B);
	reset(C);
	reset(D);
	
	init_timer0( MILLI_SEC );
	
	gstr_info_t my_timer ;
	start_timer( & my_timer , 1000 , & clock_func , PERIODIC );
	
    while(1)
    {
        dispatch();
    }
}

void clock_func(void)
{
	 static ecore_u8 seconds = 0 , minutes = 0 ;
	 
	 
	 if( seconds==59 && minutes == 59)
	 {
		 seconds = 0 ;  minutes=0 ;
		 reset(A);
		 reset(B);
		 reset(C);
		 reset(D);
	 }
	 else if( seconds == 59)
	 {
		 seconds=0 ;
		 minutes ++ ;
		 reset(C);
		 reset(D);
		 display( A , minutes % 10);
		 display( B , minutes / 10);
	 }
	 else
	 {
		 seconds ++ ;
		 display(D , seconds%10);
		 display(C , seconds/10);
	 }	
}
