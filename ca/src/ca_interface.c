/*
 * file:         ca_interface.c
 * brief:
 * author:       Amber Olsson, Yanling Jin
 * date:         2011-04-26
 * version:      0.1
 * history       2011-04-07 create the file
 * detail:
 */

#include <stdlib.h>
#include <stdio.h>

#ifdef ARDUINO
#include <WProgram.h>
#endif

#include "ca_interface.h"
#include "proto_lib.h"


#ifdef ARDUINO
/*
 * ARDUINO
 * All collision preperation goes here.
 */
int ca_init(void)
{
	/* to init the arduino lib */
	init();

	/* to init the print serial */
	Serial.begin(9600);
	return 0;
}


/*
 * ARDUINO
 * Collision is started here
 */
int ca_run(void)
{

	write_to_move(direction_filter());

	return 0;
}


#elif defined PC
/*
 * PC
 * All collision preperation goes here.
 */
int ca_init(void)
{

	return 0;
}


/*
 * PC
 * Collision is started here
 */
int ca_run(void)
{
	/* fake data here*/
	write_to_move(direction_filter(120,120,50,120, 120,200, 40, 120));
	return 0;
}

#endif



/*
 * return the current flying direction
 * read from movement
 */
int get_dir(void)
{
	
	int dir = proto_read_direction();
	//	int dir=2;
	return  dir;
}


/*
 * write the direction intructions
 * send to the movement
 */
void write_to_move(int direction){

	/* 0 hover 1 front 2 back 3 left 4 right  REST free to go */
	proto_write_yaw(direction);
}
