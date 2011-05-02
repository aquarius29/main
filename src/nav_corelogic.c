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
* 
* TODO: Import the path calculation classes and send them the navigation data
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "nav_corelogic.h"
#include "tmxparser.c"
#include "gps_nav.h"
//#include "path_structure.h"

/* Possible thread patterns 
*	1: GPS I/O Thread + GPS Navigation Thread > GPS I/O Thread dies, kill GPS Nav Thread OR Restart GPS I/O Thread
*	2:
*
*
*/

pthread_t manualCommandThread;
pthread_t gpsSetupThread;
pthread_t gpsNavigationThread;

static pthread_mutex_t watchdogMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t watchdogCond = PTHREAD_COND_INITIALIZER;

int waitingForGpsSetupThread = 1;

static pthread_mutex_t gpsRunningMutex = PTHREAD_MUTEX_INITIALIZER;

int gpsRunning = 0;
int startGpsThread = 0;

/* Add global variables (within mutex scope) that need to be modified outside and inside threads*/


//void nav_run_gps_system(GPSLocation *destination)
void nav_run_gps_system()
{
	printf("Initiating GPS System\n");
	
	gpsRunning = 1;
	
	/* Create watchdog thread to monitor multithreading*/
	int gpsWatchdogThreadResult;
	char *watchDogMessage = "Forcing watchdog into slave labour\n";
	pthread_t gpsWatchdogThread;
	
	printf("Attempting to create gps watchdog thread\n");
    gpsWatchdogThreadResult = pthread_create(&gpsWatchdogThread, NULL, startgpswatchdog, (void *) watchDogMessage);
    
	/* wait for the watchdog thread to finish */
	pthread_join(gpsWatchdogThread, NULL);
	
	// /* check if thread was created */
	//     if (manualThreadResult == 0)
	// 	printf("Manual Command Thread created\n");
	//     else
	//     {
	// 	printf("Couldnt create manual command thread\nRetrying.....\n");
	//         manualThreadResult = pthread_create(&manualCommandThread, NULL, commandFetcher, (void *) message);
	//        
	//  		if (manualThreadResult == 0)
	// 		printf("Thread created\n");
	//     }
	// 
	//     printf("Starting GPS System\n");
	// 
	// gpsThreadResult = pthread_create(&gpsThread, NULL, setupgps, (void*) message2);
	// 
	// /* check if thread was created */
	//     if (gpsThreadResult == 0)
	// 	printf("Manual Command Thread created\n");
	//     else
	//     {
	// 	printf("Couldnt create manual command thread\nRetrying.....\n");
	//         gpsThreadResult = pthread_create(&manualCommandThread, NULL, setupgps, (void *) message);
	// 
	//  		if (gpsThreadResult == 0)
	// 		printf("Thread created\n");
	//     }
	printf("Switching off gps system\n");
}

