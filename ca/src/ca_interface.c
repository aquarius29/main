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
//#include "proto_ca.h"


#ifdef ARDUINO
/*
 * ARDUINO
 * All collision preperation goes here.
 */
int ca_init(void)
{
	/* to init the print serial */
	Serial.begin(9600);

	/* to init the arduino lib */
	init();

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
	write_to_move(direction_filter(100,100,100,100));
	return 0;
}

#endif


/*
 * return the flying speed.
 */
int get_speed(void)
{
	//	int speed = read_speed();
	int speed=1;
	return  speed;
}


/*
 * return the flying direction.
 */
int get_dir(void)
{
	//	int dir = read_direction();
	int dir=1;
	return  dir;
}


/*
 * send to the movement
 */
void write_to_move(int direction){

	/* 0 hover 1 front 2 back 3 left 4 right REST free to go */

	//	write(direction)
}
