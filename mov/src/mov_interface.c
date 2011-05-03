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

	return 0;

}


/*
 *
 */
int mov_run(){
	printf("\n \n*********************LOOOOOOOP***************************\n");

	/*If the distanceToTravel is less than or equal to 0, we have probably arrived**/

	if(distanceToTravel <= 0 && heightArrived == 1 && yawArrived == 1){
		heightArrived = 0;
		yawArrived = 0;
		distanceToTravel = 0;
		if (read_command()== 0) {  
			printf("**end of the file**\n");
			return 1;
		}
		else{
			distanceToTravel = navCommand.distance;
		}
	}
	

	command_logic();

	/* stabilize based on last movement  */
	//stabL();
	sleep(1);

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