/* watchdog function to handle multithreading */
void *startgpswatchdog(void *ptr)
{
	char *setupMessage;
    setupMessage = (char *) ptr;
    printf("%s\n", setupMessage);

	int manualCommandThreadResult; 
	int gpsSetupThreadResult;
	int gpsNavigationThreadResult;
	
	char *message = "manual movement thread command started";
	char *message2 = "gps setup thread started";
	char *message3 = "gps navigation thread started";

	/* pthread functions return 0 when successful */
	printf("Attempting to create manual command handler thread\n");
    manualCommandThreadResult = pthread_create(&manualCommandThread, NULL, commandFetcher, (void *) message);

	printf("Attempting to create GPS setup thread\n");
	gpsSetupThreadResult = pthread_create(&gpsSetupThread, NULL, setupgps, (void*) message2);
	
	pthread_cond_wait(&watchdogCond, &watchdogMutex); /* Set watchdog to wait for mutex unlock */
	
	printf("Attempting to create GPS Navigation thread\n");
	gpsNavigationThreadResult = 
	pthread_create(&gpsNavigationThread, NULL, setupgpsnavigation, (void*) message3);
	
	while (gpsRunning == 1)
	{
		// if (pthread_kill(manualCommandThread, 0) != 0)
		// 	{
		// 		printf("Manual Command Thread was murdered\nRessurecting....\n");
		// 		manualCommandThreadResult = pthread_create(&manualCommandThread, NULL, commandFetcher, (void *) message);
		// 	}
		if (pthread_kill(gpsSetupThread, 0) != 0)
		{
			int cancelResult;
			
			cancelResult = pthread_cancel( gpsNavigationThread );
			printf("cancel result is %d\n", cancelResult);
			while(cancelResult != 0)
			{
				//printf(".....");
				cancelResult = pthread_cancel( gpsNavigationThread );
			}
			// /* Create new thread for gps setup*/
			// 		printf("GPS Setup Thread died a horrible death\nRessurecting....\n");
			// 		gpsSetupThreadResult = pthread_create(&gpsSetupThread, NULL, setupgps, (void*) message2);
		}
		// if (pthread_kill(gpsNavigationThread, 0) == 0)
		// 		{
		// 			printf("GPS Navigation Thread was digitally destroyed\nReconstructing....\n");
		// 			gpsNavigationThreadResult = pthread_create(&gpsNavigationThread, NULL, setupgpsnavigation, (void*) message3);
		// 		}
	}
	
	/* wait for the threads to finish */
	pthread_join(manualCommandThread, NULL); 
	pthread_join(gpsSetupThread, NULL);
	pthread_join(gpsNavigationThread, NULL);	
}

void *setupgps(void *ptr)
{
	char *message;
    message = (char *) ptr;
    printf("%s\n", message);

	int result;

	result = pthread_mutex_lock( &watchdogMutex);
	if (result != 0)
		printf("error locking pthread mutex\n");
	
	waitingForGpsSetupThread = 0;
	
	result = pthread_mutex_unlock( &watchdogMutex );
	if (result != 0)
	printf("error unlocking pthread mutex\n");
	
	result = pthread_cond_signal(&watchdogCond); /* Wake watchdog */
	if (result != 0)
	printf("error with conditional signal\n");
	
	 setup_gps(UNO,57600);
	
	result = pthread_mutex_lock( &gpsRunningMutex );
	if (result != 0)
		printf("error locking pthread mutex\n");
			
	gpsRunning = 0;
			
		result = pthread_mutex_unlock(&gpsRunningMutex );
	if (result != 0)
		printf("error unlocking pthread mutex\n");
}

void *setupgpsnavigation(void *ptr)
{
	char *message;
    message = (char *) ptr;
    printf("%s\n", message);

	 struct point Destination = {-2,57.7053,11.9340};
	 gps_navigation(Destination);
}



void nav_run_indoor_system(position startTile, position destinationTile)
{
	printf("Creating manual command handler thread\n");
	
	int threadResult; /* pthread functions return 0 when successful */
	char *message = "manual movement command thread started";
	pthread_t manualCommandThread;
    
    threadResult = 
    pthread_create(&manualCommandThread, NULL, commandFetcher, (void *) message);

    /* check if thread was created */
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
   // init_path(startTile, destinationTile);
	printf("indoor navigation system started\n");
}

// set the gps destination
void setGPSDestination(GPSLocation *destination)
{
	
}

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

// function by which external system e.g Connectivity sends a request to move
// and the request is passes on to the movement for processing.
// NOTE: Wait for correct protocol implementation/
void relayManualMovementCommand(movementCommand *_command)
{
	// if (_command->command == NULL)
	// 	{
	// 		printf("Invalid Manual Command, cannot relay to movement\n");
	// 	}
	// 	else
	// 	{
	// 		// use protocol here to send the data to the movement for handling
	// 	}
	
}

