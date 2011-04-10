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
#include "CoreLogic.h"
#include "TMXParser.c"
#include "movementCommands.h"

// function to setup the initial gps system
void setupGPSSystem()
{
		printf("Starting GPS System\n");
		// TODO: start connection to gps
		// TODO: start parser
		// TODO: fetch data from gps data structure
		// TODO: Notify path calculation that gps is started/ is being used send in start and desintation
		printf("gps system started\n");
}

// set the gps destination
void setGPSDestination(GPSLocation *destination);

// function to kill GPS system - e.g only manual input wanted.
void killGPSSystem()
{
	
}

// setup the indoor navigation system
void setupIndoorNavigationSystem(int startTile, int destinationTile)
{
		printf("indoor navigation system started\n");
		world = malloc(sizeof(ThreeDWorld));
		if (world == NULL)
		{
			printf("Youre world is fucked! couldnt create existance\n");
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

// function to kill the navigation system e.g. the user wants only manual input.
void killIndoorNavigationSystem()
{
	
}

// function by which external system e.g Connectivity sends a request to move
// and the request is passes on to the movement for processing.
// NOTE: Wait for correct protocol implementation/
void relayManualMovementCommand(moveCommand *_command)
{
	if (_command->command == NULL)
	{
		printf("Invalid Manual Command, cannot relay to movement\n");
	}
	else
	{
		// use protocol here to send the data to the movement for handling
	}
	
}

// function for the path calculation/navigation to use to 
// send the movement to the movement for handling. 
// Movement commands will be processed one at a time
// NOTE: Wait for correct protocol implementation/
void sendMovementCommand(moveCommand *move)
{
	if (move->command == NULL)
	{
		printf("Movement from path calculation invalid\n");
	}
	else
	{
		// use protocol to send the movement command to the movement group
	}
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
	int firstDimension = tileNumber / world->mapwidth;
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
		int firstDimension = tileNumber / world->mapwidth;
		int secondDimension = tileNumber % world->mapWidth;

		// 1 marks the tile as having an object.
		world->representation[firstDimension][secondDimension] = 1;

		// notify the path calculation to recheck the worldMap and recalculate.
		printf("Collision object created\n");
	}

}

// Dealloc shouldnt be needed during a flight, unless flight switches between GPS/outdoor system
void dealloc()
{
	free(world);
}