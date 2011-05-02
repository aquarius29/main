/*****************************************************************************
 * Product: movement.c
 * Version: 0.1
 * Created: April 4 2011
 * History:
 *          
 *
 *
 * Movement/CA Group
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "mov_interface.h"


// BitMasking example http://www.indiabix.com/technical/c/bits-and-bytes/
#define BIT_POS(N)            ( 1U << (N) )
#define SET_FLAG(N, F)        ( (N) |= (F) )
#define CLR_FLAG(N, F)        ( (N) &= -(F) )

#define WEIGHT 5
#define G 9.81
#define INCREMENT 5

<<<<<<< HEAD
int isHovering = 1;
=======
>>>>>>> 223ece499c18c9454a45621fcfa1b8fbd582f737

///////struct control_message motor_msg;

/* 
 * Print out the data from the navigation
 * For testing purpose only
 */
void test(void) {
    printf("==============================\n");
    printf("Type = %c\n", navCommand.type);
    printf("Order = %c\n", navCommand.order);
    printf("Height = %d\n", navCommand.height);
    printf("Distance = %d\n", navCommand.distance);
    printf("Yaw = %d\n", navCommand.yaw);
    printf("Speed = %d\n", navCommand.speed);
    printf("==============================\n");
}

//************************************************************
// 
// 0100 0000 (start)
//************************************************************
void start_motors()
{
  char msg = 0;
  SET_FLAG(msg, BIT_POS(6));
  pWrite(msg);
}

//************************************************************
//
//  0000 0000 (stop)
//************************************************************
void stop_motors()
{
  char msg = 0;
  pWrite(msg);
}

//check the drone height
void check_height(void){
	int height_desire =navCommand.height;
	int height_current =sensor.height;

	if(height_desire > height_current){	
		hover();	
		//increase all motors
	}
	else if(height_desire<height_current){
		hover();
		//decrease all motors
	}
	else{
		hover();
	}
}

void check_heading(void){


	int heading_desire=navCommand.yaw;
	int heading_current=sensor.yaw;

	if(heading_desire-heading_current>0){
		//rotate right
	}
	else if(heading_desire-heading_current<0){
		//rotate left
	}
	else{
		hover();
	}
}

void check_pitch_roll(void){

	int pitch_current=sensor.pitch;
	int roll_current=sensor.roll;
	if()



}

//************************************************************
//
//  1111 1111 (hover)
//************************************************************
void hover()
{
  char msg = 0;
  msg = ~msg;
  pWrite(msg);
}


//************************************************************
//
//Go Left without turning (Strafe)
//0110 1100 (left, decreases left motor and increases right motor)
//************************************************************
void go_left_no_strafe()
{
  char msg = to_AffectedMotorBinary(1,1,0,0);
  SET_FLAG(msg, BIT_POS(6));
  msg = to_MotorMessage(1,0,msg);
  pWrite(msg);
}


//************************************************************
//
//Go Right without turning (Strafe)
//0100 1100 (right, increases left motor and decreases right motor)
//************************************************************
void go_right_no_strafe()
{
  char msg = to_AffectedMotorBinary(1,1,0,0);
  SET_FLAG(msg, BIT_POS(6));
  msg = to_MotorMessage(0,0,msg);
  pWrite(msg);
}


//************************************************************
//Go Forwards
//
//0110 0011 (forward, decreases front motor and increases rear motor)
//************************************************************
void go_forwards()
{

     /*   motor_msg.rear=1;
	motor_msg.left=1;
	motor_msg.increase=1;
	motor_msg.panic=1;*/

  char msg = to_AffectedMotorBinary(0,0,1,1);
  SET_FLAG(msg, BIT_POS(6));
  msg = to_MotorMessage(1,0,msg);
  pWrite(msg);
}

//************************************************************
//Go Backwards
//
//0100 0011 (forward, decreases front motor and increases rear motor)
//************************************************************
void go_backwards()
{

  char msg = to_AffectedMotorBinary(0,0,1,1);
	/*motor_msg.rear=1;
	motor_msg.right=1;
	motor_msg.increase=1;
	motor_msg.panic=1;*/
  SET_FLAG(msg, BIT_POS(6));
  msg = to_MotorMessage(0,0,msg);
  pWrite(msg);
}


//************************************************************
//Receives if the message is increasing(boolean), is in panic mode(boolean) 
//and the char representing the binary of the 4 affected motors 
//
// returns the 8 bits as a char , representing the message
//
//Example:
//<<46>> or 00100110
//<<protocol:2 = 0, increase/decrease:1 = 1, mode:1 = 0, motors:4 = 6>>
//************************************************************
char to_MotorMessage(char ID0, char ID1, char increasing, char panicMode, char motor1,char motor2, char motor3, char motor4)
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

//*******TEST METHODS
void pWrite(char msg)
{
  printf("\nProtocol has this written to it: ");
  print_char_to_Binary(msg);
}

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

//************End of Testing methods
