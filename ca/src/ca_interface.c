<<<<<<< HEAD
<<<<<<< HEAD
/*
 * file:         ca_interface.c
 * brief:
 * author:       Amber Olsson, Yanling Jin
 * date:         2011-04-26
 * version:      0.1
 * history       2011-04-07 create the file
 * detail:
 */

=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
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
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#include <stdlib.h>
#include <stdio.h>

#ifdef ARDUINO
#include <WProgram.h>
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

//************************************************************
// ARDUINO
// All collision preperation goes here.
//************************************************************
int ca_init(void)
{
  return 1;
}


//************************************************************
// ARDUINO
// Collision is started here
//************************************************************
int ca_run(void)
{
  init();

  /* //init the serial output */
  // serial_init();
  // fdevopen(serial_putchar, serial_getchar);

  int i=0;
  while(i<1000)
    {
      direction_filter();
      i++;
    }

  return 1;

<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
}


#elif defined PC
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
//************************************************************
// PC
//  All movement preperation goes here.
//************************************************************
int ca_init(void)
{
  

  return 1;


}

//************************************************************
// PC
// Movement is started here
//************************************************************
int ca_run(void)
{

  int ir1=100;
  int ir2=100;
  int ir3=100;
  int ir4=100;
  int i=0;
  while (i<5){
    direction_filter(get_speed(),get_dir(),ir1, ir2, ir3, ir4);
    i++;
  }

  return 1;
}


#endif
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
