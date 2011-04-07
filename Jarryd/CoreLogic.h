/*
* Author: Jarryd Hall
*/

#include "Tilemap.h"

#ifndef CORELOGIC_H
#define CORELOGIC_H


typedef struct
{
	// the angle/direction the drone moved
	int directionMoved;
	
	// distance moved on each axis
	int xAxisMovement;
	int yAxisMovement;
	int zAxisMovement;
}
movementPerformed;

typedef struct
{
	double latitude;
	double longitude;
}
GPSLocation;

typedef struct
{
	ThreeDWorld *world;
	int startTile;
	int destinationTile;
}
indoorRouteRequest;

typedef struct 
{
	GPSLocation *startPoint;
	GPSLocation *destinationPoint;
}
outdoorRouteRequest;

// define 3Dworld pointer
ThreeDWorld *world;

void setupGPSSystem(GPSLocation *start, GPSLocation *destination); // setup the initial gps system
void killGPSSystem(); // kill GPS system - e.g only manual input wanted.
void setupIndoorNavigationSystem(int startTile, int destinationTile); // setup the indoor navigation system
void killIndoorNavigationSystem(); // kill the navigation system e.g. user wants only manual input.
void relayManualMovementCommand(moveCommand *_command); // relay movementCommand /Connectivity > core > movement
void sendMovementCommand(moveCommand *move); // send the movement to the movement for handling.
void updateGPSDestination(GPSLocation *destination); // update the destination at any given time: GPS
void updateIndoorDestination(int tileNumber, ThreeDWorld *world); // update an indoor destination
void receiveMovementData(movementPerformed *movement); // receive data about the movement from movement group
void createIndoorCollisionObject(int tileNumber); // create a collision object for the indoor system.
void dealloc();

#endif /* CORELOGIC_H */