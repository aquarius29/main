/*
 * file:         mov_interface.c
 * brief:
 * author:       
 * date:         2011-05-03
 * version:      0.1
 * history      
 *
 * detail:
 */



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

int changingAltitude;
int changingHeading;

extern int duration;

extern struct nav navCommand;
extern struct sensor sensorCommand;
extern struct sensor oldSensorCommand;


/*
 * 
 *
 */
void command_logic(void) {
    printOrientation();
    char order = navCommand.order;  
    /*If Order is Hover, we will not attempt to move a distance. Our pitch and roll is set to hover mode */
    if (order == '0') { 
		distanceToTravel = 0;
		check_heading();
		check_pitch_roll(0);
		check_changingAltitude();
		check_height();
		/*If order is set to move, we will attempt to control height, heading, and movement */
    } else if (order == '1') {
		updateDistanceToTravel();
		check_heading();
		check_pitch_roll(1);
		check_changingAltitude();
		check_height();
		/*If order is set land, we attempt to go into hover mode and then land */
    } else if(order == '2') {
		distanceToTravel = 0;
		check_pitch_roll(0);
		check_heading();
		check_changingAltitude();
		if (sensorCommand.height <= 0){
			heightArrived = 1;
		}
		/*Order is invalid. Land! */
		else { 
			land(); 
 
#ifdef SIMULATOR
			/* simulated - decrease the sensed height */
			sensorCommand.height = readSensorTest(sensorCommand.height, 'd');
#endif
		} 

    }
	else {
		stop_motors();
	}
}

/*
 * Check if we are the point where we are changing altitude
 */
void check_changingAltitude(void){
    if(oldSensorCommand.height != sensorCommand.height + BUFF_DISTSNCE)
		changingAltitude = 1;
    else
		changingAltitude = 0;

}


/*
 * Check the drone height and make the proper command to motors
 */
void check_height(void){

    //printf("!!!!!!!!!!!!!check height: \n");
    int height_desire =navCommand.height;
    int height_current =sensorCommand.height;

    /*If we need to DECREASE the height */
    if(height_current > height_desire+BUFF_DISTSNCE){
	/*If we are a level where our altitude is changing */
		if(changingAltitude == 1) {
		    hover();	
		    decrease_all();
		}

#ifdef SIMULATOR
		/* simulated - decrease the sensed height */
		sensorCommand.height = readSensorTest(sensorCommand.height, 'd');
#endif
    }
    /*If we need to INCREASE height */
    else if(height_current<height_desire-BUFF_DISTSNCE){
	/*if we are a level where our altitude is changing */
		if(changingAltitude == 1) {	
			hover();
			increase_all();
		}
		
#ifdef SIMULATOR
		/* simulated - increase the sensed height */		
		sensorCommand.height = readSensorTest(sensorCommand.height, 'i');
#endif

    }
    else{
	/*Height desired has been reached */
		hover();
		heightArrived = 1;
    }
    printOrientation();
}



/*
 * check the drone heading and make the proper command to motors
 */
void check_heading(void)
{
    printf("!!!!!!!!!!!!!check heading: \n");
    int heading_desire=navCommand.yaw;
    int heading_current=sensorCommand.yaw;

 
    int difference = heading_current-heading_desire;
    /*The difference between the current and desired explains how to turn efficiently */
    if(heading_current>heading_desire+BUFF_YAW && difference>180){
		turn_right();

#ifdef SIMULATOR
		/* simulated - increase the yaw sensor*/
		sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'i');
#endif
    }
	else if(heading_current>heading_desire+BUFF_YAW && difference<180){
		turn_left();

#ifdef SIMULATOR
		/* simulated - decrease the yaw sensor*/
		sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'd');
#endif
    }
    else if(heading_current<heading_desire-BUFF_YAW && difference>180){
		turn_left();

#ifdef SIMULATOR
		/* simulated - decrease the yaw sensor */
		sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'd');
#endif
    }
    else if(heading_current<heading_desire-BUFF_YAW && difference<180){
		turn_right();

#ifdef SIMULATOR
		/* simulated - increase the yaw sensor*/
		sensorCommand.yaw = readSensorTest(sensorCommand.yaw, 'i');
#endif
    }
    else{ /*In any other case, the heading is ok, so hover to return our motors to all the same speed */
		hover();
		yawArrived = 1;
    }
    printOrientation();
}

/*
 * check the drone pitch and roll  and make the proper command to motors
 */
void check_pitch_roll(int isHovering) {
    //printf("!!!!!!!!!!!!!check pitch and roll: \n");
    int pitch_current=sensorCommand.pitch;
    int roll_current=sensorCommand.roll;
    int pitch_desire;
    int roll_desire;

    /* The desired pitch and roll depends on if we want to hover or move forwards*/
    if(isHovering==0){
		pitch_desire=0;
		roll_desire=0;
    }
    else{
		pitch_desire=20;
		roll_desire=20;
    }
    /*If we need to decrease the pitch */
    if(pitch_current>pitch_desire+BUFF_PR){
	increase_left_decrease_right();

#ifdef SIMULATOR
		/* simulated - decrease the sensed pitch */
		sensorCommand.pitch = readSensorTest(sensorCommand.pitch, 'd');
#endif
    }
    /*If we need to increase the pitch */
    else if(pitch_current<pitch_desire-BUFF_PR){
		increase_right_decrease_left();

#ifdef SIMULATOR
		/* simulated - increase the sensed pitch*/
		sensorCommand.pitch = readSensorTest(sensorCommand.pitch, 'i');
#endif
    }
    else{
	/*If we are at the desired pitch, nothing special happens. */
    }
    /*If we need to decrease the roll */
    if(roll_current>roll_desire+BUFF_PR){
		increase_front_decrease_rear();

#ifdef SIMULATOR
		/* simulated -decrease the sensed roll*/
		sensorCommand.roll = readSensorTest(sensorCommand.roll, 'd');
#endif
    }
    /*If we need to increase the roll */
    else if(roll_current<roll_desire-BUFF_PR){
		increase_rear_decrease_front();

#ifdef SIMULATOR
		/* simulated - increase the sensed roll*/
		sensorCommand.roll = readSensorTest(sensorCommand.roll, 'i');
#endif
    }
    else{
	/*If we are at the desired  roll, nothing special happens. */
    }
    printOrientation();
}


/*
 *  Update the distance we need to move
 */
void updateDistanceToTravel(void){

    distanceTraveled = SPEED * duration;
    distanceToTravel = distanceToTravel - distanceTraveled ;
}


/*
 * Do a print out of the current sensor readings 
 */
void printOrientation(void){

    printf("\n {pitch: %d roll: %d, yaw: %d height: %d distance left: %d}\n", 
		   sensorCommand.pitch, sensorCommand.roll,sensorCommand.yaw,
		   sensorCommand.height, distanceToTravel );
}
