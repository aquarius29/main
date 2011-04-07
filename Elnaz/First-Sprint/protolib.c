/*****************************************************************************
* Product: 
* Version: 
* Released: April 1 2011
* Updated: April 1 2011
*
* Copyright (C) 2011 Peter Mihail Anton ,Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/


char motor_ctrl = 0; // from Filter to Motor Control; DEFAULT is 0

void write_motor_ctrl(char value){
	motor_ctrl = value;	
}
	
char read_motor_ctrl(void){
	return motor_ctrl;	
}
