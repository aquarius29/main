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

ThreeDWorld *world;

void setNavigationSystem(char *navigationSystem);
void setupGPSSystem();
void setupIndoorNavigationSystem();
void manualMovementCommand(moveCommand *_command);
void receiveOrder(movementPerformed *movement);

#endif /* NAVIGATIONSYSTEM_H */