/*
 * file:         mov_interface.c
 * brief:
 * author:       Yanling Jin, Amber Olsson
 * date:         2011-05-03
 * version:      0.1
 * history      
 *
 * detail:
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "mov_interface.h"

/* BitMasking example http://www.indiabix.com/technical/c/bits-and-bytes/ */
#define BIT_POS(N)            ( 1U << (N) )
#define SET_FLAG(N, F)        ( (N) |= (F) )
#define CLR_FLAG(N, F)        ( (N) &= -(F) )

#ifdef DEBUG
#define DEBUG_PRINT(s)        printf(s)
#else
#define DEBUG_PRINT(s)
#endif


/* 
 * 01 00 00 00
 */
void start_motors(void)
{
	uint8_t msg = to_MotorMessage(0,1,0,0,0,0,0,0);
	DEBUG_PRINT ("start motors\n");
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  00 00 00 00
 */
void stop_motors(void)
{

	uint8_t msg = to_MotorMessage(0,0,0,0,0,0,0,0);
	DEBUG_PRINT ("stop motors\n");
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  10 10 00 01
 */
void increase_rear_motor(void){
	uint8_t msg = to_MotorMessage(1,0,1,0,0,0,0,1);
	DEBUG_PRINT ("increase rear motor\n");
	pWrite(msg);
	write_to_motor(msg);

}

/*
 *  10 00 00 01
 */
void decrease_rear_motor(void){

	uint8_t msg = to_MotorMessage(1,0,0,0,0,0,0,1);
	DEBUG_PRINT ("decrease rear motors\n");
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  10 10 00 10
 */
void increase_front_motor(void){

	uint8_t msg = to_MotorMessage(1,0,1,0,0,0,1,0);
	DEBUG_PRINT  ("increase front motor\n");
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  10 00 00 10
 */
void decrease_front_motor(void){

	uint8_t msg = to_MotorMessage(1,0,0,0,0,0,1,0);
	DEBUG_PRINT  ("decrease front motor\n");
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  10 10 01 00
 */
void increase_left_motor(void){
	uint8_t msg = to_MotorMessage(1,0,1,0,0,1,0,0);
	DEBUG_PRINT ("increase left motor\n");
	pWrite(msg);
	write_to_motor(msg);

}


/*
 *  10 00 01 00
 */
void decrease_left_motor(void){

	uint8_t msg = to_MotorMessage(1,0,0,0,0,1,0,0);
	DEBUG_PRINT ("decrease left motor\n");
	pWrite(msg);
	write_to_motor(msg);
}


/*
 *  10 10 10 00
 */
void increase_right_motor(void){

	uint8_t msg = to_MotorMessage(1,0,1,0,1,0,0,0);
	DEBUG_PRINT  ("increase right motor\n");
	pWrite(msg);
	write_to_motor(msg);
}


/*
 *  10 00 10 00
 */
void decrease_right_motor(void){
	uint8_t msg = to_MotorMessage(1,0,0,0,1,0,0,0);
	DEBUG_PRINT  ("decrease right motor\n");
	pWrite(msg);
	write_to_motor(msg);

}


/*
 *  11 10 00 11
 */
void increase_rear_decrease_front(void){
   
    uint8_t msg = to_MotorMessage(1,1,1,0,0,0,1,1);
    DEBUG_PRINT  ("increase rear decrease front\n");
    pWrite(msg);
	write_to_motor(msg);
}


/*
 *  11 00 00 11
 */
void increase_front_decrease_rear(void){
   
    uint8_t msg = to_MotorMessage(1,1,0,0,0,0,1,1);
   DEBUG_PRINT  ("increase front decrease rear\n");
    pWrite(msg);
	write_to_motor(msg);

}

/*
 *  11 10 11 00
 */
void increase_left_decrease_right(void){
   
    uint8_t msg = to_MotorMessage(1,1,1,0,1,1,0,0);
    DEBUG_PRINT  ("increase left decrease right\n");
    pWrite(msg);
	write_to_motor(msg);
}

/*
 *  11 00 11 00
 */
void increase_right_decrease_left(void){

    uint8_t msg = to_MotorMessage(1,1,0,0,1,1,0,0);
    DEBUG_PRINT  ("increase right decrease left\n");
    pWrite(msg);
	write_to_motor(msg);
}

/*
 *  10 10 11 11
 */
void increase_all(void){
	uint8_t msg = to_MotorMessage(1,0,1,0,1,1,1,1);
	DEBUG_PRINT  ("increase all motors\n");
	pWrite(msg);
	write_to_motor(msg);

}

/*
 *  10 00 11 11
 */
void decrease_all(void){
    uint8_t msg = to_MotorMessage(1,0,0,0,1,1,1,1);
    DEBUG_PRINT  ("decrease all motors\n");
    pWrite(msg);
	write_to_motor(msg);
}


/*
 * 11 00 00 10
 */
void go_forwards(void)
{
	uint8_t msg = to_MotorMessage(1,1,0,0,0,0,1,0);
	DEBUG_PRINT ("go forward\n");
	pWrite(msg);
	write_to_motor(msg);
}

/*
 * 11 00 00 01 
 */
void go_backwards(void)
{

	uint8_t msg = to_MotorMessage(1,1,0,0,0,0,0,1);
	DEBUG_PRINT ("go backward\n");
	pWrite(msg);
	write_to_motor(msg);
}

/*
 * 11 10 01 00
 */
void strafe_left(void)
{
	uint8_t msg = to_MotorMessage(1,1,1,0,0,1,0,0);
	DEBUG_PRINT  ("scrafe left\n");
	pWrite(msg);
	write_to_motor(msg);
}


/*
 * 11 00 10 00
 */
void strafe_right(void)
{
	uint8_t msg = to_MotorMessage(1,1,0,0,1,0,0,0);
	DEBUG_PRINT  ("scrafe right\n");
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  11 10 11 00
 */
void turn_left(void){
  
    uint8_t msg = to_MotorMessage(1,1,0,0,1,1,0,0);
    DEBUG_PRINT  ("turn left\n");
    pWrite(msg);
	write_to_motor(msg);
}

/*
 *  11 00 11 00
 */
void turn_right(void)
{
    uint8_t msg = to_MotorMessage(1,1,0,0,1,1,0,0);
    DEBUG_PRINT ("turn right\n");
    pWrite(msg);
	write_to_motor(msg);
}

/*
 *  11 11 11 11
 */
void hover(void)
{
	uint8_t msg =to_MotorMessage(1,1,1,1,1,1,1,1);
	DEBUG_PRINT  ("hover\n");
	pWrite(msg);
	write_to_motor(msg);
}

/*
 *  land
 */
void land(void){
	hover();
	decrease_all();
	DEBUG_PRINT ("land\n");
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
	DEBUG_PRINT ("\nProtocol has this written to it: ");
#ifdef DEBUG
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

	for(counter = counter - 1; counter >= 0; counter--)
		{
			temp = 1 << counter;
			bit = temp & bin;
			if( bit == 0)
				printf("0");
			else
				printf("1");
		}

	printf("\n");
}
