#include <stdio.h>


unsigned char filter_message;
unsigned char motor_message;

void write_filter(unsigned char message){
	filter_message=message;
}

unsigned char read_filter(void){
	unsigned char temp=filter_message;
	filter_message=0;
	return temp;
}

void write_motor(unsigned char message){
	motor_message=message;
}    
unsigned char read_motor(void){
	unsigned char temp=motor_message;
	motor_message=0;
	return temp;
}
void test_send_to_filter(unsigned char);
void test_receive_filter();
void test_send_to_motor(unsigned char);
void test_receive_motor();


