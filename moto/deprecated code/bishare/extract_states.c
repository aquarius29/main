#include <stdio.h>
#include "extract_states.h"
/* state positions in bits*//*00000000*/
/* @uthor Bishare Sufi*/
/* unsigned char 1 byte = 8 bits the size of the message
using hexadecimal*/
/* code for generating and extracting states */
/*state definition*/

#define HOVER 0xC0
#define FORWARD 0xE3
#define TURN_RIGHT 0xEC /* this code was created in the beginning of the
                           project is not used for the project */          
#define TURN_LEFT 0xCE
#define BACKWARD 0xC3

#define PANIC_STATE 0x80
#define START_STATE 0x40
#define INCREASE_MOTOR 0x20
#define DECREASE_MOTOR 0x10
#define RIGHT_MOTOR 0x8
#define LEFT_MOTOR 0x4
#define FRONT_MOTOR 0x2
#define REAR_MOTOR 0x1
#define STOP_STATE 0x0

unsigned char generate_value_Inc_motor(unsigned char motor){ // increase the speed
   return motor | INCREASE_MOTOR; // | = motor together with INCREASE_MOTOR
}

unsigned char generate_value_Dec_motor(unsigned char motor){//decrease the speed
   return motor | DECREASE_MOTOR; // | = motor together with DECREASE_MOTOR
}

unsigned char generate_value_Con_motor(unsigned char motor){
   return motor;
}

unsigned char generate_value_Pan_motor(unsigned char motor){//panic the speed
   return motor | PANIC_STATE; // | = motor together with PANIC_MOTOR
}

void extract(unsigned char st){
        if(st == START_STATE){ // constant state never change
		printf("Start State");
	}
        else if(st == FORWARD){ 
		         printf("Forward State");
        }
        else if(st == BACKWARD){ 
		         printf("Backward State");
        }
        else if(st == TURN_LEFT){ 
		         printf("Turn left State");
        }
        else if(st == TURN_RIGHT){ 
		         printf("Turn Right State");
        }
	else if(st == STOP_STATE){ // constant state  never change 
		printf("Stop State");
	}
        else{//control message
		if(st & INCREASE_MOTOR){
			printf("Increase State ");
        	}
                else{
			printf("Decrease State ");
        	}

		if(st & PANIC_STATE){
			printf("Panic State ");
        	}
		else{
			printf("NOrmal State ");
		}

                if(st & FRONT_MOTOR){
			printf("Front Motor "); 
                }  
                if(st & REAR_MOTOR){
			printf("Rear Motor "); 
                }
		if(st & LEFT_MOTOR){
			printf("Left Motor ");
		}
		if(st & RIGHT_MOTOR){ // mask motor right true =1&1 false=0&1  
			printf("Right Motor ");
		}
	}
	printf("\n");
}


int main(void){

	unsigned char st;

	st = generate_value_Inc_motor(LEFT_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Inc_motor(RIGHT_MOTOR);// generate value
	extract(st); // extract the value
        st=generate_value_Inc_motor(LEFT_MOTOR | RIGHT_MOTOR);// here is the 
	extract(st); // same, but | this means both together


	st = generate_value_Inc_motor(FRONT_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Inc_motor(REAR_MOTOR);// generate value
	extract(st); // extract the value
        st=generate_value_Inc_motor(FRONT_MOTOR | REAR_MOTOR);// here is the 
	extract(st); // same, but | this means both together


        st = generate_value_Dec_motor(LEFT_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Dec_motor(RIGHT_MOTOR);// generate value
	extract(st); // extract the value
        st =generate_value_Dec_motor(LEFT_MOTOR | RIGHT_MOTOR);// here is the 
	extract(st); // same, but | this means both together


        st = generate_value_Dec_motor(FRONT_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Dec_motor(REAR_MOTOR);// generate value
	extract(st); // extract the value
        st =generate_value_Dec_motor(FRONT_MOTOR | REAR_MOTOR);// here is the 
	extract(st); // same, but | this means both together



        st = generate_value_Con_motor(FORWARD);// generate value
	extract(st); // extract the value
        st = generate_value_Con_motor(BACKWARD);// generate value
	extract(st); // extract the value
        st = generate_value_Con_motor(TURN_LEFT);// generate value
	extract(st); // extract the value
        st = generate_value_Con_motor(TURN_RIGHT);// generate value
	extract(st); // extract the value


	/*st = generate_value_Pan_motor(PANIC_STATE | TURN_LEFT);// generate value
	extract(st); // extract the value*/
        st = generate_value_Pan_motor(LEFT_MOTOR | INCREASE_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Pan_motor(RIGHT_MOTOR | DECREASE_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Pan_motor(LEFT_MOTOR | DECREASE_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Pan_motor(RIGHT_MOTOR | INCREASE_MOTOR);// generate value
	extract(st); // extract the value
        /*st = generate_value_Pan_motor(TURN_RIGHT);// generate value
        extract(st);// exract te value*/


	/*st = generate_value_Pan_motor(FORWARD);// generate value
        extract(st); // extract the value*/
        st = generate_value_Pan_motor(FRONT_MOTOR | INCREASE_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Pan_motor(REAR_MOTOR | DECREASE_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Pan_motor(FRONT_MOTOR | DECREASE_MOTOR);// generate value
        extract(st); // extract the value
        st = generate_value_Pan_motor(REAR_MOTOR | INCREASE_MOTOR);// generate value
	extract(st); // extract the value
       /* st = generate_value_Pan_motor(BACKWARD);
        extract(st);// extract the value */
  
}


