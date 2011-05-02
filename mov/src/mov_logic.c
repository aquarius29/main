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

/* BitMasking example http://www.indiabix.com/technical/c/bits-and-bytes/ */
#define BIT_POS(N)            ( 1U << (N) )
#define SET_FLAG(N, F)        ( (N) |= (F) )
#define CLR_FLAG(N, F)        ( (N) &= -(F) )

#define BUFF_YAW 5
#define BUFF_DISTSNCE 0.2
#define BUFF_PR 1

/* 
 * Print out the data from the navigation
 * For testing purpose only
 */
void testNavCommand(void) {
    printf("==============================\n");
    printf("Type = %c\n", navCommand.type);
    printf("Order = %c\n", navCommand.order);
    printf("Height = %d\n", navCommand.height);
    printf("Distance = %d\n", navCommand.distance);
    printf("Yaw = %d\n", navCommand.yaw);
    printf("Speed = %d\n", navCommand.speed);
    printf("==============================\n");
}



/*
 * parse the navigation information
 */
void command_logic(void) {
    char order = navCommand.order;
    float speed = navCommand.speed;
    distanceToTravel = navCommand.distance;
	//lift off
    if (order == 0 || order==1) {
		check_pitch_roll(0);
		check_height();
		check_heading();
    } else if (order == 2) {
		check_pitch_roll(1);
		check_height();
		check_heading();
    } else {
		land();  	
    }
}



/* 
 * 01 00 00 00
 */
void start_motors(void)
{
	char msg = to_MotorMessage(0,1,0,0,0,0,0,0);
	printf ("start motors");
	pWrite(msg);
}

/*
 *  00 00 00 00
 */
void stop_motors(void)
{

	char msg = to_MotorMessage(0,0,0,0,0,0,0,0);
	printf ("stop motors");
	pWrite(msg);
}

/*
 *  10 10 00 01
 */
void increase_rear_motor(void){

    /* simulated */
    sensorCommand.pitch = readSensorTest(sensorCommand.pitch, 'i');

	char msg = to_MotorMessage(1,0,1,0,0,0,0,1);
	printf ("increase rear motor");
	pWrite(msg);

}

/*
 *  10 00 00 01
 */
void decrease_rear_motor(void){

	char msg = to_MotorMessage(1,0,0,0,0,0,0,1);
	printf ("decrease rear motors");
	pWrite(msg);
}

/*
 *  10 10 00 10
 */
void increase_front_motor(void){

	char msg = to_MotorMessage(1,0,1,0,0,0,1,0);
	printf ("increase front motor");
	pWrite(msg);
}

/*
 *  10 00 00 10
 */
void decrease_front_motor(void){

	char msg = to_MotorMessage(1,0,0,0,0,0,1,0);
	printf ("decrease front motor");
	pWrite(msg);
}

/*
 *  10 10 01 00
 */
void increase_left_motor(void){
	char msg = to_MotorMessage(1,0,1,0,0,1,0,0);
	printf ("increase left motor");
	pWrite(msg);

}


/*
 *  10 00 01 00
 */
void decrease_left_motor(void){

	char msg = to_MotorMessage(1,0,0,0,0,1,0,0);
	printf ("decrease left motor");
	pWrite(msg);
}


/*
 *  10 10 10 00
 */
void increase_right_motor(void){

	char msg = to_MotorMessage(1,0,1,0,1,0,0,0);
	printf ("increase right motor");
	pWrite(msg);
}


/*
 *  10 00 10 00
 */
void decrease_right_motor(void){
	char msg = to_MotorMessage(1,0,0,0,1,0,0,0);
	printf ("decrease right motor");
	pWrite(msg);

}


/*
 *  11 10 00 11
 */
void increase_rear_decrease_front(void){

	char msg = to_MotorMessage(1,1,1,0,0,0,1,1);
	printf ("increase rear decrease front");
	pWrite(msg);
}


/*
 *  11 00 00 11
 */
void increase_front_decrease_rear(void){
	char msg = to_MotorMessage(1,1,0,0,0,0,1,1);
	printf ("increase front decrease rear");
	pWrite(msg);

}

/*
 *  11 10 11 00
 */
void increase_left_decrease_right(void){
	char msg = to_MotorMessage(1,1,1,0,1,1,0,0);
	printf ("increase left decrease right");
	pWrite(msg);
}

/*
 *  11 00 11 00
 */
void increase_right_decrease_left(void){

	char msg = to_MotorMessage(1,1,0,0,1,1,0,0);
	printf ("increase right decrease left");
	pWrite(msg);
}

/*
 *  10 10 11 11
 */
