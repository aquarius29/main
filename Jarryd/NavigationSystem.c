/*
* Author: Jarryd Hall
* Purpose: Logic for controlling which navigation system is in use. 
* Interface: 
*
* Function: Switch between functions. Manual input, Auto-pilot(gps/ad-hoc)
*           User input: Transform user input to an angle, pass it along
*           Auto-Pilot GPS: Create connection to gps/ start gps parser
*           Auto-Pilot ad-hoc: Parse TMX File
*
*/

#include <stdio.h>
#include "NavigationSystem.h"
#include "TMXParser.c"
#include "movementCommands.h"

// Determine if the gps system is used together with the indoor system
void setNavigationSystem(char* navigationSystem)
{
	if (strcmp("gps", navigationSystem) == 0)
	{
		setupGPSSystem;
		printf("gps system started\n");
	}
	else if ((strcmp("indoor", navigationSystem) == 0))
	{
		setupIndoorNavigationSystem;
		printf("indoor navigation system started\n");
	}
	else
		fprintf(stderr, "Incorrect system selected\n");
}

void setupGPSSystem()
{
	// TODO: start connection to gps
	// TODO: start parser
	// TODO: fetch data from gps data structure
}

void setupIndoorNavigationSystem()
{
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
	}
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

// Dealloc shouldnt be needed during a flight, unless flight switches to GPS/outdoor system
void dealloc()
{
	free(world);
}