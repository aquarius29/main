/*
*   @author     Jarryd Hall.
* 
*   @details    Core Logic will be used as an entry point for external sub-systems e.g Connectivity
*               and will be used to write data using the protocol for e.g. Movement and UI data.
*          
*               Core Logic will create a watchdog thread which in turn multithreads the following:
*               Protocol Reader Thread to get data from the protocol.
*               GPS Setup thread which connects to GPS device and reads data from the device.
*               GPS Navigation thread which calculates gps flight path.
*
*               Core Logic is used to setup the correct system e.g. 
*               GPS navigation / Indoor Navigation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <signal.h>
#include "nav_corelogic.h"
#include "nav_gps_nav.h"
#include "nav_tilemap.h"
#include "nav_indoorstructure.h"
#include "nav_handlemanualcommands.h"

static tile roomPositionToTile(roomPosition *current);

pthread_t protocolWatchdogThread;
pthread_t protocolReadThread;

pthread_t gpsSetupThread;
pthread_t gpsNavigationThread;

pthread_t indoorWatchdogThread;
pthread_t indoorNavigationThread;

pthread_t connectivityListenerWatchdogThread;
pthread_t connectivityListenerThread;

int protocolReading = 0;
int monitoringProtocolThread = 1;

static pthread_mutex_t watchdogMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t watchdogCond = PTHREAD_COND_INITIALIZER;
int waitingForGpsSetupThread = 1;

static pthread_mutex_t gpsRunningMutex = PTHREAD_MUTEX_INITIALIZER;
int gpsRunning = 0;

static pthread_mutex_t indoorNavigationRunningMutex = PTHREAD_MUTEX_INITIALIZER;
int indoorSystemRunning = 1;

static pthread_mutex_t movementIdMutex = PTHREAD_MUTEX_INITIALIZER;
static int nav_movementId = 0;

static pthread_mutex_t newMovementMutex = PTHREAD_MUTEX_INITIALIZER;
static int nav_newMovement = 0;

static pthread_mutex_t gpsDestinationXMutex = PTHREAD_MUTEX_INITIALIZER;
double nav_runGPSDestinationX;

static pthread_mutex_t gpsDestinationYMutex = PTHREAD_MUTEX_INITIALIZER;
double nav_runGPSDestinationY;

static pthread_mutex_t indoorStartXMutex = PTHREAD_MUTEX_INITIALIZER;
double nav_runIndoorStartX;

static pthread_mutex_t indoorStartYMutex = PTHREAD_MUTEX_INITIALIZER;
double nav_runIndoorStartY;

static pthread_mutex_t indoorEndXMutex = PTHREAD_MUTEX_INITIALIZER;
double nav_runIndoorEndX;

static pthread_mutex_t indoorEndYMutex = PTHREAD_MUTEX_INITIALIZER;
double nav_runIndoorEndY;

static pthread_mutex_t startIndoorMutex = PTHREAD_MUTEX_INITIALIZER;
int nav_startIndoor;

static pthread_mutex_t startOutdoorMutex = PTHREAD_MUTEX_INITIALIZER;
int nav_startOutdoor;



// void startConnectivityListenerThreads()
// {
// 	
// }

// void *startConnectivityListenerWatchdog(void *ptr)
// {
// 	/* Multithreading FTFW */
// 	
// 	char *message;
//     message = (char *) ptr;
// 	printf("%s\n", message);
// 
// 	int conListenerThreadResult;
// 	
// 	char *message2 = "Connectivity Listener Started";
// 	
//     conListenerThreadResult = 
// 		pthread_create(&connectivityListenerThread, NULL, startConnectivityListener, (void*) message2);
// 	
// 	int watching = 1;
// 	
// 	while(watching == 1)
// 	{
// 		if (pthread_kill(connectivityListenerThread, 0) != 0) /* Listener died */
// 		{
// 			conListenerThreadResult = 
// 				pthread_create(&connectivityListenerThread, NULL, startConnectivityListener, (void*) message2);
// 		}
// 	}
// 	
// 	 pthread_join(connectivityListenerThread, NULL);
// }

