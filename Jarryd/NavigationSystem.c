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
* User controls: see .h file
*
*/

#include <stdio.h>
#include "NavigationSystem.h"
#include "TMXParser.c"
#include "Tilemap.c"

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
	ThreeDWorld *world = NULL;
	// TODO: Set the return of the parsed doc to the new representation

	char *doc = "secondYearSquare.xml";
	parseDoc(doc);
	
	// TODO: Open the return struct and set the representation fields to the fields\
	//       of the returned parsed struct.
	
	
}

// Create a movement order
void createMovementOrder(char* _order, int _direction, int _height)
{
	controlOrder *order = malloc(sizeof(controlOrder));
	order->order = _order;
	order->direction = _direction;
	order->height = _height;
	// Function from interface to send order goes here e.g. InterfaceSendOrder(order);
	free(order);
}

void receiveOrder(movementPerformed *movement)
{
	
}