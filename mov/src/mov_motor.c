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

#include "mov_interface.h"

/* BitMasking example http://www.indiabix.com/technical/c/bits-and-bytes/ */
#define BIT_POS(N)            ( 1U << (N) )
#define SET_FLAG(N, F)        ( (N) |= (F) )
#define CLR_FLAG(N, F)        ( (N) &= -(F) )


/* 
 * 01 00 00 00
 */
void start_motors(void)
{
	char msg = to_MotorMessage(0,1,0,0,0,0,0,0);
	printf ("start motors\n");
	pWrite(msg);
}

/*
 *  00 00 00 00
 */
void stop_motors(void)
{

	char msg = to_MotorMessage(0,0,0,0,0,0,0,0);
	printf ("stop motors\n");
	pWrite(msg);
}

/*
 *  10 10 00 01
 */
void increase_rear_motor(void){

 
	char msg = to_MotorMessage(1,0,1,0,0,0,0,1);
	printf ("increase rear motor\n");
	pWrite(msg);

}

/*
 *  10 00 00 01
 */
void decrease_rear_motor(void){

	char msg = to_MotorMessage(1,0,0,0,0,0,0,1);
	printf ("decrease rear motors\n");
	pWrite(msg);
}

/*
 *  10 10 00 10
 */
void increase_front_motor(void){

	char msg = to_MotorMessage(1,0,1,0,0,0,1,0);
	printf ("increase front motor\n");
	pWrite(msg);
}

/*
 *  10 00 00 10
 */
void decrease_front_motor(void){

	char msg = to_MotorMessage(1,0,0,0,0,0,1,0);
	printf ("decrease front motor\n");
	pWrite(msg);
}

/*
 *  10 10 01 00
 */
void increase_left_motor(void){
	char msg = to_MotorMessage(1,0,1,0,0,1,0,0);
	printf ("increase left motor\n");
	pWrite(msg);

}


/*
 *  10 00 01 00
 */
void decrease_left_motor(void){

	char msg = to_MotorMessage(1,0,0,0,0,1,0,0);
	printf ("decrease left motor\n");
	pWrite(msg);
}


/*
 *  10 10 10 00
 */
void increase_right_motor(void){

	char msg = to_MotorMessage(1,0,1,0,1,0,0,0);
	printf ("increase right motor\n");
	pWrite(msg);
}


/*
 *  10 00 10 00
 */
void decrease_right_motor(void){
	char msg = to_MotorMessage(1,0,0,0,1,0,0,0);
	printf ("decrease right motor\n");
	pWrite(msg);

}


/*
 *  11 10 00 11
 */
void increase_rear_decrease_front(void){
   
    char msg = to_MotorMessage(1,1,1,0,0,0,1,1);
    printf ("increase rear decrease front\n");
    pWrite(msg);
}


/*
 *  11 00 00 11
 */
void increase_front_decrease_rear(void){
   
    char msg = to_MotorMessage(1,1,0,0,0,0,1,1);
    printf ("increase front decrease rear\n");
    pWrite(msg);

}

/*
 *  11 10 11 00
 */
void increase_left_decrease_right(void){
   
    char msg = to_MotorMessage(1,1,1,0,1,1,0,0);
    printf ("increase left decrease right\n");
    pWrite(msg);
}

/*
 *  11 00 11 00
 */
void increase_right_decrease_left(void){

    char msg = to_MotorMessage(1,1,0,0,1,1,0,0);
    printf ("increase right decrease left\n");
    pWrite(msg);
}

/*
 *  10 10 11 11
 */
void increase_all(void){
	char msg = to_MotorMessage(1,0,1,0,1,1,1,1);
	printf ("increase all motors\n");
	pWrite(msg);

}

/*
 *  10 00 11 11
 */
void decrease_all(void){
    char msg = to_MotorMessage(1,0,0,0,1,1,1,1);
    printf ("decrease all motors\n");
    pWrite(msg);
}


/*
 * 11 00 00 10
 */
void go_forwards(void)
{
	char msg = to_MotorMessage(1,1,0,0,0,0,1,0);
	printf ("go forward\n");
	pWrite(msg);
}

/*
 * 11 00 00 01 
 */
void go_backwards(void)
{

	char msg = to_MotorMessage(1,1,0,0,0,0,0,1);
	printf ("go backward\n");
	pWrite(msg);
}

/*
 * 11 10 01 00
 */
void strafe_left(void)
{
	char msg = to_MotorMessage(1,1,1,0,0,1,0,0);
	printf ("scrafe left\n");
	pWrite(msg);
}


/*
 * 11 00 10 00
 */
void strafe_right(void)
{
	char msg = to_MotorMessage(1,1,0,0,1,0,0,0);
	printf ("scrafe right\n");
	pWrite(msg);
}

/*
 *  11 10 11 00
 */
void turn_left(void){
  
    char msg = to_MotorMessage(1,1,0,0,1,1,0,0);
    printf ("turn left\n");
    pWrite(msg);
}

/*
 *  11 00 11 00
 */
void turn_right(void)
{
    char msg = to_MotorMessage(1,1,0,0,1,1,0,0);
    printf ("turn right\n");
    pWrite(msg);
}

/*
 *  11 11 11 11
 */
void hover(void)
{
	char msg =to_MotorMessage(1,1,1,1,1,1,1,1);
	printf ("hover\n");
	pWrite(msg);
}

/*
 *  
 */
void land(void){
	hover();
	decrease_all();
	printf("land\n");
}

/*
 *Receives if the message is increasing(boolean), is in panic mode(boolean) 
 *and the char representing the binary of the 4 affected motors 
 *
 *returns the 8 bits as a char , representing the message
 *Example:
 *<<46>> or 00100110
 *<<protocol:2 = 0, increase/decrease:1 = 1, mode:1 = 0, motors:4 = 6>>
 */
char to_MotorMessage(char ID0, char ID1, char increasing, char panicMode,
					 char motor1,char motor2, char motor3, char motor4)
{
	char motors = 0;

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
void pWrite(char msg)
{
	//	printf("\nProtocol has this written to it: ");
	//	print_char_to_Binary(msg);
}


/*
 *  
 */
void print_char_to_Binary(char bin)
{
	char counter,temp,bit;

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