void *startConnectivityListener(void *ptr)
{
	char *message;
    message = (char *) ptr;
	printf("%s\n", message);
	
	/* Declare safety variables because segments cant be locked/unlocked 
	*  using mutexes if they are checking in statement such as if and while.
	*/
	int newMoveCheck = 0;
	int startIndoorCheck = 0;
	int startOutdoorCheck = 0;
	
	int listening = 1;
	
	while(listening == 1)
	{
		int result; /* Use for testing */
		
		/* check if a new movement command waits */
		result = pthread_mutex_lock(&newMovementMutex);
		newMoveCheck = nav_newMovement;
		printf("nav new movement in thread is :%d\n", nav_newMovement);
		printf("newMoveCheck in mutex lock is:%d\n", newMoveCheck);
	    result = pthread_mutex_unlock(&newMovementMutex);
	
		printf("newMoveCheck is %d\n", newMoveCheck);
		sleep(1);
		
		if(newMoveCheck == 1)
		{
			printf("New Move requested for sending\n");
			int tempId;
			int result; /* Use for testing */
			
			/* fetch the id of the movement requested */
			result = pthread_mutex_lock(&movementIdMutex);
		    tempId = nav_movementId;
		    result = pthread_mutex_unlock(&movementIdMutex);
			
			printf("The movement id fetched by connectivity listener thread is : %d", tempId);
			
			/* Add function to send movement command to manual movement handler. */
			
			/* set it back to 0 */
			result = pthread_mutex_lock(&newMovementMutex);
			nav_newMovement = 0;
		    result = pthread_mutex_unlock(&newMovementMutex);
			
			if(nav_newMovement == 0)
				printf("Waiting for next movement command\n");
		}
		
		/* Check if indoor system start request has been made */
		result = pthread_mutex_lock(&startIndoorMutex);
		int startIndoorCheck = nav_startIndoor;
		result = pthread_mutex_unlock(&startIndoorMutex);
		
		if (startIndoorCheck == 1)
		{
			//printf("I got here\n");
			/* Set it back to 0*/
			result = pthread_mutex_lock(&startIndoorMutex);
			nav_startIndoor = 0;
			result = pthread_mutex_unlock(&startIndoorMutex);
			
			double indoorStartX;
			double indoorStartY;
			double indoorEndX;
			double indoorEndY;
			
			/* Lock and Unlock Variables to copy values for triggering indoor start system
			*  This wouldnt be necessary if I knew the input was in sequence 
			*  and a write wouldnt occur to these variables elsewhere at this point. 
			*  Basically: This is for thread safety. :D
			*
			* If you are wondering why there are so many mutexes( 1 per variable)
			* I want to maintain concurrency as much as possible, releasing mutex 
			* ownership as quickly as possible.
			*/
			
			int result; /* Use for testing */

		    result = pthread_mutex_lock(&indoorStartXMutex);
		    indoorStartX = nav_runIndoorStartX;
		    result = pthread_mutex_unlock(&indoorStartXMutex);

			result = pthread_mutex_lock(&indoorStartYMutex);
			indoorStartY = nav_runIndoorStartY;
		    result = pthread_mutex_unlock(&indoorStartYMutex);

			result = pthread_mutex_lock(&indoorEndXMutex);
		    indoorEndX = nav_runIndoorEndX;
		    result = pthread_mutex_unlock(&indoorEndXMutex);

			result = pthread_mutex_lock(&indoorEndYMutex);
		    indoorEndY = nav_runIndoorEndY;
		    result = pthread_mutex_unlock(&indoorEndYMutex);
		
			/* 
			*  call the trigger function with the new values, this is a function 
			*  to trigger nav when it is already running.
			*  Waiting on the new function for starting path calculation
			*  once system is running.
			*/		
			// struct thread_data *data = malloc(sizeof(struct thread_data));
			// 		        data->starttile.x = indoorStartX;
			// 				data->starttile.y = indoorStartY;
			// 		        data->destinationtile.x = indoorEndX;
			// 				data->destinationtile.y = indoorEndY;
			// 		        data->message = "Indoor system started";
			// 			
			// 			initPath(&data->starttile, &data->destinationtile);
			
			
		}
		
		/* Again, these check are needed because locking/unlocking cant be done
		*  in if and while statements.
		*/
		result = pthread_mutex_lock(&startOutdoorMutex);
		startOutdoorCheck = nav_startOutdoor;
		result = pthread_mutex_unlock(&startOutdoorMutex);
		
		if(startOutdoorCheck == 1)
		{
			double destinationX;
			double destinationY;
			int result; /* Use for testing*/
			
			result = pthread_mutex_lock(&gpsDestinationXMutex);
		    destinationX = nav_runGPSDestinationX;
		    result = pthread_mutex_unlock(&gpsDestinationXMutex);

			result = pthread_mutex_lock(&gpsDestinationYMutex);
		    destinationY = nav_runGPSDestinationY;
		    result = pthread_mutex_unlock(&gpsDestinationYMutex);
		
			/* Start the GPS System with destination values */
			nav_runGpsSystem(destinationX, destinationY);
			
			/* Set it back to 0 */
			result = pthread_mutex_lock(&startOutdoorMutex);
			nav_startOutdoor = 0;
			result = pthread_mutex_unlock(&startOutdoorMutex);
		}
	}
}

