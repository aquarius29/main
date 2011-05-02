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
 * 
 */
void command_logic(void) {
    char order = navCommand.order;
    float speed = navCommand.speed;
    
	//lift off
    if (order == 0 || order==1) {
	distanceToTravel = 0;
		check_pitch_roll(0);
		check_height();
		check_heading();
    } else if (order == 2) {
	distanceToTravel = navCommand.distance;
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

    if(height_desire > height_current+BUFF_DISTSNCE){	
	hover();	
	increase_all();
		 /* simulated */
    sensorCommand.height = readSensorTest(sensorCommand.height, 'i');
    }
    else if(height_desire<height_current-BUFF_DISTSNCE){
	hover();
	decrease_all();
	 /* simulated */
    sensorCommand.height = readSensorTest(sensorCommand.height, 'd');
    }
    else{
	heightArrived = 1;
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


int pRead_speed(){
    return 5; 
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
