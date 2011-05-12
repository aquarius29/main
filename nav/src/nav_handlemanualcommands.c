#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "nav_handlemanualcommands.h"

#define DISTANCE_PER_COMMAND 20
#define ANGLE_PER_COMMAND 5
#define HEIGHT_PER_COMMAND 5

#define SLEEP_DURATION (0.1 * 1000000000)

#define FORWARD 3
#define BACK 5
#define LEFT 7
#define RIGHT 9
#define UP 11
#define DOWN 13

static int newCommand[3];
static manualCommand *first;
static manualCommand *last;

int ch;

static void queueManualCommand(int n) {
    manualCommand  *temp;

    temp = calloc(1, sizeof(manualCommand));
    temp->value = n;

    if (first == 0) {
        first = temp;
        newCommand[0] = 0; // Altitude
        newCommand[1] = 0; // Distance
        newCommand[2] = 0; // Angle
    }
    else {
        last->next = temp;
    }
    last = temp;
    temp->next = 0;
}

void freeManualCommandList(void) {
    manualCommand *temp = 0;
    while (first != 0) {
        temp = first->next;
        free(first);
        first = temp;
    }
}

int8_t commandHandled (void) {
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
            default:
                printf("Not a valid command. \n");
                break;
        }
        temp = temp->next;
    }
}

void receiveManualMovementCommand(int command) {
    
    struct timespec t;
    t.tv_sec = 0;
    t.tv_nsec = SLEEP_DURATION;
    
    queueManualCommand(command);
    calculateNewCommand();
    
    for (;;) {
        if (commandHandled() == 1) {
            nanosleep(&t , NULL);
        }
        else {
            printf("%d\t %d\t %d\n", newCommand[0], newCommand[1], newCommand[2]);
            // nav_sendManualMovementCommand(newCommand[0], newCommand[1], newCommand[2]);
            // track current position for indoor system
            freeManualCommandList();
            break;
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
// }