/*
 * file:         mov_logic.c
 * brief:        Contains the logic for calculate movement
 * author:       
 * date:         2011-05-10
 * version:      0.1
 * history      
 *
 * detail:
 */
#ifdef PC
#include <stdlib.h>
#include <stdio.h>
#endif

#ifdef DEBUG
#define DEBUG_PRINT(s)        printf(s)
#else
#define DEBUG_PRINT(s)
#endif


#include "mov_interface.h"

#define BUFF_YAW 1
#define BUFF_DISTSNCE 1
#define BUFF_PR 1
#define SPEED 100
#define DEFAULT_CA_DISTANCE 100

/*For Sending to Simulation */
#define INCREASING 1
#define DECREASING 2

extern int distanceToTravel;
extern int distanceTraveled;

extern int yawArrived;
extern int heightArrived;

int changingAltitude;
int changingHeading;

extern int duration;

extern struct nav navCommand;
extern struct nav *p;
extern struct sensor sensorCommand;
extern struct sensor oldSensorCommand;


/*
 * This function init the movement of the drone
 * It checks the command from collision avoidance first
 * And then move according to the movement orders
 */
void command_logic(void) {

	doCa();

    printOrientation();
	convertCommand();

    char order = navCommand.order;  

	if (order == '1') {
		moveCommand();
    }else if(order == '2') {
		landCommand();
    }else { 
		hoverCommand();
	} 
}



void convertCommand(void){
	if(navCommand.type=='0'){
		p->height=navCommand.height+sensorCommand.height;
		p->yaw=navCommand.yaw+sensorCommand.yaw;
	}
}

/*
 *If Order is Hover, we will not attempt to move a distance.
 * Our pitch and roll is set to hover mode 
 */
void hoverCommand(void) {
	distanceToTravel = 0;
	check_heading();
	check_pitch_roll(0);
	check_changingAltitude();
	check_height();
}

/*
 *If order is set to move, 
 *we will attempt to control height, heading, and movement
 */
void moveCommand (void){
	if(yawArrived!=1){
		check_heading();
		check_pitch_roll(0);
		check_changingAltitude();
		check_height();
	}
	else{
		updateDistanceToTravel();
		check_pitch_roll(1);
		check_changingAltitude();
		check_height();
	}
}

/*
 *If order is set land, 
 *we attempt to go into hover mode and then land 
 */
void landCommand(void){
	navCommand.height=0;
	hoverCommand();
	if (sensorCommand.height <= 0){
		heightArrived = 1;
		stop_motors();
	}
	/*Order is invalid. Land! */
	else { 
		land(); 
		sensorCommand.height = do_sensor_simulation(sensorCommand.height, DECREASING);
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
    DEBUG_PRINT("!!!!!!!!!!!!!check height: \n");
    int height_desire =navCommand.height;
    int height_current =sensorCommand.height;

	/*higher than it supposed to be, decrease all motors*/
    if(height_current > height_desire+BUFF_DISTSNCE){	
		if(changingAltitude == 1) {
		    hover();	
		    decrease_all();
		}
		sensorCommand.height = do_sensor_simulation(sensorCommand.height, DECREASING);
    }

	/*lower than it supposed to be, increase all motors*/
    else if(height_current<height_desire-BUFF_DISTSNCE){
		if(changingAltitude == 1) {	
			hover();
			increase_all();
		}			
		sensorCommand.height = do_sensor_simulation(sensorCommand.height, INCREASING);
    }
	/*it's under the perfect height*/
    else{
		hover();
		heightArrived = 1;
    }
    printOrientation();
}



/*
 * Check the drone's heading
 * Adjust the drone's motor according to that
 */
void check_heading(void)
{
   DEBUG_PRINT ("!!!!!!!!!!!!!check heading: \n");

    int heading_desire=navCommand.yaw;
    int heading_current=sensorCommand.yaw;
    int difference = heading_current-heading_desire;

    if(heading_current>heading_desire+BUFF_YAW && difference>180){
		turn_right();
		sensorCommand.yaw = do_sensor_simulation(sensorCommand.yaw, INCREASING);
    }
	else if(heading_current>heading_desire+BUFF_YAW && difference<180){
		turn_left();
		sensorCommand.yaw = do_sensor_simulation(sensorCommand.yaw, DECREASING);
    }
    else if(heading_current<heading_desire-BUFF_YAW && difference>180){
		turn_left();
		sensorCommand.yaw = do_sensor_simulation(sensorCommand.yaw, DECREASING);
    }
    else if(heading_current<heading_desire-BUFF_YAW && difference<180){
		turn_right();
		sensorCommand.yaw = do_sensor_simulation(sensorCommand.yaw, INCREASING);
    }
    else{
		hover();
		yawArrived = 1;
    }
    printOrientation();
}

/*
 * 
 */
void check_pitch_roll(int isHovering) {
    DEBUG_PRINT("!!!!!!!!!!!!!check pitch and roll: \n");
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
		
		/* simulated */
		sensorCommand.pitch = do_sensor_simulation(sensorCommand.pitch, DECREASING);
    }
    else if(pitch_current<pitch_desire-BUFF_PR){
		increase_right_decrease_left();

		/* simulated */
		sensorCommand.pitch = do_sensor_simulation(sensorCommand.pitch, INCREASING);
    }
    else{
		//great
    }

    //roll calc
    if(roll_current>roll_desire+BUFF_PR){
		increase_front_decrease_rear();

		/* simulated */
		sensorCommand.roll = do_sensor_simulation(sensorCommand.roll, DECREASING);
    }
    else if(roll_current<roll_desire-BUFF_PR){
		increase_rear_decrease_front();


		/* simulated */
		sensorCommand.roll = do_sensor_simulation(sensorCommand.roll, INCREASING);
    }
    else{
		//great
    }
    printOrientation();
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
void printOrientation(void)
{
#ifdef DEBUG
   printf("\n {pitch: %d roll: %d, yaw: %d height: %d distance left: %d}\n", 
		   sensorCommand.pitch, sensorCommand.roll,sensorCommand.yaw,
		   sensorCommand.height, distanceToTravel );
#endif
}
