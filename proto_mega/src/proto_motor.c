/*****************************************************************************
* Product: 
* Version: 
* Released: April 1 2011
* Updated: April 28 2011
*
* Copyright (C) 2011 Petre Mihail Anton, Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

#ifdef PC
   #include <stdio.h>
   #include "proto_tint.h"
#endif

char motor_ctrl = 0; // from Filter to Motor Control; DEFAULT is 0

void proto_write_motor_ctrl(char value){
	motor_ctrl = value;
#ifdef PC
	storeForTint(WRITE, UNKNOWN, UNKNOWN, motor_ctrl);
	#ifdef DEBUG
		printf("Motor value set to: %c\n", motor_ctrl);
	#endif
#endif
}
	
char proto_read_motor_ctrl(void){
#ifdef PC
	storeForTint(READ, MOTOR, UNKNOWN, motor_ctrl);
	#ifdef DEBUG
		printf("Motor value is: %c\n", motor_ctrl);
	#endif
#endif
	return motor_ctrl;	
}
