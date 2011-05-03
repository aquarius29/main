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

GPSLocation *currentOutdoorPosition;

void nav_run_gps_system();
//void nav_run_gps_system(GPSLocation *destination); // setup gps system
void killGPSSystem(); /* kill GPS system - e.g only manual input wanted. */
void nav_run_indoor_system(position startTile, position destinationTile); /* setup the indoor navigation system */
void killIndoorNavigationSystem(); /* kill the navigation system e.g. user wants only manual input. */
void relayManualMovementCommand(movementCommand *_command); /* relay movementCommand /Connectivity > core > movement */
void sendMovementCommand(movementCommand *move); /* send the movement to the movement for handling. */
void updateGPSDestination(GPSLocation *destination); /* update the destination at any given time: GPS */
void updateIndoorDestination(int tileNumber, ThreeDWorld *world); /* update an indoor destination */
void receiveMovementData(movementCommand *movement); /* receive data about the movement from movement group */
void createIndoorCollisionObject(int tileNumber, ThreeDWorld *world); /* create a collision object for the indoor system. */
void sendMovementCommandsListToMovement(); /* send a list of movement commands to movement group. */
void *commandFetcher(void *ptr);
void killThread();
void dealloc();
double getLat(); // called by UI via connectivity
double getLong(); // called by UI via connectivity
void *setupgps(void *ptr);
void *setupgpsnavigation(void *ptr);
void *startgpswatchdog(void *ptr);

#endif /* CORELOGIC_H */
