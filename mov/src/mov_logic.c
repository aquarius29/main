/*
 * file:         mov_logic.c
 * brief:        Contains the logic for calculate movement
 * author:       
 * date:         2011-05-03
 * version:      0.1
 * history      
 *
 * detail:
 */
#ifdef PC
#include <stdlib.h>
#include <stdio.h>
#endif

#include "mov_interface.h"

#define BUFF_YAW 1
#define BUFF_DISTSNCE 1
#define BUFF_PR 1
#define SPEED 100
#define DEFAULT_CA_DISTANCE 100


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
 * This function init the movement of the drone
 * It checks the command from collision avoidance first
 * And then move according to the movement orders
 */
void command_logic(void) {
	doCa();
#ifdef DEBUG
    printOrientation();
#endif
    char order = navCommand.order;  
	/*
	 *If order is set to move, 
	 *we will attempt to control height, heading, and movement
	 */
	if (order == '1') {
		updateDistanceToTravel();
		check_heading();
		check_pitch_roll(1);
		check_changingAltitude();
		check_height();
	
    }
	/*If order is set land, we attempt to go into hover mode and then land */
	else if(order == '2') {
		distanceToTravel = 0;
		check_pitch_roll(0);
		check_heading();
		check_changingAltitude();
		if (sensorCommand.height <= 0){
			heightArrived = 1;
			stop_motors();
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
    /*
	 *If Order is Hover, we will not attempt to move a distance.
	 * Our pitch and roll is set to hover mode 
	 */
    else { 
		distanceToTravel = 0;
		check_heading();
		check_pitch_roll(0);
		check_changingAltitude();
		check_height();
	} 

}

/*
 * Check the collision avoidance
 * Change the drone's heading according to the instruction
 * Set the default distance to 100
 */
void doCa(void){
	extern int caDir;
	if(caDir>0){
		navCommand.order = 1;
		yawArrived = 0;
		distanceToTravel = DEFAULT_CA_DISTANCE;

		if(caDir == 1){ /*FORWARDS ..add no sensor data */
			navCommand.yaw = sensorCommand.yaw;
		}
		else if(caDir == 2){ /* BACKWARDS .. add 180 degrees to sensor data */
			navCommand.yaw = sensorCommand.yaw + 180;
		}
		else if(caDir == 3){ /*GO LEFT... add -90 degrees to sensor data  */
			navCommand.yaw = sensorCommand.yaw - 90;
		}
		else if(caDir == 4){ /*GO RIGHT ... add 90 degrees to sensor data */
			navCommand.yaw = sensorCommand.yaw + 90;
		}
	}
	else if(caDir==0){
		navCommand.order = 0;
		yawArrived = 0;
		distanceToTravel =0;
	}
    caDir = -1;
}

/*
 * Check if the Altitude is changing
 * return 1 as changing, 0 as not changing
 */
void check_changingAltitude(void){
    if(oldSensorCommand.height != sensorCommand.height + BUFF_DISTSNCE) {
		changingAltitude = 1;
	}
    else {
		changingAltitude = 0;
	}
}


/*
 * Check the drone height,
 * Adjust the motor according to the drone's height
 */
void check_height(void)
{
#ifdef DEBUG
    printf("!!!!!!!!!!!!!check height: \n");
#endif
    int height_desire =navCommand.height;
    int height_current =sensorCommand.height;

	/*higher than it supposed to be, decrease all motors*/
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

	/*lower than it supposed to be, increase all motors*/
    else if(height_current<height_desire-BUFF_DISTSNCE){
		if(changingAltitude == 1) {	
			hover();
			increase_all();
		}		
#ifdef SIMULATOR
		/* simulated */		
		sensorCommand.height = readSensorTest(sensorCommand.height, 'i');
#endif

    }
	/*it's under the perfect height*/
    else{
		hover();
		heightArrived = 1;
    }
#ifdef DEBUG
    printOrientation();
#endif
}



/*
 * Check the drone's heading
 * Adjust the drone's motor according to that
 */
void check_heading(void)
{
#ifdef DEBUG
    printf("!!!!!!!!!!!!!check heading: \n");
#endif

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
#ifdef DEBUG
    printOrientation();
#endif
}

/*
 * 
 */
void check_pitch_roll(int isHovering) {
#ifdef DEBUG
    printf("!!!!!!!!!!!!!check pitch and roll: \n");
#endif
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
#ifdef DEBUG
    printOrientation();
#endif
}


/*
 * calculate the distance left
 */
void updateDistanceToTravel(void){
    distanceTraveled = SPEED * duration;
    distanceToTravel = distanceToTravel - distanceTraveled ;
}


/*
 * print the drone's current attitude,
 * DEBUG only
 */
#ifdef DEBUG
void printOrientation(void)
{
    printf("\n {pitch: %d roll: %d, yaw: %d height: %d distance left: %d}\n", 
		   sensorCommand.pitch, sensorCommand.roll,sensorCommand.yaw,
		   sensorCommand.height, distanceToTravel );
}
#endif