/* GPS System Functions start here */

//!
/*!
*
*
*
*/ 
//void nav_runGpsSystem(GPSLocation *dest)
void nav_runGpsSystem(double lat, double lon)
{
    printf("Initiating GPS System\n");
    
    gpsRunning = 1;

    destination = malloc(sizeof(GPSLocation));	
	destination->latitude = lat;
	destination->longitude = lon;
    
    printf("destination lat : %lf", destination->latitude);
    
    /* Create watchdog thread to monitor multithreading */
    int gpsWatchdogThreadResult;
    pthread_t gpsWatchdogThread;
    
    printf("Attempting to create gps watchdog thread\n");
    gpsWatchdogThreadResult = pthread_create(&gpsWatchdogThread, NULL, startgpswatchdog, (void *) destination);
    
    /* wait for the watchdog thread to finish */
    pthread_join(gpsWatchdogThread, NULL);
    
    free(destination); /* clean the filth */
    
    printf("Switching off gps system\n");
}

//! Watchdog function to handle gps multithreading.
/*! A threaded function that will monitor the GPS threads
*   to see if they dont unexpectedly quit or die.
*   This watchdog thread restarts threads that are needed to keep 
*   the GPS system running correctly.
*
* @param ptr A void pointer to send arguments to the watchdog thread.
*/
void *startgpswatchdog(void *ptr)
{
	//! Copy the data passed in to the thread.
	GPSLocation *destination = malloc(sizeof(GPSLocation));
	memcpy(destination, ptr, sizeof(GPSLocation));
    
	printf("destination after watchdog receive lat : %lf\n", destination->latitude);
    printf("destination after watchdog receive lon : %lf\n", destination->longitude);

    //! Thread results for the GPS Threads.
    int gpsSetupThreadResult;
    int gpsNavigationThreadResult;
    
    char *message2 = "gps setup thread started";

    /* pthread functions return 0 when successful */
    printf("Attempting to create GPS setup thread\n");
    gpsSetupThreadResult = pthread_create(&gpsSetupThread, NULL, setupgps, (void*) message2);
    
    /* pthread_cond_wait(&watchdogCond, &watchdogMutex); /* Set watchdog to wait for mutex unlock */

    int data = 0;
    int loopCount = 0;
    
    //! Check for 10 seconds if the GPS IO returns good data.
    while(loopCount < 1000)
    {
        //! Check if the GPS IO thread reports good data and start the GPS nav thread.
        data = get_goodData();
        
        if (data == 1)
        {
            printf("Attempting to create GPS Navigation thread\n");
            gpsNavigationThreadResult = 
            pthread_create(&gpsNavigationThread, NULL, setupgpsnavigation, (void*) destination);
            break;
        }
        else
            usleep(20000);
    }
    
    //! As long as the GPS System is running, monitor the GPS Threads.
    while (gpsRunning == 1)
    {
		//killGPSIO();
		
        /*! pthread_kill(someThread, 0)
        * sending a zero to the thread will not kill the thread
        * using the return value it can check of the thread is dead 
        */
        
        if (pthread_kill(gpsSetupThread, 0) != 0)/* GPS Setup Thread is dead */
        {
            printf("GPS Setup Thread died a horrible death\nRessurecting....\n");
            
            int cancelResult;

            cancelResult = pthread_cancel( gpsNavigationThread ); /* cancel the nav thread */
            printf("cancel result is %d\n", cancelResult);
            while(cancelResult != 0)
            {
                printf(".....");
                cancelResult = pthread_cancel( gpsNavigationThread );
            }
                /* Create new thread for gps setup */
                gpsSetupThreadResult = pthread_create(&gpsSetupThread, NULL, setupgps, (void*) message2);

                while(loopCount < 1000)
                {
                    data = get_goodData();

                    if (data == 1)
                    {
                        printf("Attempting to create GPS Navigation thread\n");
                        gpsNavigationThreadResult = 
                        pthread_create(&gpsNavigationThread, NULL, setupgpsnavigation, (void*) destination);
                        break;
                    }
                    else
                        usleep(20000);
                }
        }

        if (pthread_kill(gpsNavigationThread, 0) != 0)
        {
            printf("GPS Navigation Thread was digitally destroyed\nReconstructing....\n");
            gpsNavigationThreadResult = 
            pthread_create(&gpsNavigationThread, NULL, setupgpsnavigation, (void*) destination);
        }
    }
    
    /* wait for the threads to finish */
    pthread_join(gpsSetupThread, NULL);
    pthread_join(gpsNavigationThread, NULL);   

	free(destination); /* clean the filth */ 
}

