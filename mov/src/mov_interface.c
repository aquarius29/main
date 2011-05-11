/*
 * file:         mov_interface.c
 * brief:        Contains the interface of movement component
 * author:       Yanling Jin, Amber Olsson
 * date:         2011-05-03
 * version:      0.1
 * history       2011-04-17 create the file
 *
 * detail:       This file is the interface of the movement component\n
 */


#ifdef ARDUINO
#include "WProgram.h"
#elif defined PC
#include <stdlib.h>
#include <stdio.h>
#endif

#ifndef SIMULATOR
#include "proto_lib.h"
#endif 

#include "mov_interface.h"
#include <stdint.h>

#define SONAR_PIN 5
#define NO_MESSAGE 11

/* global variables*/
#ifdef SIMULATOR
FILE *file;
#endif

int distanceToTravel;
int distanceTraveled;

int yawArrived;
int heightArrived;

int start_time;
int duration;


struct nav navCommand;
struct sensor sensorCommand;
struct sensor oldSensorCommand;

struct sensor *pSensorC = &sensorCommand;
struct nav *p = &navCommand;

/*Motor Messages */
uint8_t msg1;
uint8_t msg2;
uint8_t msg3;
uint8_t msg4;
uint8_t msg5;
uint8_t msg6;
uint8_t msg7;
uint8_t msg8;
uint8_t message_counter;

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
    	clear_message_array();
	read_sensorCommand();

#ifdef DEBUG
	Serial.println("\n*************LOOOOOOOP**************\n");
#endif
	read_caCommand();

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
int mov_init(void) {

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
int mov_run(void) {

	read_sensorCommand();
	clear_message_array();

#ifdef DEBUG
	printf("\n \n*********************LOOOOOOOP***************************\n");
#endif
	read_caCommand();

	/*
	 * If the distanceToTravel is less than or equal to 0, we have probably arrived
	 * A new command would be read 
	 */
	if(distanceToTravel <= 0 && heightArrived == 1 && yawArrived == 1) {

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
	/*get the last sensor command*/
	oldSensorCommand = sensorCommand;
	/*get the duration*/
	duration = 10;

	send_dir_to_ca(2);
	
	write_array();
	return 0;
}
#endif



/*
 * write a message to an array
 */
void write_to_motor(unsigned char msg){
    
    switch(message_counter){
    case 1: msg1 = msg; break;
    case 2: msg2 = msg; break;
    case 3: msg3 = msg; break;
    case 4: msg4 = msg; break;
    case 5: msg5 = msg; break;
    case 6: msg6 = msg; break;
    case 7: msg7 = msg; break;
    case 8: msg8 = msg; break;
    }

    message_counter= message_counter + 1;
}

/*
 *Clear the message array to NO MESSAGE
 */
void clear_message_array(){

    message_counter = 1;
    msg1 = NO_MESSAGE;
    msg2 = NO_MESSAGE;
    msg3 = NO_MESSAGE;
    msg4 = NO_MESSAGE;
    msg5 = NO_MESSAGE;
    msg6 = NO_MESSAGE;
    msg7 = NO_MESSAGE;
    msg8 = NO_MESSAGE;
}

/*
 *Write a set of messages stored ina  struct to motor
 */
void write_array(){

#ifndef SIMULATOR
    //proto_write_motor2(msg1,msg2,msg3,msg4,msg5,msg6,msg7,msg8);
#endif
}

/*
 * write message to navigation
 */
void write_to_nav(void) {

#ifndef SIMULATOR
	//write to navigation
#endif
}


/*
 * read navigation Command
 */
void read_navCommand(void) {

#ifndef SIMULATOR
	//read navigation command
    p-> type = 0;
    p -> order = 0;
    p -> height = 0;
    p -> distance = 0;
    p -> yaw = 0;

	/* navCommand.type =0; */
	/* navCommand.order=0; */
	/* navCommand.height =10; */
	/* navCommand.distance=0; */
	/* navCommand.yaw=0; */
#endif
}


/*
 * read collision avoidance command
 */
void read_caCommand(void){

#ifndef SIMULATOR
	//read collision avoidance command
    //PROTOCOL READ FROM CA
    caDir = proto_read_yaw();
    	printf("@@@@@@@@@@@@@@@@\n @@@@@@@@@@@@@ %d  @@@@@@@@@@@@\n @@@@@@@@@@@@@",caDir);
#endif
}

void send_dir_to_ca(int i){

#ifndef SIMULATOR
	proto_write_direction(i);
#endif
}



void read_sensorCommand(void){

#ifndef SIMULATOR
    struct stab_gyroscope *stabCommand = (struct stab_gyroscope *)proto_stabReadAttitude();

    pSensorC -> pitch = stabCommand -> pitch;
    pSensorC -> roll = stabCommand -> roll;
    pSensorC -> yaw = stabCommand -> yaw;
    pSensorC -> height = (int) sonar_distance(SONAR_PIN);


	/* sensorCommand.pitch = stabCommand->pitch; */
	/* sensorCommand.roll = stabCommand->roll; */
	/* sensorCommand.yaw = stabCommand->yaw; */
	/* sensorCommand.height =(int)sonar_distance(SONAR_PIN); */

	/* printf("@@@@@@@@@@@@@@@@\n @@@@@@@@@@@@@ %d  @@@@@@@@@@@@\n @@@@@@@@@@@@@",sensorCommand.pitch); */
	/* printf("@@@@@@@@@@@@@@@@\n @@@@@@@@@@@@@ %d  @@@@@@@@@@@@\n @@@@@@@@@@@@@",sensorCommand.roll); */
	/* printf("@@@@@@@@@@@@@@@@\n @@@@@@@@@@@@@ %d  @@@@@@@@@@@@\n @@@@@@@@@@@@@",sensorCommand.yaw); */
	/* printf("@@@@@@@@@@@@@@@@\n @@@@@@@@@@@@@ %d  @@@@@@@@@@@@\n @@@@@@@@@@@@@",sensorCommand.height); */
#endif
}






