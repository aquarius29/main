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
/*
 *
 */
int mov_init()
{
    heightArrived = 1;
    yawArrived = 1;
    distanceToTravel = 0;
    duration=0;

	return 1;
}


/*
 *
 */
int mov_run(){

    printf("dis %d Height %d Yaw %d", distanceToTravel, heightArrived, yawArrived);
 
	/*If the distanceToTravel is less than or equal to 0, we have probably arrived**/
	if(distanceToTravel <= 0 && heightArrived == 1 && yawArrived == 1)
	    {
		 heightArrived = 0;
		 yawArrived = 0;
		 distanceToTravel = 0;
			if (read_command()== 0) {  /***check if there is a valid command***/
				printf("**end of the file**\n");
				return 1;
			}
			else
			    	distanceToTravel = navCommand.distance;
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




void write_to_motor(void){


}
void write_to_nav(void ) {
	//write to navigation
}


void read_navCommand(void) {
	//read navigation command
}
