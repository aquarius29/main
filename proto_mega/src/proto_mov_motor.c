/*!
* @file proto_mov_motor.c
* @brief Movement messages
* @author Elnaz Shahmehr
* @history 
*           - 2011-04-07
* 			- 2011-04-28 updated by Elnaz
* 			- 2011-05-12 updated by Mihail
*			- 2011-05-13 updated by Elnaz
*
*/

#ifdef PC
    #include <stdio.h> 
    #include <stdint.h>
    
#endif

#include <stdlib.h>
#include "proto_lib.h"


uint8_t motor_message;
struct move_commands * movPtr;

struct move_commands * proto_read_motor2(void){ 
#ifdef PC
    storeForTint(PROTO_READ, PROTO_MOTOR, PROTO_UNKNOWN, movPtr->message1);
    storeForTint(PROTO_READ, PROTO_MOTOR, PROTO_UNKNOWN, movPtr->message2);
    storeForTint(PROTO_READ, PROTO_MOTOR, PROTO_UNKNOWN, movPtr->message3);
    storeForTint(PROTO_READ, PROTO_MOTOR, PROTO_UNKNOWN, movPtr->message4);
    storeForTint(PROTO_READ, PROTO_MOTOR, PROTO_UNKNOWN, movPtr->message5);
    storeForTint(PROTO_READ, PROTO_MOTOR, PROTO_UNKNOWN, movPtr->message6);
    storeForTint(PROTO_READ, PROTO_MOTOR, PROTO_UNKNOWN, movPtr->message7);
    storeForTint(PROTO_READ, PROTO_MOTOR, PROTO_UNKNOWN, movPtr->message8);
	#ifdef DEBUG
	printf("move_commands value set to: %d , %d\n", movPtr->message1,
	    movPtr->message2, movPtr->message3, movPtr->message4, movPtr->message5,
	    movPtr->message6, movPtr->message7, movPtr->message8);
    #endif
#endif
    return (struct move_commands *) movPtr;
}



void proto_write_motor2(uint8_t message1, uint8_t message2, uint8_t message3,
        uint8_t message4, uint8_t message5, uint8_t message6,
        uint8_t message7, uint8_t message8){ 
    movPtr->message1 = message1;
    movPtr->message2 = message2;
    movPtr->message3 = message3;
 	movPtr->message4 = message4;
    movPtr->message5 = message5;
    movPtr->message6 = message6;
 	movPtr->message7 = message7;
    movPtr->message8 = message8;	
#ifdef PC
    storeForTint(PROTO_WRITE, PROTO_MOVEMENT, PROTO_UNKNOWN, movPtr->message1);
    storeForTint(PROTO_WRITE, PROTO_MOVEMENT, PROTO_UNKNOWN, movPtr->message2);
    storeForTint(PROTO_WRITE, PROTO_MOVEMENT, PROTO_UNKNOWN, movPtr->message3);
    storeForTint(PROTO_WRITE, PROTO_MOVEMENT, PROTO_UNKNOWN, movPtr->message4);
    storeForTint(PROTO_WRITE, PROTO_MOVEMENT, PROTO_UNKNOWN, movPtr->message5);
    storeForTint(PROTO_WRITE, PROTO_MOVEMENT, PROTO_UNKNOWN, movPtr->message6);
    storeForTint(PROTO_WRITE, PROTO_MOVEMENT, PROTO_UNKNOWN, movPtr->message7);
    storeForTint(PROTO_WRITE, PROTO_MOVEMENT, PROTO_UNKNOWN, movPtr->message8);
	#ifdef DEBUG
    printf("move_commands value set to: %d, %d, %d, %d, %d, %d, %d, %d\n", movPtr->message1,
            movPtr->message2, movPtr->message3, movPtr->message4,
            movPtr->message5, movPtr->message6, movPtr->message7,
            movPtr->message8);
    #endif
#endif
} 

void createDefaultmove(){
    if(movPtr == NULL){
        movPtr = (struct move_commands *) malloc(sizeof(struct move_commands));
    }
    movPtr->message1 = 0xF1;
	movPtr->message2 = 0xF1;
	movPtr->message3 = 0xF1;
	movPtr->message4 = 0xF1;
	movPtr->message5 = 0xF1;
	movPtr->message6 = 0xF1;
	movPtr->message7 = 0xF1;
	movPtr->message8 = 0xF1;
}


void proto_write_motor(uint8_t message){
	motor_message=message;
#ifdef PC
    storeForTint(PROTO_WRITE, PROTO_MOTOR, PROTO_UNKNOWN, motor_message);
	#ifdef DEBUG
	   printf("move to motor msg value set to: %c\n", motor_message);
    #endif 
#endif
} 
   
uint8_t proto_read_motor(void){
	uint8_t temp=motor_message;
	motor_message=0xf1;
#ifdef PC
    storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, temp);
	#ifdef DEBUG
	printf("move to motor msg value set to: %c\n", temp);
    #endif
#endif
	return temp;
}
