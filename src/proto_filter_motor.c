#include <stdio.h>

 #ifdef PC
   #include <stdio.h>
   #include<proto_filter_motor.h>
#endif


unsigned char filter_message;
unsigned char motor_message;

void write_filter(unsigned char message){
	filter_message=message;
#ifdef PC
	printf("filter value set to: %c\n", filter_message);
#endif
}

unsigned char read_filter(void){
	unsigned char temp=filter_message;
	filter_message=0;

#ifdef PC
	printf("filter value set to: %c\n", temp);
#endif

	return temp;
}

void write_motor(unsigned char message){
	motor_message=message;
#ifdef PC
	printf("motor value set to: %c\n", motor_message);
#endif

}    
unsigned char read_motor(void){
	unsigned char temp=motor_message;
	motor_message=0;
#ifdef PC
	printf("motor value set to: %c\n", temp);
#endif
	return temp;
}

void test_send_to_filter(unsigned char);
void test_receive_filter();
void test_send_to_motor(unsigned char);
void test_receive_motor();


