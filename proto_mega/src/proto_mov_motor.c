#include <stdio.h>


unsigned char motor_message;


void proto_write_motor(unsigned char message){
	motor_message=message;
#ifdef PC
	printf("move to motor msg value set to: %c\n", motor_message);
#endif
}    
unsigned char proto_read_motor(void){
	unsigned char temp=motor_message;
	motor_message=0xf1;
#ifdef PC
	printf("move to motor msg value set to: %c\n", temp);
#endif
	return temp;
}
