/*
* Author: Jarryd Hall
* Purpose: Core Logic for controlling which navigation system is in use. 
* Interface: 
*
* Function: Switch between functions. Manual input, Auto-pilot(gps/ad-hoc)
*           User input: Transform user input to an angle, pass it along
*           Auto-Pilot GPS: Create connection to gps/ start gps parser
*           Auto-Pilot ad-hoc: Parse TMX File
* TODO: Import the path calculation classes and send them the navigation data
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "nav_corelogic.h"
#include "tmxparser.c"

//#include "movementCommands.h"

// start the gps navigation system
void nav_run_gps_system(GPSLocation *destination)
{
	printf("Creating manual command handler thread\n");
	
	// pthread functions return 0 when successful
	int manualThreadResult; 
	int gpsThreadResult;
	
	char *message = "manual movement thread command started";
	char *message2 = "gps thread started";
	pthread_t manualCommandThread;
	pthread_t gpsThread;
    
    manualThreadResult = pthread_create(&manualCommandThread, NULL, commandFetcher, (void *) message);

    // check if thread was created
    if (manualThreadResult == 0)
		printf("Manual Command Thread created\n");
    else
    {
		printf("Couldnt create manual command thread\nRetrying.....\n");
        manualThreadResult = pthread_create(&manualCommandThread, NULL, commandFetcher, (void *) message);
       
 		if (manualThreadResult == 0)
			printf("Thread created\n");
    }

    printf("Starting GPS System\n");

	gpsThreadResult = pthread_create(&gpsThread, NULL, setupgps, (void*) message2);
	
	// check if thread was created
    if (gpsThreadResult == 0)
		printf("Manual Command Thread created\n");
    else
    {
		printf("Couldnt create manual command thread\nRetrying.....\n");
        gpsThreadResult = pthread_create(&manualCommandThread, NULL, setupgps, (void *) message);

 		if (gpsThreadResult == 0)
			printf("Thread created\n");
    }
	
	//setup_gps();
    // TODO: start parser
    // TODO: start gps navigation system. Use the destination GPSLocation

    printf("gps system started\n");

    pthread_join(manualCommandThread, NULL); // wait for the thread to finish
	

	printf("Switching off gps system\n");
}

void *setupgps(void *ptr)
{
	setup_gps();
}

// start the indoor navigation system
void nav_run_indoor_system(int startTile, int destinationTile)
{
	printf("Creating manual command handler thread\n");
	
	int threadResult; // pthread functions return 0 when successful
	char *message = "manual movement command thread started";
	pthread_t manualCommandThread;
    
    threadResult = 
    pthread_create(&manualCommandThread, NULL, commandFetcher, (void *) message);

    // check if thread was created
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

	printf("indoor navigation system started\n");
	
	world = malloc(sizeof(ThreeDWorld));
	
	if (world == NULL)
	{
		printf("Youre world is fuckd! couldnt create existance\n");
	}
	else
	{
		char *doc = "secondYearSquare.xml";
		// send the world pointer to the parser for on-the-fly ThreeDWorld setup
		parseDoc(doc, world);
		// TODO: call path calculation functions and send in the world pointer
		// send the startTile and DestinationTile with the world data
	}
}

// set the gps destination
void setGPSDestination(GPSLocation *destination)
{
	
}

// function to kill GPS system - e.g only manual input wanted.
void killGPSSystem()
{
	
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

// Dealloc shouldnt be needed during a flight, 
// unless flight switches between GPS/outdoor system
void dealloc()
{
	free(world);
}

int main(int argc, char **argv) 
{
	
	return 1;
}