#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "nav_handlemanualcommands.h"
<<<<<<< HEAD

#define DISTANCE_PER_COMMAND 20
#define ANGLE_PER_COMMAND 5
#define HEIGHT_PER_COMMAND 5

#define SLEEP_DURATION (0.1 * 1000000000)

// Get these from nav_movementcommands.h
// #define FORWARD 3
// #define BACK 5
// #define LEFT 7
// #define RIGHT 9
// #define UP 11
// #define DOWN 13

static int32_t newCommand[3];
static manualCommand *first;
static manualCommand *last;
static int8_t bool;

int8_t ch;

static void queueManualCommand(int n) {
=======
#include "nav_movementcommands.h"

#define DISTANCE_PER_COMMAND 10
#define ANGLE_PER_COMMAND 10
#define HEIGHT_PER_COMMAND 10

#define SLEEP_DURATION (0.1 * 1000000000)


static int16_t newCommand[4];
static manualCommand *first;
static manualCommand *last;
static uint8_t bool;
static uint8_t destinationSet;
static roomPosition checkpoint;

uint8_t ch;

/*Keep the thread running until it is killed externally*/
void initManualNavigation(void) {
    for(;;) {
        ;
    }
}
static void queueManualCommand(int16_t n) {
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    manualCommand  *temp;

    temp = calloc(1, sizeof(manualCommand));
    temp->value = n;

    if (first == 0) {
        first = temp;
        newCommand[0] = 0; // Altitude
        newCommand[1] = 0; // Distance
        newCommand[2] = 0; // Angle
<<<<<<< HEAD
=======
        newCommand[3] = 0; // Order
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
        bool = 1;
    }
    else {
        last->next = temp;
    }
    last = temp;
    temp->next = 0;
}

<<<<<<< HEAD
void freeManualCommandList(void) {
=======
static void freeManualCommandList(void) {
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    manualCommand *temp = 0;
    while (first != 0) {
        temp = first->next;
        free(first);
        first = temp;
    }
}

<<<<<<< HEAD
int8_t commandHandled (void) {
=======
uint8_t commandHandled (void) {
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    return ch;
}

static void calculateNewCommand(void) {
    manualCommand *temp;
    temp = last;
    while ( temp != NULL)
    {
        switch (temp->value) {
            case FORWARD:
                newCommand[1] += DISTANCE_PER_COMMAND;
                break;
            case BACK:
                newCommand[2] += 180;
                break;
            case LEFT:
                newCommand[2] -= ANGLE_PER_COMMAND;
                break;
            case RIGHT:
                newCommand[2] += ANGLE_PER_COMMAND;
                break;
            case UP:
                newCommand[0] += HEIGHT_PER_COMMAND;
                break;
            case DOWN:
                newCommand[0] -= HEIGHT_PER_COMMAND;
                break;
<<<<<<< HEAD
=======
            case LAND:
                newCommand[3] = 2;
                break;
            case TAKE_OFF:
                newCommand[0] = 50;
                break;    
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
            default:
                printf("Not a valid command. \n");
                break;
        }
        temp = temp->next;
    }
}

<<<<<<< HEAD
static void trackChangedPosition(void) {
    
}

void receiveManualMovementCommand(int32_t command) {
    
=======
static void calculateNewPosition(int32_t angle, int32_t distance) {
    checkpoint.lon += distance * cos(angle);
    checkpoint.lat += distance * sin(angle);
}

static void updateManualPosition(void) {    

    checkpoint.angle += newCommand[2] * (M_PI / 180);
    checkpoint.distance = newCommand[1];
    
    printf("Current angle and distance: %f\t %f\n", checkpoint.angle, checkpoint.distance);
    
    calculateNewPosition(checkpoint.angle, checkpoint.distance);
    
    printf("Current position: lon %f\t lat %f\n\n", checkpoint.lon, checkpoint.lat);
    
}

void collisionOverManual(int32_t angle) {
    // Abort all manual commands from user
    freeManualCommandList();
    
    checkpoint.angle = (angle - TRUE_NORTH) * (M_PI / 180);
    checkpoint.distance = AVOID_DISTANCE;
    
    calculateNewPosition(checkpoint.angle, checkpoint.distance);
}

void initManualStart(tile *start) {
    checkpoint.lon = (start->x * CENTIMETRES_PER_TILE) + TILE_CENTER;
    checkpoint.lat = (start->y * CENTIMETRES_PER_TILE) + TILE_CENTER;
}

void initManualToAuto(tile *end) {
    
    if (destinationSet == 0) {
        destinationSet = 1;
    }
    
    // Get the position of current tile center
    int16_t currentTileCenterX;
    if (((int16_t)(checkpoint.lon) % TILE_CENTER) >= TILE_CENTER / 2) {
        currentTileCenterX = (int16_t)(checkpoint.lon) - (int16_t)(checkpoint.lon) % TILE_CENTER;
    }
    else {
        currentTileCenterX = (int16_t)(checkpoint.lon) + (int16_t)(checkpoint.lon) % TILE_CENTER;
    }
    int16_t currentTileCenterY;
    if (((int16_t)(checkpoint.lat) % TILE_CENTER) >= TILE_CENTER / 2) {
        currentTileCenterY = (int16_t)(checkpoint.lat) - (int16_t)(checkpoint.lat) % TILE_CENTER;
    }
    else {
        currentTileCenterY = (int16_t)(checkpoint.lat) + (int16_t)(checkpoint.lat) % TILE_CENTER;
    }
        
    // Calculate different in X and Y to tile center
    int16_t changeX = checkpoint.lon - currentTileCenterX;
    int16_t changeY = checkpoint.lat - currentTileCenterY;
    
    
    // Calculate distance to current tile center
    int16_t distance = (sqrt(changeX * changeX + changeY * changeY));
    
    // Calculate angle to current tile center
    int16_t angle = ((int16_t)(
        (atan2((double)changeY, (double)changeX) / (M_PI/180))
        )) + TRUE_NORTH;
    if (angle > 359) {
        angle -= 360;
    }
    
    printf("Distance to tile center: %d\n", distance);
    printf("Angle to tile center: %d\n", angle);
    
    // Attempt to send movement command to tile center
    for (;;) {
        if (commandHandled() == 0) {
            // sendManualMovementCommand(0, distance, angle, 0);
            sendautomovementcommand(0, 0, distance, angle);
            break;
        }
    }
    
    // Init path with newStart
    tile newStart;
    newStart.x = currentTileCenterX / CENTIMETRES_PER_TILE;
    newStart.y = currentTileCenterY / CENTIMETRES_PER_TILE;    
    initPath(&newStart, end);
}

void receiveManualMovementCommand(uint8_t command) {
    ch = 0; //for testing
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    struct timespec t;
    t.tv_sec = 0;
    t.tv_nsec = SLEEP_DURATION;
    
<<<<<<< HEAD
=======
    if (getRunning() == 1) {
        checkpoint = getCurrentPosition();
        stopIndoorNavigation();
        destinationSet = 1;
        
    }
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
    queueManualCommand(command);
    calculateNewCommand();
    
    if (bool == 1) {
        for (;;) {
            if (commandHandled() == 1) {
                nanosleep(&t , NULL);
                bool = 0;
            }
            else {
<<<<<<< HEAD
                printf("%d\t %d\t %d\n", newCommand[0], newCommand[1], newCommand[2]);
                // nav_sendManualMovementCommand(newCommand[0], newCommand[1], newCommand[2]);
                // track current position for indoor system
                trackNewPosition();
                
=======
                // printf("Height %d\t Distance %d\t Angle %d\n", newCommand[0], newCommand[1], newCommand[2]);
                sendManualMovementCommand(newCommand[0], newCommand[1], newCommand[2], newCommand[3]);
                
                updateManualPosition();
                
                // resume auto
                if (destinationSet == 1) {
                    initManualToAuto(getDestinationTile());
                }
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
                
                freeManualCommandList();
                break;
            }
        }
    }
}

 
// int main(void) {
//     // difficult to test the change from 1 to 0, use if instead of while
//     ch = 1;
//     receiveManualMovementCommand(3);
//     receiveManualMovementCommand(3);
//     receiveManualMovementCommand(7);
//     receiveManualMovementCommand(7);
//     ch = 0;
//     receiveManualMovementCommand(3);
//     receiveManualMovementCommand(5);    
//     return 0;
<<<<<<< HEAD
// }
=======
// }
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
