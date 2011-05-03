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


#define BUFF_YAW 5
#define BUFF_DISTSNCE 0.2
#define BUFF_PR 1
#define SPEED 5

/* 
 * Print out the data from the navigation
 * For testing purpose only
 */
void printNavCommand(void) {
    printf("==============================\n");
    printf("Type = %c\n", navCommand.type);
    printf("Order = %c\n", navCommand.order);
    printf("Height = %d\n", navCommand.height);
    printf("Distance = %d\n", navCommand.distance);
    printf("Yaw = %d\n", navCommand.yaw);
    printf("==============================\n");
}

/*
 * 
 */
void command_logic(void) {
	printNavCommand();
	printOrientation();
   char order = navCommand.order;  
	//lift off
    if (order == '0') {
		distanceToTravel = 0;
		check_pitch_roll(0);
		check_height();
		check_heading();
    } else if (order == '1') {
		updateDistanceToTravel();
		check_pitch_roll(1);
		check_height();
		check_heading();
    } else {
			land();  	
    }
}

//check the drone height
void check_height(void)
{
    int height_desire =navCommand.height;
    int height_current =sensorCommand.height;

    if(height_current > height_desire+BUFF_DISTSNCE){	
		hover();	
		decrease_all();

		/* simulated */
		sensorCommand.height = readSensorTest(sensorCommand.height, 'd');
    }
    else if(height_current<height_desire-BUFF_DISTSNCE){
		hover();
		increase_all();

		/* simulated */
		sensorCommand.height = readSensorTest(sensorCommand.height, 'i');
    }
    else{
		heightArrived = 1;
    }
}

void check_heading(void)
{
    int heading_desire=navCommand.yaw;
    int heading_current=sensorCommand.yaw;

    if(heading_current>heading_desire+BUFF_YAW){
		turn_left();
     /* simulated */
    sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'd');
    }
    else if(heading_current<heading_desire-BUFF_YAW){
		turn_left();
      /* simulated */
    sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'i');
    }
    else{
		yawArrived = 1;
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
		/* simulated */
		sensorCommand.pitch = readSensorTest(sensorCommand.pitch, 'd');
	}
	else if(pitch_current<pitch_desire-BUFF_PR){
	    increase_right_decrease_left();
		/* simulated */
		sensorCommand.pitch = readSensorTest(sensorCommand.pitch, 'i');
	}
	else{
		//great
	}

	//roll calc
	if(roll_current>roll_desire+BUFF_PR){
		increase_front_decrease_rear();
		/* simulated */
		sensorCommand.roll = readSensorTest(sensorCommand.roll, 'd');
	}
	else if(roll_current<roll_desire-BUFF_PR){
		increase_rear_decrease_front();		
		/* simulated */
		sensorCommand.roll = readSensorTest(sensorCommand.roll, 'i');
	}
	else{
		//great
	}
}

//(rand() % (max - min + 1) + min);
int readSensorTest(int currentSensor, char command){
    srand(time(NULL));
    int i = (rand() % (5 - 0 + 1) + 0);  // between 5 and -5 degree variation
    int new;

    switch (command) {
    case 'i':
		new = currentSensor + i;
		break;
    case 'd':
		new = currentSensor - i;
		break;
    }
	
	return new;
}


void printOrientation(void)
{
    printf("\n {pitch: %d roll: %d, yaw: %d height %d }\n", 
		   sensorCommand.pitch, sensorCommand.roll,sensorCommand.yaw,
		   sensorCommand.height);
}


void updateDistanceToTravel(void){
    distanceTraveled = SPEED * duration;
    distanceToTravel = distanceToTravel - distanceTraveled ;
}
