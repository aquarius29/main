/*
* Author: Jarryd Hall
*/

#include "tilemap.h"
#include "movementcommands.h"
#include "path_structure.h"

#ifndef CORELOGIC_H
#define CORELOGIC_H

int ON_OFF;

typedef struct
{
	double latitude;
	double longitude;
}
GPSLocation;

typedef struct
{
	position startTile;
	position destinationTile;
}
indoorRouteRequest;

typedef struct 
{
	GPSLocation *startPoint;
	GPSLocation *destinationPoint;
}
outdoorRouteRequest;

struct thread_data
{
	position starttile;
	position destinationtile;
	char *message;
};

GPSLocation currentOutdoorPosition;

void nav_sendCurrentIndoorPositionToGui(pixel *currentPosition);
void nav_sendCurrentOutdoorPositionToGui(GPSLocation *currentPosition);
void nav_sendOutdoorPathToGui(GPSLocation **path);
void nav_sendIndoorPathToGui(pixel **path);
void nav_runGpsSystem(GPSLocation *dest); /* setup gps system */
void nav_runIndoorSystem(position startTile, position destinationTile); /* setup the indoor navigation system */
void nav_sendManualMovementCommand(movementCommand *move); /* send the movement to the movement for handling. */
void nav_updateGPSDestination(GPSLocation *destination); /* update the destination at any given time: GPS */
void nav_updateIndoorDestination(int tileNumber, ThreeDWorld *world); /* update an indoor destination */
void nav_receiveMovementData(movementCommand *movement); /* receive data about the movement from movement group */
void nav_createIndoorCollisionObject(int tileNumber, ThreeDWorld *world); /* create a collision object for the indoor system. */
void nav_killGPSSystem(); /* kill GPS system - e.g only manual input wanted. */
void nav_killIndoorNavigationSystem(); /* kill the navigation system e.g. user wants only manual input. */

void killThread();
void dealloc();

/* Threaded Functions*/
void *setupgps(void *ptr);
void *setupgpsnavigation(void *ptr);
void *startgpswatchdog(void *ptr);
void *startIndoorNavigationSystem(void *ptr);


#endif /* CORELOGIC_H */