/*****************************************************************************
 * Product: mov_Interface.c
 * Version: 0.1
 * Created: April 7, 2011
 * History:
 *          
 *
 *
 * Movement/CA Group
 *****************************************************************************/


#include "mov_interface.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef PC
#include <time.h>
#endif



#ifdef ARDUINO
//************************************************************
// ARDUINO
// All movement preperation goes here.
//************************************************************
int mov_init()
{
	//start magnetometer
	start_time=0;
	duration=0;

	return 1;
}


//************************************************************
// ARDUINO
// Movement is started here
//************************************************************
int mov_run()
{
	if(start_time != 0){
		duration = millis() - start_time;
}
  
	//stabilize based on last movement 
  
	//move

	start_time = millis();
  
	return 1;

}
#endif



#ifdef PC
//************************************************************
// PC
//  All movement preperation goes here.
//************************************************************
int mov_init()
{
	start_time=0;
	duration=0;

	return 1;

}

//************************************************************
// PC
// Movement is started here
//************************************************************
int mov_run()
{
	if(start_time != 0){
		duration = clock() / (CLOCKS_PER_SEC / 1000) - start_time;
	}

	//stabilize based on last movement 
  
	//move

	start_time =  clock() / (CLOCKS_PER_SEC / 1000);
  
	printf("%d", start_time);

	return 1;
}
#endif




void write_to_motor(float f1, float f2, float f3, float f4) {

	printf("write to motor here");
	unsigned char message = 0;
    
    message = 0xFF;
    /* send message to motor here */
	// write_motor(message);
}


void write_to_nav() {
	//write to navigation
}


void read_navCommand() {
	//read navigation command
}


void write_to_collision() {
	//write to collision
}
