/*
* 	@author 	Jarryd Hall
* 
* 	@details 	Core Logic will be used as an entry point for external sub-systems e.g Connectivity
*   	       	and will be used to write data using the protocol for e.g. Movement and UI data.
*          
*       	   	Core Logic will create a watchdog thread which in turn multithreads the following:
*          		Manual movement command fetcher for handling manual movement commands and relaying them
*          		GPS Setup thread which connects to GPS device and reads data from the device
*          		GPS Navigation thread which calculates gps flight path
*
*				Core Logic is used to setup the correct system e.g. 
*				GPS navigation / Indoor Navigation
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "nav_corelogic.h"
#include "tmxparser.c"
#include "gps_nav.h"
#include "tilemap.h"
//#include "path_structure.h"

pthread_t gpsSetupThread;
pthread_t gpsNavigationThread;
pthread_t indoorNavigationThread;

static pthread_mutex_t watchdogMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t watchdogCond = PTHREAD_COND_INITIALIZER;

int waitingForGpsSetupThread = 1;

static pthread_mutex_t gpsRunningMutex = PTHREAD_MUTEX_INITIALIZER;

int gpsRunning = 0;
int indoorSystemRunning = 0;

/* GPS System Functions start here */
void nav_runGpsSystem(GPSLocation *dest)
{
	printf("Initiating GPS System\n");
	
	gpsRunning = 1;
	ON_OFF = 1;
	
	GPSLocation *destination = malloc(sizeof(GPSLocation));
	destination = dest;
	
	printf("destination lat : %lf", destination->latitude);
    
	/* Create watchdog thread to monitor multithreading */
	int gpsWatchdogThreadResult;
	pthread_t gpsWatchdogThread;
	
	printf("Attempting to create gps watchdog thread\n");
    gpsWatchdogThreadResult = pthread_create(&gpsWatchdogThread, NULL, startgpswatchdog, (void *) destination);
    
	/* wait for the watchdog thread to finish */
	pthread_join(gpsWatchdogThread, NULL);
	
	free(destination); /* clean the filth */
	
	printf("Switching off gps system\n");
}

/* watchdog function to handle gps multithreading */
void *startgpswatchdog(void *ptr)
{
	GPSLocation *destination;
	destination = (GPSLocation *) ptr;
	printf("destination after watchdog receive lat : %lf\n", destination->latitude);
	printf("destination after watchdog receive lon : %lf\n", destination->longitude);
 
	int gpsSetupThreadResult;
	int gpsNavigationThreadResult;
	
	char *message2 = "gps setup thread started";

	/* pthread functions return 0 when successful */
	printf("Attempting to create GPS setup thread\n");
	gpsSetupThreadResult = pthread_create(&gpsSetupThread, NULL, setupgps, (void*) message2);
	
	/* pthread_cond_wait(&watchdogCond, &watchdogMutex); /* Set watchdog to wait for mutex unlock */

	int data = 0;
    int loopCount = 0;
    
	while(loopCount < 1000)
	{
		data = get_goodData();
		
		if (data == 1)
		{
			printf("Attempting to create GPS Navigation thread\n");
			gpsNavigationThreadResult = 
			pthread_create(&gpsNavigationThread, NULL, setupgpsnavigation, (void*) destination);
			break;
		}
		else
        	usleep(20000);
	}
	
	while (gpsRunning == 1)
	{
		/* pthread_kill(someThread, 0) */
		/* sending a zero to the thread will not kill the thread */
		/* using the return value it can check of the thread is dead */
		
        if (pthread_kill(gpsSetupThread, 0) != 0)/* GPS Setup Thread is dead */
        {
			printf("GPS Setup Thread died a horrible death\nRessurecting....\n");
            
			int cancelResult;

            cancelResult = pthread_cancel( gpsNavigationThread ); /* cancel the nav thread */
            printf("cancel result is %d\n", cancelResult);
            while(cancelResult != 0)
            {
                printf(".....");
                cancelResult = pthread_cancel( gpsNavigationThread );
            }
                /* Create new thread for gps setup */
                gpsSetupThreadResult = pthread_create(&gpsSetupThread, NULL, setupgps, (void*) message2);

				while(loopCount < 1000)
				{
					data = get_goodData();

					if (data == 1)
					{
						printf("Attempting to create GPS Navigation thread\n");
						gpsNavigationThreadResult = 
						pthread_create(&gpsNavigationThread, NULL, setupgpsnavigation, (void*) destination);
						break;
					}
					else
			        	usleep(20000);
				}
        }
    }
		// if (pthread_kill(gpsNavigationThread, 0) == 0)
		// 		{
		// 			printf("GPS Navigation Thread was digitally destroyed\nReconstructing....\n");
		// 			gpsNavigationThreadResult = pthread_create(&gpsNavigationThread, NULL, setupgpsnavigation, (void*) message3);
		// 		}
//	}
	
	/* wait for the threads to finish */
	pthread_join(gpsSetupThread, NULL);
	pthread_join(gpsNavigationThread, NULL);	
}