void increase_all(void){
	char msg = to_MotorMessage(1,0,1,0,1,1,1,1);
	printf ("increase all motors");
	pWrite(msg);

}

/*
 *  10 00 11 11
 */
void decrease_all(void){
	char msg = to_MotorMessage(1,0,0,0,1,1,1,1);
	printf ("decrease all motors");
	pWrite(msg);
}


/*
 * 11 00 00 10
 */
void go_forwards(void)
{
	char msg = to_MotorMessage(1,1,0,0,0,0,1,0);
	printf ("go forward");
	pWrite(msg);
}

/*
 * 11 00 00 01 
 */
void go_backwards(void)
{

	char msg = to_MotorMessage(1,1,0,0,0,0,0,1);
	printf ("go backward");
	pWrite(msg);
}

/*
 * 11 10 01 00
 */
void strafe_left(void)
{
	char msg = to_MotorMessage(1,1,1,0,0,1,0,0);
	printf ("scrafe left");
	pWrite(msg);
}


/*
 * 11 00 10 00
 */
void strafe_right(void)
{
	char msg = to_MotorMessage(1,1,0,0,1,0,0,0);
	printf ("scrafe right");
	pWrite(msg);
}

/*
 *  11 10 11 00
 */
void turn_left(void){
    
      /* simulated */
    sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'i');

    char msg = to_MotorMessage(1,1,0,0,1,1,0,0);
    printf ("turn left");
    pWrite(msg);
}

/*
 *  11 00 11 00
 */
void turn_right(void)
{
     /* simulated */
    sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'd');

    char msg = to_MotorMessage(1,1,0,0,1,1,0,0);
    printf ("turn right");
    pWrite(msg);
}

/*
 *  11 11 11 11
 */

void hover(void)
{
	char msg =to_MotorMessage(1,1,1,1,1,1,1,1);
	printf ("hover");
	pWrite(msg);
}

void land(void){
	hover();
	decrease_all();

}
//check the drone height
void check_height(void)
{
	int height_desire =navCommand.height;
	int height_current =sensorCommand.height;

	if(height_desire > height_current+BUFF_DISTSNCE){	
		hover();	
		increase_all();
	}
	else if(height_desire<height_current-BUFF_DISTSNCE){
		hover();
		decrease_all();
	}
	else{
		//great
	}
}

void check_heading(void)
{
	int heading_desire=navCommand.yaw;
	int heading_current=sensorCommand.yaw;

	if(heading_desire>heading_current+BUFF_YAW){
		turn_right();
	}
	else if(heading_desire<heading_current-BUFF_YAW){
		turn_left();
	}
	else{
		//great
	}
}

void check_pitch_roll(int isHovering) {

	int pitch_current=sensorCommand.pitch;
	int roll_current=sensorCommand.roll;
	int pitch_desire;
	int roll_desire;
	if(isHovering==1){
		pitch_desire=0;
		roll_desire=0;
	}
	else{
		pitch_desire=20;
		roll_desire=20;
	}
	//pitch clac
	if(pitch_current>pitch_desire+BUFF_PR){
		increase_left_decrease_right();
	}
	else if(pitch_current<pitch_desire-BUFF_PR){
	    increase_right_decrease_left();
	}
	else{
		//great
	}

	//roll calc
	if(roll_current>roll_desire+BUFF_PR){
		increase_front_decrease_rear();
	}
	else if(roll_current<roll_desire-BUFF_PR){
		increase_rear_decrease_front();
	}
	else{
		//great
	}
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

//******TEST METHODS ***/
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

int pRead_speed(){
    return 2; 
}

int readSensorTest(int currentSensor, char command){

    srand(time(NULL));
    int i = (rand() % (5 + 5 + 1) - 5);  // between 5 and -5 degree variation

    int new;
    switch (command) {
    case 'i':
	new = currentSensor + 1 + i;
	break;
    case 'd':
	new = currentSensor - 1 + i;
	break;
    }
	
	return new;
}


void printOrientation(void){
    printf("\n {pitch: %d roll: %d, yaw: %d height %d }", 
	   sensorCommand.pitch, sensorCommand.roll,sensorCommand.yaw,
	   sensorCommand.height);
}

//************End of Testing methods

void get_speed(void){

   speed = pRead_speed();
}

void get_distance_travelled(void){

   get_speed();
   distanceTraveled = speed * duration;
  printf("\n \n \n TRAVELED %d", distanceTraveled);
}

void updateDistanceToTravel(void){

    get_distance_travelled();
    distanceToTravel = distanceToTravel - distanceTraveled ;
}


