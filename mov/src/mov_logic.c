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


#define BUFF_YAW 1
#define BUFF_DISTSNCE 1
#define BUFF_PR 1
#define SPEED 5


extern int distanceToTravel;
extern int distanceTraveled;

extern int yawArrived;
extern int heightArrived;

extern int changingAltitude;
extern int changingHeading;

extern int duration;

extern struct nav navCommand;
extern struct sensor sensorCommand;
extern struct sensor oldSensorCommand;


/*
 * 
 */
void command_logic(void) {
    printOrientation();
    char order = navCommand.order;  
    //lift off
    if (order == '0') {
		distanceToTravel = 0;
		check_heading();
		check_pitch_roll(0);
		check_changingAltitude();
		check_height();
    } else if (order == '1') {
		updateDistanceToTravel();
		check_heading();
		check_pitch_roll(1);
		check_changingAltitude();
		check_height();
    } else if(order == '2') {
		distanceToTravel = 0;
		check_pitch_roll(0);
		check_heading();
		check_changingAltitude();
		if (sensorCommand.height <= 0){
			heightArrived = 1;
		}
		else {
			land(); 
 
#ifdef SIMULATOR
			/* simulated */
			sensorCommand.height = readSensorTest(sensorCommand.height, 'd');
#endif
		} 

    }
	else {
		stop_motors();
	}
}

void check_changingAltitude(void){
    if(oldSensorCommand.height != sensorCommand.height + BUFF_DISTSNCE)
		changingAltitude = 1;
    else
		changingAltitude = 0;

}

//check the drone height
void check_height(void)
{
    printf("!!!!!!!!!!!!!check height: \n");
    int height_desire =navCommand.height;
    int height_current =sensorCommand.height;

    if(height_current > height_desire+BUFF_DISTSNCE){	
		if(changingAltitude == 1) {
		    hover();	
		    decrease_all();
		}

#ifdef SIMULATOR
		/* simulated */
		sensorCommand.height = readSensorTest(sensorCommand.height, 'd');
#endif
    }
    else if(height_current<height_desire-BUFF_DISTSNCE){
		if(changingAltitude == 1) {	
			hover();
			//printf("&&&&&&&&&&&&&&INCREASED&&&&&&&&&&&&&&&");
			increase_all();
		}
		
#ifdef SIMULATOR
		/* simulated */		
		sensorCommand.height = readSensorTest(sensorCommand.height, 'i');
#endif

    }
    else{
		hover();
		heightArrived = 1;
    }
    printOrientation();
}



void check_heading(void)
{
    printf("!!!!!!!!!!!!!check heading: \n");
    int heading_desire=navCommand.yaw;
    int heading_current=sensorCommand.yaw;

    int difference = heading_current-heading_desire;
    if(heading_current>heading_desire+BUFF_YAW && difference>180){
		turn_right();

#ifdef SIMULATOR
		/* simulated */
		sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'i');
#endif
    }
	else if(heading_current>heading_desire+BUFF_YAW && difference<180){
		turn_left();

#ifdef SIMULATOR
		/* simulated */
		sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'd');
#endif
    }
    else if(heading_current<heading_desire-BUFF_YAW && difference>180){
		turn_left();

#ifdef SIMULATOR
		/* simulated */
		sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'd');
#endif
    }
    else if(heading_current<heading_desire-BUFF_YAW && difference<180){
		turn_right();

#ifdef SIMULATOR
		/* simulated */
		sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'i');
#endif
    }
    else{
		hover();
		yawArrived = 1;
    }
    printOrientation();
}

void check_pitch_roll(int isHovering) {
    printf("!!!!!!!!!!!!!check pitch and roll: \n");
    int pitch_current=sensorCommand.pitch;
    int roll_current=sensorCommand.roll;
    int pitch_desire;
    int roll_desire;

    if(isHovering==0){
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

#ifdef SIMULATOR
		/* simulated */
		sensorCommand.pitch = readSensorTest(sensorCommand.pitch, 'd');
#endif
    }
    else if(pitch_current<pitch_desire-BUFF_PR){
		increase_right_decrease_left();

#ifdef SIMULATOR
		/* simulated */
		sensorCommand.pitch = readSensorTest(sensorCommand.pitch, 'i');
#endif
    }
    else{
		//great
    }

    //roll calc
    if(roll_current>roll_desire+BUFF_PR){
		increase_front_decrease_rear();

#ifdef SIMULATOR
		/* simulated */
		sensorCommand.roll = readSensorTest(sensorCommand.roll, 'd');
#endif
    }
    else if(roll_current<roll_desire-BUFF_PR){
		increase_rear_decrease_front();

#ifdef SIMULATOR
		/* simulated */
		sensorCommand.roll = readSensorTest(sensorCommand.roll, 'i');
#endif
    }
    else{
		//great
    }
    printOrientation();
}

#ifdef SIMULATOR
//(rand() % (max - min + 1) + min);
int readSensorTest(int currentSensor, char command){
   
    int i = (rand() % (6 - 0 + 1) + 0);  // between 5 and -5 degree variation

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
#endif

void printOrientation(void)
{
    printf("\n {pitch: %d roll: %d, yaw: %d height: %d distance left: %d}\n", 
		   sensorCommand.pitch, sensorCommand.roll,sensorCommand.yaw,
		   sensorCommand.height, distanceToTravel );
}


void updateDistanceToTravel(void){

    distanceTraveled = SPEED * duration;
    distanceToTravel = distanceToTravel - distanceTraveled ;
}