void *setupgps(void *ptr)
{
	char *message;
    message = (char *) ptr;
    printf("%s\n", message);
    	
	setup_gps(UNO,57600);
}

void *setupgpsnavigation(void *ptr)
{
	printf("GPS Navigation Thread Started\n");
	
	GPSLocation *destination;
	destination = (GPSLocation *) ptr;
	printf("destination after gps nav receive lat : %lf\n", destination->latitude);
	printf("destination after gps nav receive lon : %lf\n", destination->longitude);

	 // struct point Destination = {-2,57.7053,11.9340};
	 // 	 gps_navigation(Destination);
	gps_navigation(destination);
}
/* GPS System Functions end here */

/* Indoor System Functions start here */
void nav_runIndoorSystem(position startTile, position destinationTile)
{  
  	struct thread_data *data = malloc(sizeof(struct thread_data));
		data->starttile = startTile;
		data->destinationtile = destinationTile;
		data->message = "Indoor system started";
			
	int indoorThreadResult;
	
	indoorThreadResult = 
		pthread_create(&indoorNavigationThread, NULL, startIndoorNavigationSystem, (void *) data);
	
	indoorSystemRunning = 1;
	
	while(indoorSystemRunning == 1)
	{
		if (pthread_kill(indoorNavigationThread, 0) == 0)
		{
			free(data);
			printf("Indoor System quite unexpectedly\nRestarting...\n");
			
			struct thread_data *newData = malloc(sizeof(struct thread_data));
			newData->
			newData->
			newData->
			
			indoorThreadResult = 
				pthread_create(&indoorNavigationThread, NULL, startIndoorNavigationSystem, (void *) newData);
		}
	}
    /* check if thread was created */
    /*
    if (threadResult == 0)
		printf("Thread created\n");
    else
    {
		printf("Couldnt create thread\nRetrying.....\n");
		
        threadResult = 
	    pthread_create(&manualCommandThread, NULL, commandFetcher, (void *) message);
       
 		if (threadResult == 0)
			printf("Thread created\n");
    }
    
    */
   // init_path(startTile, destinationTile);
	pthread_join(indoorNavigationThread, NULL);
	printf("indoor navigation system shut down\n");
}

/* Function to be run in a pthread for indoor navigation */
void *startIndoorNavigationSystem(void *ptr)
{
	printf("Started the indoor navigation tread\n");
	struct thread_data *data = (struct thread_data*) ptr;
	
	/* Call the indoor nav system here and pass in the data ptr */
	
	
}

// function for the path calculation/navigation to use to 
// send the movement to the movement for handling. 
// Movement commands will be processed one at a time
// NOTE: Wait for correct protocol implementation/
// Does the path calculation want manual commands sent to them as well so they can update the navigation
// or do they want to update it when they receive movementsMande data from movement group?
void nav_sendMovementCommand(movementCommand *move)
{
	if(move->type == 0)
	{
		/* Send the movement command to navigation system */
		/* Send the movement command to movement/write it to protocol static object */ 
	}
	else if (move->type == 1)
	{
		/* If movement commands are not being written in the nav systems directly. skip this else statement */
		/* Send the movement command to movement/write it to the protocol static object */
	}
}

