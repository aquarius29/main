/* Module: msg_parsing.c
*  Author:  Rahwa Bahta, Reza Moussavi
*  This modul will pars the incoming message form filter and call diffrent function
*/


#include<stdio.h>
#include <stdlib.h>
#include"state_definitions.h"


// Driver Functionns which will moved to motor_driver.c file
// Here we use them as testing functions

void motor_driver_hover(){
	printf("Motor Hover\n");
}

void motor_driver_start(){
	printf("Motor Start\n");
}

void motor_driver_stop(){
	printf("Motor Stop\n");
}

void motor_driver_forward(char panic){
	printf("Forward %s\n",panic?"Panic":"Normal");
}

void motor_driver_backward(char panic){
	printf("Backward %s\n",panic?"Panic":"Normal");
}

void motor_driver_turn_right(char panic){
	printf("Turn right %s\n",panic?"Panic":"Normal");
}

void motor_driver_turn_left(char panic){
	printf("Turn left %s\n",panic?"Panic":"Normal");
}

void motor_driver_apply_left(char increase,char panic){
	printf("LeftMotor %s %s\n",increase?"Increase":"Decrease",panic?"Panic":"Normal");
}

void motor_driver_apply_right(char increase,char panic){
	printf("RightMotor %s %s\n",increase?"Increase":"Decrease",panic?"Panic":"Normal");
}

void motor_driver_apply_front(char increase,char panic){
	printf("FrontMotor %s %s\n",increase?"Increase":"Decrease",panic?"Panic":"Normal");
}

void motor_driver_apply_rear(char increase,char panic){
	printf("RearMotor %s %s\n",increase?"Increase":"Decrease",panic?"Panic":"Normal");
}

//END of Driver Functions

void apply_message_control(unsigned char msg){
	if(msg&MSG_FRONT_MOTOR_MASK){
		motor_driver_apply_front(msg&MSG_INCREASE_MASK,msg&MSG_PANIC_MASK);
	}
	if(msg&MSG_REAR_MOTOR_MASK){
		motor_driver_apply_rear(msg&MSG_INCREASE_MASK,msg&MSG_PANIC_MASK);
	}
	if(msg&MSG_LEFT_MOTOR_MASK){
		motor_driver_apply_left(msg&MSG_INCREASE_MASK,msg&MSG_PANIC_MASK);
	}
	if(msg&MSG_RIGHT_MOTOR_MASK){
		motor_driver_apply_right(msg&MSG_INCREASE_MASK,msg&MSG_PANIC_MASK);
	}
}

void apply_message_special(unsigned char msg){

}

void apply_message(unsigned char msg){
	switch(msg & MSG_ID_MASK){
		case START_MOTOR:
			motor_driver_start();
			break;
		case STOP_MOTOR:
			motor_driver_stop();
			break;
		case MSG_CONTROL_MASK:
			apply_message_control(msg);
			break;
		case MSG_SPECIAL_MASK:
			apply_message_control(msg);
			break;
	}
}

/*
void hexa_to_bits(unsigned char msg)
{

	switch(msg) 
	{
		case START_MOTOR: start_motor();
		break;
		case STOP_MOTOR: stopmotor();
		break;
		case INCREASE_REAR_MOTOR: rear_motor(INCREASE);
		break;
		case DECREASE_REAR_MOTOR: rear_motor(DECREASE);
		break;
		case INCREASE_FRONT_MOTOR: front_motor(INCREASE);
		break;	
		case DECREASE_FRONT_MOTOR: front_motor(DECREASE);
		break;
		case INCREASE_LEFT_MOTOR: left_motor(INCREASE);
		break;
		case  DECREASE_LEFT_MOTOR: left_motor(DECREASE);
		break;
		case  INCREASE_RIGHT_MOTOR: right_motor(INCREASE);
		break;
		case DECREASE_RIGHT_MOTOR : right_motor(DECREASE);
		break;
		case DECREASE_FRONT_INCREASE_REAR : front_motor(DECREASE); rear_motor(INCREASE);
		break;
		case DECREASE_REAR_INCREASE_FRONT: rear_motor(DECREASE); front_motor(INCREASE);
		break;
		case DECREASE_RIGHT_INCREASE_LEFT: right_motor(DECREASE); left_motor(INCREASE);
		break;
		case DECREASE_LEFT_INCREASE_RIGHT:  left_motor(DECREASE); right_motor(INCREASE);
		break;
		case PANIC_INCREASE_REAR_MOTOR: rear_motor(PANIC_INCREASE);
		break;
		case  PANIC_DECREASE_REAR_MOTOR: rear_motor(PANIC_DECEASE);
		break;
		case PANIC_INCREASE_FRONT_MOTOR : front_motor(PANIC_INCREASE);
		break;
		case PANIC_DECREASE_FRONT_MOTOR: front_motor(PANIC_DECEASE);
		break;
		case PANIC_INCREASE_LEFT_MOTOR: left_motor(PANIC_INCREASE);
		break;
		case  PANIC_DECREASE_LEFT_MOTOR: left_motor(PANIC_DECREASE);
		break;
		case PANIC_INCREASE_RIGHT_MOTOR: right_motor(PANIC_INCREASE);
		break;
		case PANIC_DECREASE_RIGHT_MOTOR: right_motor(PANIC_DECREASE);
		break;
		case PANIC_FORWARD: go_forward();
		break;
		case PANIC_BACKWARD: go_backward();
		break;
		case PANIC_TURN_RIGHT : turn_right();
		break;
		case PANIC_TURN_LEFT : turn_left();
		break;
		case FORWARD: go_forward();
		break;
		case BACKWARD: go_backward();
		break;
		case TURN_RIGHT: turn_right();
		break;
		case TURN_LEFT: turn_left();
		break;
		
	}
}
*/	



/*main(){
	int msg;
	printf("hexa",msg);
	scanf("%x",&msg);
	unsigned char message_pars(struct bits_type msg);
	return;
unsigned char message_pars(struct bits_type msg){
	
}*/