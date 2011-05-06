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


#ifdef ARDUINO
#include "WProgram.h"
#elif defined PC
#include <stdlib.h>
#include <stdio.h>
#endif

#include "mov_interface.h"

#ifndef SIMULATOR
//#include "proto_mov_motor.h"
#endif

/* global variables*/

#ifdef SIMULATOR
FILE *file;
#endif

int distanceToTravel;
int distanceTraveled;

int yawArrived;
int heightArrived;

int changingAltitude;
int changingHeading;

static int start_time;
int duration;

struct nav navCommand;
struct sensor sensorCommand;
struct sensor oldSensorCommand;


int caDir=-1;


#ifdef ARDUINO
/*
 * ARDUINO
 * all the movement preparation
 */
int mov_init()
{
	/*init the serial print*/
	Serial.begin(9600);

	/*init the movement control varaibles*/
	heightArrived = 1;
	yawArrived = 1;
	distanceToTravel = 0;
	duration=0;

	return 0;
}

/*
 * ARDUINO 
 * running the movement code
 */
int mov_run()
{

#ifdef DEBUG
	Serial.println("\n*********************LOOOOOOOP***************************\n");
#endif

	/*calculate the duration*/
	if(start_time != 0){
		duration = millis() - start_time;
	}
  
	/*
	 * If the distanceToTravel is less than or equal to 0, we have probably arrived
	 * A new command would be read 
	 */
	if(distanceToTravel <= 0 && heightArrived == 1 && yawArrived == 1){
		/*reset control variables*/
		heightArrived = 0;
		yawArrived = 0;
		distanceToTravel = 0;
		/*read new command*/
		read_navCommand();
		distanceToTravel=navCommand.distance;
	}

	/*flight control*/	
	command_logic();

	/*get the last sensor command*/
	oldSensorCommand = sensorCommand;

	/*reset the start time*/
	start_time = millis();
  
	return 0;
}
#endif





#ifdef PC
/*
 * PC
 * all the movement preparations
 */
int mov_init(void)
{
	/*open the file which contains the simulated controls*/
#ifdef SIMULATOR
    file = fopen("input.txt", "r");
    srand(time(NULL));
#endif

	/*init the movement control varaibles*/
    heightArrived = 1;
    yawArrived = 1;
    distanceToTravel = 0;

    duration=0;

	return 0;
}


/*
 * PC
 * running the movement code
 */
int mov_run(void){
	printf("\n \n*********************LOOOOOOOP***************************\n");
	//read the ca command
	read_caCommand();

	if(caDir<0){
		/*If the distanceToTravel is less than or equal to 0, we have probably arrived**/
		if(distanceToTravel <= 0 && heightArrived == 1 && yawArrived == 1){

			/*reset control variables*/
			heightArrived = 0;
			yawArrived = 0;
			distanceToTravel = 0;

			/*read a new command*/
#ifdef SIMULATOR
			if (read_command()== 0) {  
				fclose(file);
				printf("**end of the file**\n");
				return 1;
			}
			else{
				distanceToTravel = navCommand.distance;
			}
#else
			read_navCommand();
			distanceToTravel=navCommand.distance;
#endif
		}
	
		/*flight control*/
		command_logic();

		/*get the duration*/
		duration = 10;

		/*get the last sensor command*/
		oldSensorCommand = sensorCommand;
	}
	else {
	    doCa();	    /*do ca here */
		command_logic();
		/*get the last sensor command*/
		oldSensorCommand = sensorCommand;
	}
	return 0;
}
#endif


/*
 *
 */
void doCa(void){
    yawArrived = 0;
    distanceToTravel = 0;
    if(caDir == 0){ /*HOVER.. no yaw*/	  
	    navCommand.yaw = sensorCommand.yaw;
    }
    else if(caDir == 1){ /*FORWARDS ..add no sensor data */
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

    caDir = -1;
    navCommand.order = 1;
    distanceToTravel = 10;
}


/*
 * send message to motor
 */
void write_to_motor(unsigned char msg){
#ifndef SIMULATOR
	//	write_motor(msg);
#endif

}



void write_to_nav(void) {
#ifndef SIMULATOR
	//write to navigation
#endif
}


void read_navCommand(void) {
#ifndef SIMULATOR
struct nav *p = &navCommand;
	//read navigation command
	p->type =0;
	p->order=0;
	p->height =10;
	p->distance=0;
	p->yaw=0;
#endif
}


void read_caCommand(void){
#ifndef SIMULATOR
	//read collision avoidance command
    //PROTOCOL READ FROM CA
    caDir = 0;
#endif
}