/* function to update the destination at any given time: GPS */
void nav_updateGPSDestination(GPSLocation *destination)
{
	/* send the new data to the path calculation system */
}

/* function to update an indoor destination */
void nav_updateIndoorDestination(int tileNumber, ThreeDWorld *world)
{
	/* send the new data to the path calculation system */
	int firstDimension = tileNumber / world->mapWidth;
	int secondDimension = tileNumber % world->mapWidth;
	
	/* 2 marks the tile as the destination. */
	world->representation[firstDimension][secondDimension] = 2;
	/* notify the path calculation to recheck the worldMap and recalculate. */
}

/* notify the path calculation a collision was found/ stop calculation */
void nav_collisionFound()
{
	/* notify the path calculation group */
}

/* notify the path calculation to recalculate */
void nav_collisionAvoided()
{
	/* notify the path calculation to recalculate */
}

// TODO: Ask UI group how they handle input, a basic command e.g. right or an angle moved
// functions for handling the manual user input
// void manualMovementCommand(moveCommand *_command)
// {
// 	// TODO: notify the path calculation to stop creating movement orders.
// 	sendMovementCommand(_command);
// }

/* function to create a collision object for the indoor system. */
void nav_createIndoorCollisionObject(int tileNumber, ThreeDWorld *world)
{
	if (world == NULL)
	{
		printf("Trying to modify an invalid world\n");
	}
	else /* update the tilemap represenation */
	{
		/* calculate the tile to add the collision object. */
		int firstDimension = tileNumber / world->mapWidth;
		int secondDimension = tileNumber % world->mapWidth;

		/* 1 marks the tile as having an object. */
		world->representation[firstDimension][secondDimension] = 1;

		/* notify the path calculation to recheck the worldMap and recalculate. */
		printf("Collision object created\n");
	}
}

/* Begin Kill functions */

/* Kill the gps system */
void killGPSSystem()
{
	int result;
	result = pthread_mutex_lock( &watchdogMutex);
	gpsRunning = 0;
	result = pthread_mutex_unlock( &watchdogMutex );

	result = pthread_cancel(gpsNavigationThread);
}

// function to kill the navigation system e.g. the user wants only manual input.
void killIndoorNavigationSystem()
{
	
}

void killThread()
{
	printf("KILL ME\n");
	pthread_exit(NULL);
	printf("KILLED\n");
}
/* End kill functions */

/* Begin functions that are using the protocol */
void nav_sendAutoMovementCommand(movementCommand *move)
{
	/* Add protocol functions to send to movement */
}

void nav_sendManualMovementCommand(movementCommand *move)
{
	/* 1: 	Pause Auto movement command generation */
	/* 		Extract or send movement command to nav system */
	/* 2:	Add protocol functions to send to movement */
	/* 3:	Unpause auto movement command generation */
}
/* End functions that are using the protocol */

/* Begin interface:out functions for connectivity group */
void nav_sendCurrentIndoorPositionToGui(pixel *currentPosition)
{
	/* Put connectivity library function here*/
}

void nav_sendCurrentOutdoorPositionToGui(GPSLocation *currentPosition)
{
	/* Put connectivity library function here */
	/* Pass in currentOutdoorPosition */
}

void nav_sendOutdoorPathToGui(GPSLocation **path)
{
	/* Put connectivity library function here*/
}

void nav_sendIndoorPathToGui(pixel **path)
{
	/* Put connectivity library function here*/
}
/* End interface:out functions for connectivity group */

int main(int argc, char **argv) 
{
	GPSLocation *Destination = malloc(sizeof(GPSLocation));
	Destination->latitude = 57.7053;
	Destination->longitude = 11.9340;
	
	nav_runGpsSystem(Destination);
	return 0;
}