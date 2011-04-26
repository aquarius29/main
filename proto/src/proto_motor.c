/*****************************************************************************
* Product: 
* Version: 
* Released: April 1 2011
* Updated: April 1 2011
*
* Copyright (C) 2011 Peter Mihail Anton, Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

#ifdef PC
   #include <stdio.h>
#endif

char motor_ctrl = 0; // from Filter to Motor Control; DEFAULT is 0

void proto_write_motor_ctrl(char value){
	motor_ctrl = value;
#ifdef PC
	printf("Motor value set to: %c\n", motor_ctrl);
#endif
}
	
char proto_read_motor_ctrl(void){
#ifdef PC
	printf("Motor value is: %c\n", motor_ctrl);
#endif
	return motor_ctrl;	
}
