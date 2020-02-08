/*
 * sevenSegment.h
 *
 *  Created on: Aug 20, 2019
 *      Author: Abd Elrahman
 */

#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#include "common.h"
#include "GPIO_driver.h"

#define MAX_DEVICES 4




typedef enum
{
	COMMON_ANODE = 1 ,
	COMMON_CATHODE = 2 ,
}genum_type_t;

bool_t init(genum_ports base_port , genum_type_t type);
bool_t display(genum_ports base_port , ecore_u8 number);
bool_t deintit(genum_ports base_port);
bool_t reset(genum_ports base_port);





#endif /* SEVENSEGMENT_H_ */
