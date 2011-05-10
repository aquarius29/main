/*
* @author    Jarryd Hall.
* @brief     Interface module for the core logic of the abstract navigation system.
*/

#include "nav_tilemap.h"
#include "nav_movementcommands.h"
#include "nav_indoorstructure.h"

#ifndef CORELOGIC_H
#define CORELOGIC_H

int GPSIO_ON_OFF;
int GPSNAV_ON_OFF;
int sendMovement;


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

void nav_sendIndoorPathToGui(positionList *path);

/* setup gps system */
void nav_runGpsSystem(GPSLocation *dest);

/* setup the indoor navigation system */
void nav_runIndoorSystem(position startTile, position destinationTile); 

/* send the movement to the movement for handling. */
void nav_sendManualMovementCommand(movementCommand *move); 

 /* send an auto movement command for handling */
void nav_sendAutoMovementCommand(movementCommand *move);

/* update the destination at any given time: GPS */
void nav_updateGPSDestination(GPSLocation *destination); 

/* update an indoor destination */
void nav_updateIndoorDestination(int tileNumber, ThreeDWorld *world); 

/* receive data about the movement from movement group */
void nav_receiveMovementData(movementCommand *movement); 

/* create a collision object for the indoor system. */
void nav_createIndoorCollisionObject(int tileNumber, ThreeDWorld *world);
 
 /* kill GPS system - e.g only manual input wanted. */
void nav_killGPSSystem();

/* kill the navigation system e.g. user wants only manual input. */
void nav_killIndoorNavigationSystem(); 

/* kill the gps navigation system only and schedule it for restart */
void killGPSNavigationSystem();

/* kill the gps io system only and schedule it for restart*/
void killGPSIO();

/* Set a new destination for the gps */
void nav_setGPSDestination(GPSLocation *destination); 

void killThread();
void dealloc();

/* Threaded Functions*/
void *setupgps(void *ptr);
void *setupgpsnavigation(void *ptr);
void *startgpswatchdog(void *ptr);
void *startIndoorNavigationSystem(void *ptr);
void *readProtocol(void *ptr);

#endif /* CORELOGIC_H */
