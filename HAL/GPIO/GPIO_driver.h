/*
 * GPIO_driver.h
 *
 * Created: 2/4/2020 2:00:28 PM
 *  Author: Abd Elrahman
 */ 


#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_



#include"common.h"


#define BASE_A 0x39
#define BASE_B 0x36
#define BASE_C 0x33
#define BASE_D 0x30
#define DIR_OFFSET 1
#define PORT_OFFSET 2


typedef enum
{
	INPUT  ,
	OUTPUT ,
}genum_Direction;


typedef enum
{
	LOW  ,
	HIGH ,
}genum_pinState ;


typedef enum
{

	A = BASE_A ,
	B = BASE_B ,
	C = BASE_C ,
	D = BASE_D ,

}genum_ports ;


bool_t pinMode(genum_ports port ,ecore_u8 pinNum ,genum_Direction direction);
bool_t digitalWrite( genum_ports port , ecore_u8 pinNum , genum_pinState state);
/*
 * IN[state]
 * */

bool_t digitalRead( genum_ports port , ecore_u8 pinNum , ecore_u8 * state);
/*
 * OUT[state]
 * */

bool_t internal_PullUp( genum_ports port , ecore_u8 pinNum);

bool_t portMode(genum_ports port  ,genum_Direction direction);

bool_t portWrite( genum_ports port  , ecore_u8 write_value);

bool_t portRead( genum_ports port  , ecore_u8 * red_value);
/*
 * OUT[red_value]
 * */








#endif /* GPIO_DRIVER_H_ */