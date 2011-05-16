/*
* @author    Jarryd Hall.
* @brief     Interface module for the core logic of the abstract navigation system.
*/

#include "nav_tilemap.h"
#include "nav_movementcommands.h"
#include "nav_indoorstructure.h"

#ifndef CORELOGIC_H
#define CORELOGIC_H

<<<<<<< HEAD
=======
//#define CENTIMETRES_PER_TILE 

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
int GPSIO_ON_OFF;
int GPSNAV_ON_OFF;
int sendMovement;

<<<<<<< HEAD
roomPosition *currPosition;

=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
typedef struct
{
    double latitude;
    double longitude;
}
GPSLocation;

typedef struct
{
    tile startTile;
    tile destinationTile;
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
    tile starttile;
    tile destinationtile;
    char *message;
};

<<<<<<< HEAD
GPSLocation currentOutdoorPosition;
=======
GPSLocation *destination;
GPSLocation currentOutdoorPosition;
roomPosition *currPosition;
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

void nav_sendCurrentIndoorPositionToGui(roomPosition *currentPosition);

void nav_sendCurrentOutdoorPositionToGui(GPSLocation *currentPosition);

void nav_sendOutdoorPathToGui(GPSLocation **path);

void nav_sendIndoorPathToGui(positionList *path, int8_t type);

/* setup gps system */
//void nav_runGpsSystem(GPSLocation *dest);
void nav_runGpsSystem(double lat, double lon);

/* setup the indoor navigation system */
//void nav_runIndoorSystem(tile startTile, tile destinationTile);
void nav_runIndoorSystem(double startX, double startY, double destinationX, double destinationY);

/* send the movement to the movement for handling. */
void nav_sendManualMovementCommand(struct movCommand *move); 

 /* send an auto movement command for handling */
void nav_sendAutoMovementCommand(struct movCommand *move);

/* update the destination at any given time: GPS */
void nav_updateGPSDestination(GPSLocation *destination); 

/* update an indoor destination */
void nav_updateIndoorDestination(int tileNumber, ThreeDWorld *world); 

/* receive data about the movement from movement group */
void nav_receiveMovementData(struct movCommand *movement); 

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

<<<<<<< HEAD
=======
/* Used by connectivity to send movement commands using an identifier int */
void nav_setMovementIdentifier(int id);

/* Start the conectivity Listener thread system */
void startConnectivityListenerThreads();

/* start and monitor the protocol read thread */
void *protocolReadWatchdog(void *ptr);

void nav_setIndoorData(double startX, double startY, double destinationX, double destinationY);
void nav_setOutdoorData(double destinationX, double destinationY);

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
void killThread();
void dealloc();

/* Threaded Functions*/
void *setupgps(void *ptr);
void *setupgpsnavigation(void *ptr);
void *startgpswatchdog(void *ptr);
void *startIndoorNavigationSystem(void *ptr);
<<<<<<< HEAD
void *readProtocol(void *ptr);
=======
void *startIndoorWatchdogThread(void *ptr);
void *readProtocol(void *ptr);
void *protocolReadWatchdog(void *ptr);
void *startConnectivityListener(void *ptr);
void *startConnectivityListenerWatchdog(void *ptr);
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

int16_t nav_init(void);
int16_t nav_run(void);


#endif /* CORELOGIC_H */
