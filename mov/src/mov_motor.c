/*!
 * @file:         mov_interface.c
 * @brief:
 * @author:       Yanling Jin, Amber Olsson
 * @date:         2011-05-03
 * @version:      0.1
 * @history      
 *
 * @detail:
 */

#ifdef ARDUINO
#include "WProgram.h"
#elif defined PC
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#endif

#include "mov_interface.h"
#define NO_MESSAGE 0xB
/* BitMasking example http://www.indiabix.com/technical/c/bits-and-bytes/ */
#define BIT_POS(N)            ( 1U << (N) )
#define SET_FLAG(N, F)        ( (N) |= (F) )
#define CLR_FLAG(N, F)        ( (N) &= -(F) )

/*Motor Messages */
extern uint8_t msg1;
extern uint8_t msg2;
extern uint8_t msg3;
extern uint8_t msg4;
extern uint8_t msg5;
extern uint8_t msg6;
extern uint8_t msg7;
extern uint8_t msg8;
uint8_t message_counter;
/* 
 * 01 00 00 00
 */
void start_motors(void){

	uint8_t msg = to_MotorMessage(0,1,0,0,0,0,0,0);

#ifdef DEBUG
#ifdef PC
    printf("start motors\n");
#elif defined ARDUINO
	Serial.println("start motors\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  00 00 00 00
 */
void stop_motors(void){

	uint8_t msg = to_MotorMessage(0,0,0,0,0,0,0,0);

#ifdef DEBUG
#ifdef PC
    printf("stop motors\n");
#elif defined ARDUINO
	Serial.println("stop motors\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  10 10 00 01
 */
void increase_rear_motor(void){

	uint8_t msg = to_MotorMessage(1,0,1,0,0,0,0,1);

#ifdef DEBUG
#ifdef PC
    printf("increase rear motor\n");
#elif defined ARDUINO
	Serial.println("increase rear motor\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  10 00 00 01
 */
void decrease_rear_motor(void){

	uint8_t msg = to_MotorMessage(1,0,0,0,0,0,0,1);

#ifdef DEBUG
#ifdef PC
    printf("decrease rear motors\n");
#elif defined ARDUINO
	Serial.println("decrease rear motors\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  10 10 00 10
 */
void increase_front_motor(void){

	uint8_t msg = to_MotorMessage(1,0,1,0,0,0,1,0);

#ifdef DEBUG
#ifdef PC
    printf("increase front motor\n");
#elif defined ARDUINO
	Serial.println("increase front motor\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  10 00 00 10
 */
void decrease_front_motor(void){

	uint8_t msg = to_MotorMessage(1,0,0,0,0,0,1,0);

#ifdef DEBUG
#ifdef PC
    printf("decrease front motor\n");
#elif defined ARDUINO
	Serial.println("decrease front motor\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  10 10 01 00
 */
void increase_left_motor(void){

	uint8_t msg = to_MotorMessage(1,0,1,0,0,1,0,0);

#ifdef DEBUG
#ifdef PC
    printf("increase left motor\n");
#elif defined ARDUINO
	Serial.println("increase left motor\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);

}


/*
 *  10 00 01 00
 */
void decrease_left_motor(void){

	uint8_t msg = to_MotorMessage(1,0,0,0,0,1,0,0);

#ifdef DEBUG
#ifdef PC
    printf("decrease left motor\n");
#elif defined ARDUINO
	Serial.println("decrease left motor\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}


/*
 *  10 10 10 00
 */
void increase_right_motor(void){

	uint8_t msg = to_MotorMessage(1,0,1,0,1,0,0,0);

#ifdef DEBUG
#ifdef PC
    printf("increase right motor\n");
#elif defined ARDUINO
	Serial.println("increase right motor\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}


/*
 *  10 00 10 00
 */
void decrease_right_motor(void){

	uint8_t msg = to_MotorMessage(1,0,0,0,1,0,0,0);

#ifdef DEBUG
#ifdef PC
    printf("decrease right motor\n");
#elif defined ARDUINO
	Serial.println("decrease right motor\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);

}


/*
 *  11 10 00 11
 */
void increase_rear_decrease_front(void){
   
    uint8_t msg = to_MotorMessage(1,1,1,0,0,0,1,1);

#ifdef DEBUG
#ifdef PC
    printf("increase rear decrease front\n");
#elif defined ARDUINO
	Serial.println("increase rear decrease front\n");
#endif
#endif
    pWrite(msg);
	write_to_motor(msg);
}


/*
 *  11 00 00 11
 */
void increase_front_decrease_rear(void){
   
    uint8_t msg = to_MotorMessage(1,1,0,0,0,0,1,1);

#ifdef DEBUG
#ifdef PC
    printf("increase front decrease rear\n");
#elif defined ARDUINO
	Serial.println("increase front decrease rear\n");
#endif
#endif
    pWrite(msg);
	write_to_motor(msg);

}

/*
 *  11 10 11 00
 */
void increase_left_decrease_right(void){
   
    uint8_t msg = to_MotorMessage(1,1,1,0,1,1,0,0);

#ifdef DEBUG
#ifdef PC
    printf("increase left decrease right\n");
#elif defined ARDUINO
	Serial.println("increase left decrease right\n");
#endif
#endif
    pWrite(msg);
	write_to_motor(msg);
}

/*
 *  11 00 11 00
 */
void increase_right_decrease_left(void){

    uint8_t msg = to_MotorMessage(1,1,0,0,1,1,0,0);

#ifdef DEBUG
#ifdef PC
    printf("increase right decrease left\n");
#elif defined ARDUINO
	Serial.println("increase right decrease left\n");
#endif
#endif
    pWrite(msg);
	write_to_motor(msg);
}

/*
 *  10 10 11 11
 */
void increase_all(void){

	uint8_t msg = to_MotorMessage(1,0,1,0,1,1,1,1);

#ifdef DEBUG
#ifdef PC
    printf("increase all motors\n");
#elif defined ARDUINO
	Serial.println("increase all motors\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);

}

/*
 *  10 00 11 11
 */
void decrease_all(void){

    uint8_t msg = to_MotorMessage(1,0,0,0,1,1,1,1);

#ifdef DEBUG
#ifdef PC
    printf("decrease all motors\n");
#elif defined ARDUINO
	Serial.println("decrease all motors\n");
#endif
#endif
    pWrite(msg);
	write_to_motor(msg);
}


/*
 * 11 00 00 10
 */
void go_forwards(void){

	uint8_t msg = to_MotorMessage(1,1,0,0,0,0,1,0);

#ifdef DEBUG
#ifdef PC
    printf("go forward\n");
#elif defined ARDUINO
	Serial.println("go forward\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}

/*
 * 11 00 00 01 
 */
void go_backwards(void){

	uint8_t msg = to_MotorMessage(1,1,0,0,0,0,0,1);

#ifdef DEBUG
#ifdef PC
    printf("go backward\n");
#elif defined ARDUINO
	Serial.println("go backward\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}

/*
 * 11 10 01 00
 */
void strafe_left(void)
{
	uint8_t msg = to_MotorMessage(1,1,1,0,0,1,0,0);

#ifdef DEBUG
#ifdef PC
    printf("scrafe left\n");
#elif defined ARDUINO
	Serial.println("scrafe left\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}


/*
 * 11 00 10 00
 */
void strafe_right(void)
{
	uint8_t msg = to_MotorMessage(1,1,0,0,1,0,0,0);

#ifdef DEBUG
#ifdef PC
    printf("scrafe right\n");
#elif defined ARDUINO
	Serial.println("scrafe right\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  11 10 11 00
 */
void turn_left(void){
  
    uint8_t msg = to_MotorMessage(1,1,1,0,1,1,0,0);

#ifdef DEBUG
#ifdef PC
    printf("turn left\n");
#elif defined ARDUINO
	Serial.println("turn left\n");
#endif
#endif
    pWrite(msg);
	write_to_motor(msg);
}

/*
 *  11 00 11 00
 */
void turn_right(void)
{
    uint8_t msg = to_MotorMessage(1,1,0,0,1,1,0,0);

#ifdef DEBUG
#ifdef PC
    printf("turn right\n");
#elif defined ARDUINO
	Serial.println("turn right\n");
#endif
#endif
    pWrite(msg);
	write_to_motor(msg);
}

/*
 *  11 11 11 11
 */
void hover(void)
{
	uint8_t msg =to_MotorMessage(1,1,1,1,1,1,1,1);

#ifdef DEBUG
#ifdef PC
    printf("hover\n");
#elif defined ARDUINO
	Serial.println("hover\n");
#endif
#endif
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  land
 */
void land(void){
	hover();
	decrease_all();
#ifdef DEBUG
#ifdef PC
    printf("land\n");
#elif defined ARDUINO
	Serial.println("land\n");
#endif
#endif
}


/*
 * write a message to an array
 */
void write_to_motor(uint8_t msg){
    
    switch(message_counter){
    case 1: msg1 = msg; break;
    case 2: msg2 = msg; break;
    case 3: msg3 = msg; break;
    case 4: msg4 = msg; break;
    case 5: msg5 = msg; break;
    case 6: msg6 = msg; break;
    case 7: msg7 = msg; break;
    case 8: msg8 = msg; break;
    }
    message_counter= message_counter + 1;
}


/*
 *Clear the message array to NO MESSAGE
 */
void clear_message_array(){

    message_counter = 1;
    msg1 = NO_MESSAGE;
    msg2 = NO_MESSAGE;
    msg3 = NO_MESSAGE;
    msg4 = NO_MESSAGE;
    msg5 = NO_MESSAGE;
    msg6 = NO_MESSAGE;
    msg7 = NO_MESSAGE;
    msg8 = NO_MESSAGE;
}


/*
 *Receives if the message is increasing(boolean), is in panic mode(boolean) 
 *and the uint8_t representing the binary of the 4 affected motors 
 *
 *returns the 8 bits as a uint8_t , representing the message
 *Example:
 *<<46>> or 00100110
 *<<protocol:2 = 0, increase/decrease:1 = 1, mode:1 = 0, motors:4 = 6>>
 */
uint8_t to_MotorMessage(uint8_t ID0, uint8_t ID1, uint8_t increasing, uint8_t panicMode,
						uint8_t motor1,uint8_t motor2, uint8_t motor3, uint8_t motor4)
{
	uint8_t motors = 0;

	if(ID0 == 1)
		SET_FLAG(motors, BIT_POS(7)); 
  
	if(ID1 == 1)
		SET_FLAG(motors, BIT_POS(6));

	if(increasing == 1)
		SET_FLAG(motors, BIT_POS(5));

	if(panicMode == 1)
		SET_FLAG(motors, BIT_POS(4));

	if(motor1 == 1) 
		SET_FLAG(motors, BIT_POS(3));

	if(motor2 == 1)
		SET_FLAG(motors, BIT_POS(2));

	if(motor3 == 1) 
		SET_FLAG(motors, BIT_POS(1)) ;

	if(motor4 == 1)
		SET_FLAG(motors, BIT_POS(0)) ;
  
	return motors;
}


/*
 *  
 */
void pWrite(uint8_t msg)
{
#ifdef DEBUG
#ifdef PC
    printf("\nProtocol has this written to it: ");
#elif defined ARDUINO
	Serial.println("\nProtocol has this written to it: ");
#endif
	print_uint8_t_to_Binary(msg);
#endif
}


/*
 *  
 */
void print_uint8_t_to_Binary(uint8_t bin)
{
	uint8_t temp,bit;
	int8_t counter;

	counter =sizeof(bin) * 8;

	for(counter = counter - 1; counter >= 0; counter--){
		temp = 1 << counter;
		bit = temp & bin;

		if( bit == 0){
#ifdef PC
			printf("0");
#elif defined ARDUINO
			Serial.print("0");
#endif
		}

		else{
#ifdef PC
			printf("1");
#elif defined ARDUINO
			Serial.print("1");
#endif
		}
	}

#ifdef PC
	printf("\n");
#elif defined ARDUINO
	Serial.println();
#endif
}