//! Setup the GPS IO Thread.
void *setupgps(void *ptr)
{
    GPSIO_ON_OFF = 1;

    char *message;
    message = (char *) ptr;
    printf("%s\n", message);
        
    setup_gps(UNO,57600);
}

//! Setup the GPS Navigation Thread.
void *setupgpsnavigation(void *ptr)
{
    printf("GPS Navigation Thread Started\n");
    
    GPSNAV_ON_OFF = 1;

    /* Point to the destination passed in as a void pointer*/
    GPSLocation *destination = (GPSLocation *) ptr;
    printf("destination after gps nav receive lat : %lf\n", destination->latitude);
    printf("destination after gps nav receive lon : %lf\n", destination->longitude);

     // struct point Destination = {-2,57.7053,11.9340};
     // gps_navigation(Destination);
    gps_navigation(destination);
}
/* GPS System Functions end here */

/* Indoor System Functions start here */

//!
/*!
*
*
*
*
*/
//void nav_runIndoorSystem(tile startTile, tile destinationTile)
void nav_runIndoorSystem(double startX, double startY, double destinationX, double destinationY)
{  
    struct thread_data *data = malloc(sizeof(struct thread_data));
        data->starttile.x = startX;
		data->starttile.y = startY;
        data->destinationtile.x = destinationX;
		data->destinationtile.y = destinationY;
        data->message = "Indoor system started";
        
	int indoorWatchdogThreadResult;
	
	printf("Starting indoor system watchdog\n");
	indoorWatchdogThreadResult = 
		pthread_create(&indoorWatchdogThread, NULL, startIndoorWatchdogThread, (void*) data);
	
	pthread_join(indoorWatchdogThread, NULL);
    
    free(data); /* clean the filth */
    
    printf("Switching off indoor system\n");
}

