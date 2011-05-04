/*****************************************************************************
* Product: 
* Version: 
* Released: April 7 2011
* Updated: April 28 2011
*
* Copyright (C) 2011 by Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/


#include <stdio.h>
#include "proto_tint.h"


unsigned char motor_message;


void proto_write_motor(unsigned char message){
	motor_message=message;
#ifdef PC
 storeForTint(WRITE, MOTOR, UNKNOWN, motor_message);
	#ifdef DEBUG
	printf("move to motor msg value set to: %c\n", motor_message);
  #endif 
#endif
}    
unsigned char proto_read_motor(void){
	unsigned char temp=motor_message;
	motor_message=0xf1;
#ifdef PC
 storeForTint(READ, MOVEMENT, UNKNOWN, temp);
	#ifdef DEBUG
	printf("move to motor msg value set to: %c\n", temp);
  #endif
#endif
	return temp;
}
