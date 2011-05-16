/*!
 * @file:         mov_interface.c
 * @brief:        Contains the interface of movement component
 * @author:       Yanling Jin, Amber Olsson
 * @date:         2011-05-03
 * @version:      0.1
 * @history       2011-04-17 create the file
 *
 * @detail:       This file is the interface of the movement component\n
 */


#ifdef ARDUINO
#include "WProgram.h"
#elif defined PC
#include <stdlib.h>
#include <stdio.h>
#endif

#ifndef TEST
#include "proto_lib.h"
#endif 

#include "mov_interface.h"
#include <stdint.h>

#define SONAR_PIN 5

/* global variables*/
#ifdef SIMULATOR
FILE *file;
#endif

int16_t distanceToTravel;
int16_t  distanceTraveled;

uint8_t yawArrived;
uint8_t heightArrived;

uint32_t start_time;
double duration;


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

int8_t caDir=5;

uint8_t count=0;

#ifdef ARDUINO
/*
 * ARDUINO
 * all the movement preparation
 */
int16_t mov_init()
{
	init();
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
int16_t mov_run()
{
	clear_message_array();
	read_sensorCommand();

#ifdef DEBUG
	Serial.println("\n*************LOOOOOOOP**************\n");
#endif
	read_caCommand();

	/*calculate the duration*/
	if(start_time != 0){
		duration = (millis() - start_time)/1000;
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

	write_array();
	return 0;
}
#endif


#ifdef PC
/*
 * PC
 * all the movement preparations
 */
int16_t mov_init(void) {

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
int16_t mov_run(void) {

	read_sensorCommand();
	clear_message_array();
	
#ifdef DEBUG
	printf("\n*********************LOOOOOOOP***************************\n");
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
#ifdef DEBUG
			printf("**end of the file**\n");
#endif
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
	
	write_array();
	return 0;
}
#endif


void write_to_nav_ca(int8_t direction) {
#ifndef TEST
	//call this method when there's a collision
	//1 collision 0 no collision
#endif
}


/*
 *Write a set of messages stored ina  struct to motor
 *send the structure to motor
 */
void write_array(){
#ifndef TEST
    proto_write_motor2(msg1,msg2,msg3,msg4,msg5,msg6,msg7,msg8);
	#ifdef DEBUG
	printf("@@@@@@@@@@@@@@SEND MESSAGE@@@@@@@@@@@@@@@\n");
	print_uint8_t_to_Binary(msg1);
	print_uint8_t_to_Binary(msg2);
	print_uint8_t_to_Binary(msg3);
	print_uint8_t_to_Binary(msg4);
	print_uint8_t_to_Binary(msg5);
	print_uint8_t_to_Binary(msg6);
	print_uint8_t_to_Binary(msg7);
	print_uint8_t_to_Binary(msg8);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	#endif
#endif
}

/*
 * write message to navigation direction
 */
void write_to_dir(void) {
#ifndef TEST
	//write to navigation 
	//uint16_t
#endif
}

void write_to_nav_comfirm(uint8_t i) {
#ifndef TEST
	//1 done nav //0 default
#endif
}

/*
 * read navigation Command
 */
void read_navCommand(void) {
#ifndef TEST
	//read navigation command
	if(count ==0){
		p-> type = 0;
		p -> order = 0;
		p -> height = 20;
		p -> distance = 0;
		p -> yaw = 0;
		count =1;
	}
	else{
		p-> type = 0;
		p -> order = 0;
		p -> height = 0;
		p -> distance = 0;
		p -> yaw = 0;
	}
	//#ifdef DEBUG
	printf("@@@@@@TO DO :{type: %d order: %d, height: %d distance: %d yaw: %d}@@@@@@\n", 
		   navCommand.type, navCommand.order,navCommand.height,
		   navCommand.distance, navCommand.yaw);
	//#endif
#endif
}


/*
 * read collision avoidance command
 */
void read_caCommand(void){
#ifndef TEST
    caDir = proto_read_yaw();
#endif
}

void send_dir_to_ca(uint8_t dir){
#ifndef TEST
	proto_write_direction(dir);
#endif
}


void read_sensorCommand(void){

#ifndef TEST
    struct  stab_attitude *stabCommand = (struct  stab_attitude *)proto_stabReadAttitude();
    pSensorC -> pitch = stabCommand -> pitch;
    pSensorC -> roll = stabCommand -> roll;
    pSensorC -> yaw = stabCommand -> yaw;
    pSensorC -> height = (uint16_t) sonar_distance(SONAR_PIN);
	#ifdef DEBUG
#ifdef PC
	printf("@@@@@@@ PITCH  @@@@@@@@@@@@@@@@@ %d  @@@@@@@@@@@@@@@@@@@@\n",sensorCommand.pitch);
	printf("@@@@@@@ ROLL   @@@@@@@@@@@@@@@@@ %d  @@@@@@@@@@@@@@@@@@@@\n",sensorCommand.roll);
	printf("@@@@@@@ YAW    @@@@@@@@@@@@@@@@@ %d  @@@@@@@@@@@@@@@@@@@@\n",sensorCommand.yaw);
	printf("@@@@@@@ HEIGHT @@@@@@@@@@@@@@@@@ %d  @@@@@@@@@@@@@@@@@@@@\n",sensorCommand.height);
#elif defined ARDUINO
	Serial.println("@@@@@@@@@@SENSOECOMMAND  PITCH@@@@@@@@@");
	Serial.print(sensorCommand.pitch);
	Serial.println("@@@@@@@@@@SENSOECOMMAND  ROLL@@@@@@@@@");
	Serial.print(sensorCommand.roll);
	Serial.println("@@@@@@@@@@SENSOECOMMAND  YAW@@@@@@@@@");
	Serial.println(sensorCommand.yaw);
	Serial.println("@@@@@@@@@@SENSOECOMMAND  HEIGHT@@@@@@@@@");
	Serial.println(sensorCommand.height);
	#endif
#endif
#endif
}