void *startIndoorWatchdogThread(void *ptr)
{
	/* Copy the data pointed to by ptr for thread security */	
	struct thread_data *data = malloc(sizeof(struct thread_data));
	memcpy(data, ptr, sizeof(struct thread_data));
	
	int indoorThreadResult;
		
    printf("Attempting to create indoor nav thread\n");
    indoorThreadResult = 
        pthread_create(&indoorNavigationThread, NULL, startIndoorNavigationSystem, (void*) data);
    
    /* duplicate the mutex variable for lock/unlock in while loop */
    int duplicateRunning = 1; 
    
    while(duplicateRunning == 1)
    {
        if (pthread_kill(indoorNavigationThread, 0) != 0)
        {
            
            printf("Indoor System quite unexpectedly\nRestarting...\n");
            
			/* Use the last current position to restart the thread*/
			data->starttile = roomPositionToTile(currPosition);
			
            indoorThreadResult = 
                pthread_create(&indoorNavigationThread, NULL, startIndoorNavigationSystem, (void*) data);
        }
        
        int result;
		
		/* 
		*lock the mutex when setting the value to the return 
		*of an accessor function in another module 
		*/
        result = pthread_mutex_lock(&indoorNavigationRunningMutex);
        duplicateRunning = indoorSystemRunning;
        result = pthread_mutex_unlock(&indoorNavigationRunningMutex);
    }
   
    //initPath(&startTile, &destinationTile);
    pthread_join(indoorNavigationThread, NULL);
    printf("indoor navigation system shut down\n");
    free(data); /* clean up */
}	

/* Function to be run in a pthread for indoor navigation */
void *startIndoorNavigationSystem(void *ptr)
{
	char *message;
    message = (char *) ptr;
    printf("%s\n", message);

	

    // printf("Started the indoor navigation tread\n");
    //     struct thread_data *data = (struct thread_data*) ptr;
    
	struct thread_data *data = malloc(sizeof(struct thread_data));
    // data->starttile.x = 1;
    // data->starttile.y = 1;
    // data->destinationtile.x = 9;
    // data->destinationtile.y = 5;
    // data->message = "Indoor system started";
    // 
    //     initPath(&data->starttile, &data->destinationtile);
    
    
    data->starttile.x = 1;
	data->starttile.y = 1;
    data->destinationtile.x = 9;
    data->destinationtile.y = 5;
	data->message = "Indoor system started";
	
	initManualStart(&data->starttile);
	receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
	receiveManualMovementCommand(6);
	receiveManualMovementCommand(6);
	receiveManualMovementCommand(6);
	receiveManualMovementCommand(6);
	receiveManualMovementCommand(6);
	receiveManualMovementCommand(6);
	receiveManualMovementCommand(6);
	receiveManualMovementCommand(6);
	receiveManualMovementCommand(6);
	receiveManualMovementCommand(7);
	receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    receiveManualMovementCommand(3);
    
    
    initManualToAuto(&data->destinationtile);
    
    int result;
    result = pthread_mutex_lock(&indoorNavigationRunningMutex);
    indoorSystemRunning = 0;
    result = pthread_mutex_unlock(&indoorNavigationRunningMutex);   
}

/* function to update the destination at any given time: GPS */
void nav_updateGPSDestination(GPSLocation *destination)
{
    /* send the new data to the path calculation system */
}

/* function to update an indoor destination */
void nav_updateIndoorDestination(int tileNumber, ThreeDWorld *world)
{
    /* send the new data to the path calculation system */
    int firstDimension = tileNumber / world->mapWidth;
    int secondDimension = tileNumber % world->mapWidth;
    
    /* 2 marks the tile as the destination. */
    world->representation[firstDimension][secondDimension] = 2;
    /* notify the path calculation to recheck the worldMap and recalculate. */
}

/* notify the path calculation a collision was found/ stop calculation */
void nav_collisionFound()
{
    /* notify the path calculation group */
}

/* notify the path calculation to recalculate */
void nav_collisionAvoided()
{
    /* notify the path calculation to recalculate */
}

// TODO: Ask UI group how they handle input, a basic command e.g. right or an angle moved
// functions for handling the manual user input
// void manualMovementCommand(moveCommand *_command)
// {
//  // TODO: notify the path calculation to stop creating movement orders.
//  sendMovementCommand(_command);
// }

