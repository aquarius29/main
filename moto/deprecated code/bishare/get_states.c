#include <stdio.h>

/* state positions in bits*//*00000000*/
/* @uthor Bishare Sufi*/
/* unsigned char 1 byte = 8 bits the size of the message
using decimal*/
/* this code is almost the same like the extract_states one*/

/*#define PANIC_TURN_RIGHT 252
#define PANIC_FORWARD 243
#define PANIC_TURN_LEFT 220
#define PANIC_BACKWARD 211
#define PANIC_INC_REM 177
#define PANIC_INC_FM 178
#define PANIC_INC_LM 180
#define PANIC_INC_RM 184
#define PANIC_DEC_REM 145
#define PANIC_DEC_FM 146
#define PANIC_DEC_LM 148
#define PANIC_DEC_RM 152*/

#define HOVER 255
#define FORWARD 227
#define TURN_RIGHT 236
#define TURN_LEFT 206
#define BACKWARD 195

#define PANIC_STATE 128
#define CONTROL_MOTOR 64
#define START_STATE 15
#define INCREASE_MOTOR 32
#define DECREASE_MOTOR 16
#define RIGHT_MOTOR 8
#define LEFT_MOTOR 4
#define FRONT_MOTOR 2
#define REAR_MOTOR 1
#define STOP_STATE 0

unsigned char generate_value_Inc_motor(unsigned char motor){ // increase the speed
   return motor | INCREASE_MOTOR; // | = motor together with INCREASE_MOTOR
}

unsigned char generate_value_Dec_motor(unsigned char motor){//decrease the speed
   return motor | DECREASE_MOTOR; // | = motor together with DECREASE_MOTOR
}

unsigned char generate_value_Con_motor(unsigned char motor){//control the speed
   return motor | CONTROL_MOTOR; // | = motor together with CONTROL_MOTOR
}

unsigned char generate_value_Pan_motor(unsigned char motor){//panic the speed
   return motor | PANIC_STATE; // | = motor together with PANIC_MOTOR
}


void extract(unsigned char st){
        if(st == START_STATE){ // const state never change
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

            else if(st == STOP_STATE){ // const state  never change
		      printf("Stop State");
	}

	else{
		if(st & INCREASE_MOTOR){
			printf("Increase State ");
        	}

                else if(st & DECREASE_MOTOR){
			     printf("Decrease State ");
        	}

                else if(st & CONTROL_MOTOR){
			     printf("Control State ");
		}

                else if(st & PANIC_STATE){
			     printf("Panic State ");
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
        st = generate_value_Inc_motor(LEFT_MOTOR | RIGHT_MOTOR);// here is the 
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
        st = generate_value_Dec_motor(LEFT_MOTOR | RIGHT_MOTOR);// here is the 
	extract(st); // same, but | this means both together

        st = generate_value_Dec_motor(FRONT_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Dec_motor(REAR_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Dec_motor(FRONT_MOTOR | REAR_MOTOR);// here is the 
	extract(st); // same, but | this means both together


        st = generate_value_Con_motor(FORWARD);// generate value
	extract(st); // extract the value
        st = generate_value_Con_motor(BACKWARD);// generate value
	extract(st); // extract the value
        st = generate_value_Con_motor(TURN_LEFT);// generate value
	extract(st); // extract the value
        st = generate_value_Con_motor(TURN_RIGHT);// generate value
	extract(st); // extract the value


	st = generate_value_Con_motor(LEFT_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Con_motor(RIGHT_MOTOR);// generate value
	extract(st); // extract the value
        st=generate_value_Con_motor(LEFT_MOTOR | RIGHT_MOTOR);// here is the 
	extract(st); // same, but | this means both together


	st = generate_value_Con_motor(FRONT_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Con_motor(REAR_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Con_motor(FRONT_MOTOR | REAR_MOTOR);// here is the 
	extract(st); // same, but | this means both together

  
        st = generate_value_Pan_motor(LEFT_MOTOR | RIGHT_MOTOR);// generate value
	extract(st); // extract the value
	st = generate_value_Pan_motor(LEFT_MOTOR | INCREASE_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Pan_motor( RIGHT_MOTOR | DECREASE_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Pan_motor(LEFT_MOTOR | DECREASE_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Pan_motor( RIGHT_MOTOR | INCREASE_MOTOR);// generate value
        extract(st); // extract the value

        st = generate_value_Pan_motor(FRONT_MOTOR | REAR_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Pan_motor(FRONT_MOTOR | INCREASE_MOTOR);// generate value
	extract(st); // extract the value    
        st = generate_value_Pan_motor(REAR_MOTOR | DECREASE_MOTOR);// generate value
	extract(st); // extract the value*/
        st = generate_value_Pan_motor(FRONT_MOTOR | DECREASE_MOTOR);// generate value
	extract(st); // extract the value
        st = generate_value_Pan_motor(REAR_MOTOR | INCREASE_MOTOR);// generate value
	extract(st); // extract the value*/

      
        
 }



