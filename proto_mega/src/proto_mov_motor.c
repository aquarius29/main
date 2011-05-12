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

#ifdef PC
   #include <stdio.h> 
   #include <stdint.h>
#endif

#include <stdlib.h>
#include "proto_lib.h"


uint8_t motor_message;
struct move_commands * movPtr;



struct move_commands * proto_read_motor2(void){ 
  if (movPtr == NULL){
	createDefaultmove();
}	
#ifdef PC
 storeForTint(READ, MOTOR, UNKNOWN, movPtr->message1);
 storeForTint(READ, MOTOR, UNKNOWN, movPtr->message2);
 storeForTint(READ, MOTOR, UNKNOWN, movPtr->message3);
 storeForTint(READ, MOTOR, UNKNOWN, movPtr->message4);
 storeForTint(READ, MOTOR, UNKNOWN, movPtr->message5);
 storeForTint(READ, MOTOR, UNKNOWN, movPtr->message6);
 storeForTint(READ, MOTOR, UNKNOWN, movPtr->message7);
 storeForTint(READ, MOTOR, UNKNOWN, movPtr->message8);
	#ifdef DEBUG
	printf("move_commands value set to: %d , %d\n", movPtr.message1 , movPtr.message2,movPtr.message3,movPtr.message4,movPtr.message5,movPtr.message6,
movPtr.message7,movPtr.message8);
  #endif
#endif
  return (struct move_commands *) movPtr;
}



void proto_write_motor2(uint8_t message1,uint8_t message2,uint8_t message3,uint8_t message4,uint8_t message5,uint8_t message6,uint8_t message7,uint8_t message8){ 
	if (movPtr == NULL)
	movPtr = (struct move_commands *) malloc(sizeof(struct move_commands));
        movPtr->message1 = message1;
        movPtr->message2 = message2;
        movPtr->message3 = message3;
 	movPtr->message4 = message4;
        movPtr->message5 = message5;
        movPtr->message6 = message6;
 	movPtr->message7 = message7;
        movPtr->message8 = message8;	
#ifdef PC
 storeForTint(WRITE, MOVEMENT, UNKNOWN, movPtr->message1);
 storeForTint(WRITE, MOVEMENT, UNKNOWN, movPtr->message2);
 storeForTint(WRITE, MOVEMENT, UNKNOWN, movPtr->message3);
 storeForTint(WRITE, MOVEMENT, UNKNOWN, movPtr->message4);
 storeForTint(WRITE, MOVEMENT, UNKNOWN, movPtr->message5);
 storeForTint(WRITE, MOVEMENT, UNKNOWN, movPtr->message6);
 storeForTint(WRITE, MOVEMENT, UNKNOWN, movPtr->message7);
 storeForTint(WRITE, MOVEMENT, UNKNOWN, movPtr->message8);

	#ifdef DEBUG
	printf("move_commands value set to: %d , %d\n", movPtr.message1 , movPtr.message2,movPtr.message3,movPtr.message4 , movPtr.message5,movPtr.message6, movPtr.message7,movPtr.message8);
  #endif
#endif
} 

void createDefaultmove(){
movPtr = (struct move_commands *) malloc(sizeof(struct move_commands));

	movPtr->message1 = 1;
	movPtr->message2 = 2;
	movPtr->message3 = 3;
	movPtr->message4 = 4;
	movPtr->message5 = 5;
	movPtr->message6 = 6;
	movPtr->message7 = 7;
	movPtr->message8 = 8;

       
}


void proto_write_motor(uint8_t message){
	motor_message=message;
#ifdef PC
 storeForTint(WRITE, MOTOR, UNKNOWN, motor_message);
	#ifdef DEBUG
	printf("move to motor msg value set to: %c\n", motor_message);
  #endif 
#endif
}    
uint8_t proto_read_motor(void){
	uint8_t temp=motor_message;
	motor_message=0xf1;
#ifdef PC
 storeForTint(READ, MOVEMENT, UNKNOWN, temp);
	#ifdef DEBUG
	printf("move to motor msg value set to: %c\n", temp);
  #endif
#endif
	return temp;
}