/* function to create a collision object for the indoor system. */
void nav_createIndoorCollisionObject(int tileNumber, ThreeDWorld *world)
{
    if (world == NULL)
    {
        printf("Trying to modify an invalid world\n");
    }
    else /* update the tilemap represenation */
    {
        /* calculate the tile to add the collision object. */
        int firstDimension = tileNumber / world->mapWidth;
        int secondDimension = tileNumber % world->mapWidth;

        /* 1 marks the tile as having an object. */
        world->representation[firstDimension][secondDimension] = 1;

        /* notify the path calculation to recheck the worldMap and recalculate. */
        printf("Collision object created\n");
    }
}

void runProtocolThread()
{
	printf("Starting protocol read watchdog\n");
	
	int protocolReadThreadResult = 1;
	char *message = "protocol watchdog thread started";
	
	while(protocolReadThreadResult == 1)
	{
		protocolReadThreadResult = 
			pthread_create(&protocolWatchdogThread, NULL, protocolReadWatchdog, (void*) message);
	}
	
	pthread_join(protocolWatchdogThread, NULL);
}

void *protocolReadWatchdog(void *ptr)
{

	char *message;
    message = (char *) ptr;
    printf("%s\n", message);
	
	char *message2 = "protocol read thread started";
            
    int protocolReadThreadResult;
    
    printf("Attempting to create protocol reader thread\n");
    protocolReadThreadResult = pthread_create(&protocolReadThread, NULL, readProtocol, (void*) message2);
	
	while(monitoringProtocolThread != 0)
	{
		if(pthread_kill(protocolReadThread, 0) != 0)
    	{
        	printf("Protocol reader thread died\nRecreating......\n");
        
        	protocolReadThreadResult = 
        		pthread_create(&protocolReadThread, NULL, readProtocol, (void*) message);
    	}
	}
	
	/* Wait for the thread to finish */
	pthread_join(protocolReadThread, NULL);
}

//! Threaded function to read using protocol.
/*! This function is used to read data using the protocol
*   and pass on the data to the relevant functions for 
*   processing.
*
* @param ptr A void pointer that takes any data pointer.
* 
*/
void *readProtocol(void *ptr)
{
    char *message;
    message = (char *) ptr;
    printf("%s\n", message);

    protocolReading = 1;
	
    
    while(protocolReading == 1)
    {
        /* Add functions to read different bullshit from the protocol*/
		/* if (Read from protocol to get the confirmation of a movement command received == 1) 
		{
			int id = readManualMovementCommand from connectivity;
			sendManualMovementCommand(id); // Call the function from movement module
			
			set_MovementCommand_True();
		}
		*/
    }
}

/* Begin Kill functions */

/* Kill the gps system */
void nav_killGPSSystem()
{
    int result;
    result = pthread_mutex_lock(&watchdogMutex);
    gpsRunning = 0;
    result = pthread_mutex_unlock(&watchdogMutex);
	
	GPSIO_ON_OFF = 0;
	GPSNAV_ON_OFF = 0;
	
    /* result = pthread_cancel(gpsNavigationThread); */
}

void killGPSNavigationSystem()
{
	GPSNAV_ON_OFF = 0;
}

void killGPSIO()
{
	GPSIO_ON_OFF = 0;
}

// function to kill the navigation system e.g. the user wants only manual input.
void nav_killIndoorNavigationSystem()
{
	stopIndoorNavigation();
}

void killThread()
{
    printf("KILL ME\n");
    pthread_exit(NULL);
    printf("KILLED\n");
}

void killProtocolReadThread()
{
	monitoringProtocolThread = 0;
	
	int result;
	result = pthread_cancel(protocolReadThread);
	
	if(result == 0)
	{
		 /*end the protocol read monitoring loop */
		printf("Protocol read thread killed\n");
	}
	else
		printf("Failed to kill protocol read thread\n");
}

/* End kill functions */

/* Begin functions that are using the protocol */
void nav_sendAutoMovementCommand(struct movCommand *move)
{
    /* Add protocol functions to send to movement */	
}

