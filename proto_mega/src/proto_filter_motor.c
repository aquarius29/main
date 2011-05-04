/*****************************************************************************
* Product: 
* Version: 
* Released: April 1 2011
* Updated: April 28 2011
*
* Copyright by (C) 2011 by Elnaz Shahmehr
*
*  
*
* <IT University of Goteborg>
*****************************************************************************/


#ifdef PC
   #include <stdio.h>
   #include"proto_filter_motor.h"
   #include "proto_tint.h"
#endif


unsigned char filter_message;
unsigned char motor_message;

void proto_write_filter(unsigned char message){
	filter_message=message;
#ifdef PC
  storeForTint(WRITE, FILTER, UNKNOWN, filter_message);
	#ifdef DEBUG
	printf("filter value set to: %c\n", filter_message);
    #endif
#endif
}

unsigned char proto_read_filter(void){
	unsigned char temp=filter_message;
	filter_message=0;

#ifdef PC
 storeForTint(READ, FILTER, UNKNOWN, temp);
	#ifdef DEBUG
	printf("filter value set to: %c\n", temp);
   #endif
#endif

	return temp;
}

void proto_write_motor(unsigned char message){
	motor_message=message;
#ifdef PC
      storeForTint(WRITE, MOTOR, UNKNOWN, motor_message);
	#ifdef DEBUG
	printf("motor value set to: %c\n", motor_message);
  #endif
#endif

}    
unsigned char proto_read_motor(void){
	unsigned char temp=motor_message;
	motor_message=0;
#ifdef PC
 storeForTint(READ, MOTOR, UNKNOWN, temp);
	#ifdef DEBUG
	printf("motor value set to: %c\n", temp);
      #endif
#endif
	return temp;
}

void test_send_to_filter(unsigned char);
void test_receive_filter();
void test_send_to_motor(unsigned char);
void test_receive_motor();


