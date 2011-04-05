/*
* Author: Jarryd Hall
* Purpose: Logic for controlling which navigation system is in use. 
* Interface: 
*
* Function: Switch between functions. Manual input, Auto-pilot(gps/ad-hoc)
*           User input: Transform user input to an angle, pass it along
*           Auto-Pilot GPS: Create connection to gps/ start gps parser
*           Auto-Pilot ad-hoc: Parse TMX File
* TODO: Import the path calculation classes and send them the navigation data
*/

#include <stdio.h>
#include "NavigationSystem.h"
#include "TMXParser.c"
#include "movementCommands.h"

void setupGPSSystem(GPSLocation *start, GPSLocation *destination)
{
		printf("Starting GPS System");
		// TODO: start connection to gps
		// TODO: start parser
		// TODO: fetch data from gps data structure
		// TODO: Notify path calculation that gps is started/ is being used send in start and desintation
		printf("gps system started\n");
}

void setupIndoorNavigationSystem(int startTile, int destinationTile)
{
		printf("indoor navigation system started\n");
		world = malloc(sizeof(ThreeDWorld));
		if (world == NULL)
		{
			printf("Youre world is fucked! couldnt create existance");
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

sendNavigationDataToPathCalculation()
{
	
}

// The function to send movement commands to movement system
// This depends totally on the implementation by the movement group.
sendMovementCommandsToMovement()
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
void receiveOrder(movementPerformed *movement)
{
	// send the movement data to the positioning system
}

// Dealloc shouldnt be needed during a flight, unless flight switches between GPS/outdoor system
void dealloc()
{
	free(world);
}