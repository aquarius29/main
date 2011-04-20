#include <stdio.h>


unsigned char motor_message;


void write_motor(unsigned char message){
	motor_message=message;
}    
unsigned char read_motor(void){
	unsigned char temp=motor_message;
	motor_message=0xf1;
	return temp;
}
