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


#include "mov_interface.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef SIMULATOR
//#include "proto_mov_motor.h"
#endif




int caDir=-1;

#ifdef ARDUINO
//************************************************************
// ARDUINO
// All movement preperation goes here.
//************************************************************
int mov_init()
{
	Serial.init(9600);

    heightArrived = 1;
    yawArrived = 1;
    distanceToTravel = 0;
	duration=0;

	return 0;
}


//************************************************************
// ARDUINO
// Movement is started here
//************************************************************
int mov_run()
{
	Serial.println("\n*********************LOOOOOOOP***************************\n");

	if(start_time != 0){
		duration = millis() - start_time;
	}
  
	/*If the distanceToTravel is less than or equal to 0, we have probably arrived*/
	if(distanceToTravel <= 0 && heightArrived == 1 && yawArrived == 1){
		heightArrived = 0;
		yawArrived = 0;
		distanceToTravel = 0;

		read_navCommand();
		distanceToTravel=navCommand.distance;
	}
	
	command_logic();

	oldSensorCommand = sensorCommand;
	start_time = millis();
  
	return 1;

}
#endif



#ifdef PC
/*
 *
 */
int mov_init(void)
{
#ifdef SIMULATOR
    file = fopen("input.txt", "r");
#endif

    heightArrived = 1;
    yawArrived = 1;
    distanceToTravel = 0;
    srand(time(NULL));
    duration=0;

	return 0;

}


/*
 *
 */
int mov_run(void){
	printf("\n \n*********************LOOOOOOOP***************************\n");
	read_caCommand();

	/*If the distanceToTravel is less than or equal to 0, we have probably arrived**/

	if(caDir<0){

	if(distanceToTravel <= 0 && heightArrived == 1 && yawArrived == 1){
		heightArrived = 0;
		yawArrived = 0;
		distanceToTravel = 0;
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
	
	command_logic();
	duration = 10;
	oldSensorCommand = sensorCommand;
}

	else{
	    doCa();	    /*do ca here */
	}
	return 0;
}
#endif

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
    yaw = 0;
#endif
}