void nav_sendManualMovementCommand(struct movCommand *move)
{
    /* 1:   Pause Auto movement command generation */
    /*      Extract or send movement command to nav system */
    /* 2:   Add protocol functions to send to movement */
    /* 3:   Unpause auto movement command generation */
}
/* End functions that are using the protocol */

/* Function for connectivity to call to pass on a movement command */
void nav_setMovementIdentifier(int id)
{
	printf("Received movement id:%d from connectivity\n", id);
	
	int result; /* Use the result for testing */
	
    result = pthread_mutex_lock(&movementIdMutex);
    nav_movementId = id;
	printf("nav_movementId is %d\n", nav_movementId);
    result = pthread_mutex_unlock(&movementIdMutex);
	
	result = pthread_mutex_lock(&newMovementMutex);
    nav_newMovement = 1;
	printf("nav_newMovement is %d in the setId function\n", nav_newMovement);
    result = pthread_mutex_unlock(&newMovementMutex);
	printf("\n");
}

void nav_setIndoorData(double startX, double startY, double destinationX, double destinationY)
{
	int result; /* Use the result for testing */
	
    result = pthread_mutex_lock(&indoorStartXMutex);
    nav_runIndoorStartX = startX;
    result = pthread_mutex_unlock(&indoorStartXMutex);

	result = pthread_mutex_lock(&indoorStartYMutex);
    nav_runIndoorStartY = startY;
    result = pthread_mutex_unlock(&indoorStartYMutex);

	result = pthread_mutex_lock(&indoorEndXMutex);
    nav_runIndoorEndX = destinationX;
    result = pthread_mutex_unlock(&indoorEndXMutex);

	result = pthread_mutex_lock(&indoorEndYMutex);
    nav_runIndoorEndY = destinationY;
    result = pthread_mutex_unlock(&indoorEndYMutex);

	result = pthread_mutex_lock(&startIndoorMutex);
	nav_startIndoor = 1;
	result = pthread_mutex_unlock(&startIndoorMutex);
}

void nav_setOutdoorData(double destinationX, double destinationY)
{
	int result; /* Use the result for testing */
	
	result = pthread_mutex_lock(&startOutdoorMutex);
	nav_startOutdoor = 1;
	result = pthread_mutex_unlock(&startOutdoorMutex);
	
    result = pthread_mutex_lock(&gpsDestinationXMutex);
    nav_runGPSDestinationX = destinationX;
    result = pthread_mutex_unlock(&gpsDestinationXMutex);

	result = pthread_mutex_lock(&gpsDestinationYMutex);
    nav_runGPSDestinationY = destinationY;
    result = pthread_mutex_unlock(&gpsDestinationYMutex);
}

/* Begin interface:out functions for connectivity group */
void nav_sendCurrentIndoorPositionToGui(roomPosition *currentPosition) {
    
	*currPosition = *currentPosition; 

	printf("Drone is approximately at X: %f    Y: %f\n", currentPosition->lon,
    currentPosition->lat);
	/* Save the current position before sending it */
	/* Put connectivity library function here*/
}

void nav_sendCurrentOutdoorPositionToGui(GPSLocation *currentPosition)
{
    /* Put connectivity library function here */
    /* Pass in currentOutdoorPosition */
}

void nav_sendOutdoorPathToGui(GPSLocation **path)
{
    /* Put connectivity library function here*/
}

void nav_sendIndoorPathToGui(positionList *path, int8_t type)
{
    int i = 0;
    /* Put connectivity library function here*/
    for(i = 0; i < path->num; i++){
        printf("X: %f   Y: %f\n", path->list[i].lon, path->list[i].lat);
    }
    if (type == 1) {
        free(path->list);
    }
    free(path);
}
/* End interface:out functions for connectivity group */

/* Helper Functions */
static tile roomPositionToTile(roomPosition *current)
{
    tile temp;
    temp.x = (current->lon - TILE_CENTER) / CENTIMETRES_PER_TILE;
    temp.y = (current->lat - TILE_CENTER) / CENTIMETRES_PER_TILE;
    return temp;
}

