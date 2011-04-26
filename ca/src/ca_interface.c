/*****************************************************************************
 * Product: movementInterface.c
 * Version: 0.1
 * Created: April 7, 2011
 * History:
 *          
 *
 * Movement/CA Group
 *****************************************************************************/
#include "ca_interface.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef ARDUINO
#include <WProgram.h>

/*
 * ARDUINO
 * All collision preperation goes here.
 */
int ca_init(void)
{
	//to init the print serial
	Serial.begin(9600);

	//to init the arduino lib
	init();
	return 1;
}


/*
 * ARDUINO
 * Collision is started here
 */
int ca_run(void)
{

	write_to_move(direction_filter());

	return 1;

}


#elif defined PC
/*
 * PC
 * All collision preperation goes here.
 */
int ca_init(void)
{

	return 1;
}


/*
 * PC
 * Collision is started here
 */
int ca_run(void)
{
	//fake data here
	write_to_move(direction_filter(100, 100, 100, 100));

	return 1;
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

	//	write(direction)

}
