/*
* Author: Jarryd Hall
*/

#include "Tilemap.h"

#ifndef NAVIGATIONSYSTEM_H
#define NAVIGATIONSYSTEM_H

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
void setupIndoorNavigationSystem(int startTile, int destinationTile);
void manualMovementCommand(moveCommand *_command);
void receiveOrder(movementPerformed *movement);

#endif /* NAVIGATIONSYSTEM_H */