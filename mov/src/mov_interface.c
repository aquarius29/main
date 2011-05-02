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
    distanceToTravel = 0;
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

    /* //duration since last time we ran */
    /* 	if(start_time != 0){ */
    /* 	    duration =  clock() / (CLOCKS_PER_SEC / 1000) - start_time; */
    /* 	    updateDistanceToTravel(); */
    /* 	    printf("duration: %d", duration); */
    /* 	    printf("\n \n \n distance to travel  %d", distanceToTravel); */
    /* 	} */
    /* 	else */
    /* 	    { */
    /* 		duration = 0; */
    /* 	    } */

	/*If the distanceToTravel is less than or equal to 0, we have probably arrived**/
	if(distanceToTravel <= 0 && heightArrived == 1 && yawArrived == 1)
	    {
		int x = read_command();
		if (x == 0) {                                               /***check if there is a valid command***/
		    printf("**end of the file**\n");
		    return 1;
    		}
	    }
	
	printOrientation();
	
	command_logic();

	//stabilize based on last movement 
	stabL();

	/* start_time =  clock() / (CLOCKS_PER_SEC / 1000); */
	duration = 10;
	    return 0;
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
