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

void setupGPSSystem(GPSLocation *start, GPSLocation *destination);
void killGPSSystem();
void setupIndoorNavigationSystem(int startTile, int destinationTile);
void killIndoorNavigationSystem();
void relayManualMovementCommand(moveCommand *_command);
void sendMovementCommand(moveCommand *move);
void updateIndoorDestination(int destinationTile);
void updateGPSDestination(GPSLocation *destination);
void receiveMovementData(movementPerformed *movement);
void createIndoorCollisionObject(int tileNumber);
void dealloc();

#endif /* CORELOGIC_H */