// function for the path calculation/navigation to use to 
// send the movement to the movement for handling. 
// Movement commands will be processed one at a time
// NOTE: Wait for correct protocol implementation/
// Does the path calculation want manual commands sent to them as well so they can update the navigation
// or do they want to update it when they receive movementsMande data from movement group?
void sendMovementCommand(movementCommand *move)
{
	// if (move->command == NULL)
	// {
	// 	printf("Movement from path calculation invalid\n");
	// }
	// else
	// {
	// 	// use protocol to send the movement command to the movement group
	// }
}

// function to update the destination at any given time: GPS
void updateGPSDestination(GPSLocation *destination)
{
	// send the new data to the path calculation system
}

// function to update an indoor destination
void updateIndoorDestination(int tileNumber, ThreeDWorld *world)
{
	// send the new data to the path calculation system
	int firstDimension = tileNumber / world->mapWidth;
	int secondDimension = tileNumber % world->mapWidth;
	
	// 2 marks the tile as the destination.
	world->representation[firstDimension][secondDimension] = 2;
	// notify the path calculation to recheck the worldMap and recalculate.
}

sendNavigationDataToPathCalculation()
{
	
}

// notify the path calculation a collision was found/ stop calculation
void collisionFound()
{
	// notify the path calculation group
}

// notify the path calculation to recalculate
void collisionAvoided()
{
	// notify the path calculation to recalculate
}

// The function to send movement commands to movement system
// This depends totally on the implementation by the movement group.
// NOTE: use this when sending an entire list of commands. 
// e.g. when no collision objects are expected to arise.
void sendMovementCommandsListToMovement()
{
	
}
// TODO: Ask UI group how they handle input, a basic command e.g. right or an angle moved
// functions for handling the manual user input
// void manualMovementCommand(moveCommand *_command)
// {
// 	// TODO: notify the path calculation to stop creating movement orders.
// 	sendMovementCommand(_command);
// }

// receive data about the movement from movement group
void receiveMovementData(movementPerformed *movement)
{
	if (movement == NULL)
	{
		printf("movement data from movement system invalid\n");
	}
	else
	{
		// send the movement data to the positioning system
	}
}

// function to create a collision object for the indoor system.
void createIndoorCollisionObject(int tileNumber, ThreeDWorld *world)
{
	if (world == NULL)
	{
		printf("Trying to modify an invalid world\n");
	}
	else
	{
		// update the tilemap represenation and then send the new one to the 
		// path calculation module or just send the tile and the path calculation updates their 
		// representation graph/ If these objects arent permananet then it makes more sense.

		// calculate the tile to add the collision object.
		int firstDimension = tileNumber / world->mapWidth;
		int secondDimension = tileNumber % world->mapWidth;

		// 1 marks the tile as having an object.
		world->representation[firstDimension][secondDimension] = 1;

		// notify the path calculation to recheck the worldMap and recalculate.
		printf("Collision object created\n");
	}
}

// handles manual drone commands
void *commandFetcher(void *ptr)
{
    char *message;
    message = (char *) ptr;
    printf("%s\n", message);

	// check if it is neccesary to malloc command if it is simply being relayed
	// movementCommand *data = malloc(sizeof movementCommand);
	// 	if (data == NULL)
	// 	{
	// 		printf("Couldnt malloc movement command\n");
	// 	}
	
	movementCommand *data;
   // data = protocol_read_command;
    if (data == NULL)
        {
            printf("No command input data\n");
        }
   // else
	//	{
        // send the command to the movement group using protocol_write
        // e.g. write_movement_command
        // use core logic funtion to pause path calculation? 
		// maybe no need for pausing if we want to retake control when 
		// manual commands are done.
//		}

//	free(data);
	
	//commandfetcher();
}

void killThread()
{
	printf("KILL ME\n");
	pthread_exit(NULL);
	printf("KILLED\n");
}

double getLat()
{
	return curr.lat;
}

double getLon()
{
	return curr.lon;
}

int main(int argc, char **argv) 
{
	nav_run_gps_system();
	return 0;
}