// int main(int argc, char **argv) {
// 
// 
// /*
//  	GPSLocation *Destination = malloc(sizeof(GPSLocation));
//  	Destination->latitude = 57.7053;
//  	Destination->longitude = 11.9340;
// 
// 	nav_runGpsSystem(Destination->latitude, Destination->longitude);
// */
// 	nav_init();
// 	nav_run();
// 
// 	//runProtocolThread();
// 	
//     // tile a, b;
//     // a.x = 1;
//     // a.y = 1;
//     // b.x = 9;
//     // b.y = 5;
//     // 
//     // nav_runIndoorSystem(a.x, a.y, b.x, b.y);
// 	
// 	
// 	
// 
//     return 0;
// }

int16_t nav_init(void)
{
	currPosition = malloc(sizeof(roomPosition));
    return 0;
}

//! Run function to start the navigation system.
/*! Run function that waits for a decision to start the
* 	indoor or gps(outdoor) systems.
*	
*	It reads using the protocol read functions and checks
*	the return values before starting the chosen system.
*
*/
int16_t nav_run(void)
{
	int conListenerThreadResult;
	char *message = "Connectivity Listener Started";
	conListenerThreadResult = 
		pthread_create(&connectivityListenerThread, NULL, startConnectivityListener, (void*) message);
		    
    int protocolReadThreadResult;
    char *message3 = "Protocol Read Thread Started";
    protocolReadThreadResult =
 		pthread_create(&protocolReadThread, NULL, readProtocol, (void*) message3);
	
	int indoorThreadResult;
	char *message2 = "Indoor Thread Started";
    indoorThreadResult = 
        pthread_create(&indoorNavigationThread, NULL, startIndoorNavigationSystem, (void*) message2);
		
	//nav_setIndoorData(1, 1, 9, 5);	
	
	/* duplicate the mutex variable for lock/unlock in while loop */
	/* used for checking if indoor system is running */
    int duplicateRunning = 1;

	int watching = 1;
	
	while(watching == 1)
	{
		if (pthread_kill(connectivityListenerThread, 0) != 0) /* Listener died */
		{
			printf("Connectivity Listener quite unexpectedly\nRestarting...\n");
			conListenerThreadResult = 
				pthread_create(&connectivityListenerThread, NULL, startConnectivityListener, (void*) message);
		}
		
		/* Monitor the indoor system */
		//if (duplicateRunning == 1 && pthread_kill(indoorNavigationThread, 0) != 0)
		if (indoorSystemRunning == 1 && pthread_kill(indoorNavigationThread, 0) != 0)
        {
            
            printf("Indoor System quite unexpectedly\nRestarting...\n");
            
			/* Use the last current position to restart the thread*/
			//data->starttile = roomPositionToTile(currPosition);
			
            indoorThreadResult = 
                pthread_create(&indoorNavigationThread, NULL, startIndoorNavigationSystem, (void*) message2);
        }

		if(pthread_kill(protocolReadThread, 0) != 0)
    	{
        	printf("Protocol reader thread died\nRecreating......\n");
        	protocolReadThreadResult = 
        		pthread_create(&protocolReadThread, NULL, readProtocol, (void*) message3);
    	}

		int result; /* Use for testing */

		/* 
		*   lock the mutex when setting the value to the return 
		*   of an accessor function in another module 
		*/
		result = pthread_mutex_lock(&indoorNavigationRunningMutex);
        duplicateRunning = indoorSystemRunning;
        result = pthread_mutex_unlock(&indoorNavigationRunningMutex);
	}
	
	/* Wait for the threads to finish */
	pthread_join(connectivityListenerThread, NULL);
	pthread_join(indoorNavigationThread, NULL);
	pthread_join(protocolReadThread, NULL);
	
	/* Destory the mutex variables */
	pthread_mutex_destroy(&watchdogMutex);
	pthread_mutex_destroy(&gpsDestinationYMutex);
 	

    return 0;
}