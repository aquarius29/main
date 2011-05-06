/*
* indoor_navigation.c
*
*  Created on: 2 apr 2011
*      Author: Eric Britsman
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "nav_indoorstructure.h"
#include "movementcommands.h"

#define PRECISION 5
#define SLEEP_DURATION (0.05 * 1000000000)
#define ALGORITHM 0
#define CENTIMETRES_PER_SECOND 100
#define SAFE_HEIGHT 200 //200 cm

static void navigatePath(void);
static int32_t count;
static int32_t running;
static positionList route;
static struct timeval timer;
static progressiveNode *first;
static progressiveNode *current;

static void insertCurrentDestinationNode(void) {
    count++;
    current->next = calloc(1, sizeof(progressiveNode));
    current->next->p = route.list[count];
    current->next->prev = current;
    current->next->next = 0;
}

static void insertCurrentDestinationNode(void) {
    count++;
    current->next = calloc(1, sizeof(progressiveNode));
    current->next->p = route.list[count];
    current->next->prev = current;
    current->next->next = 0;
}

static void insertProgressiveNode(void) {
    if (first == 0) {
        first = calloc(1, sizeof(progressiveNode));
        first->p = route.list[count];
        first->prev = 0;
        current = first;
        insertCurrentDestinationNode();
        insertProgressiveNode();
    }
    else {
        current->next->p = route.list[count];
        current->next->prev = current;
        current = current->next;
        insertCurrentDestinationNode();
    }
}

static void freeProgressiveList(void) {
    progressiveNode *temp;
    while (first != 0) {
        temp = first->next;
        free(first);
        first = temp;
    }
}
static void setDirection(void) {
    current->next->p.angle = atan2((current->next->p.lat -
    current->prev->p.lat), (current->next->p.lon - current->prev->p.lon));
}
static void setDistance(void) {
    current->next->p.distance = (sqrt((current->next->p.lon -
    current->prev->p.lon) * (current->next->p.lon -
    current->prev->p.lon) + (current->next->p.lat -
    current->prev->p.lat) * (current->next->p.lat -
    current->prev->p.lat)));
}
static void updatePosition(void) {
    struct timeval current_time;
    double changeX;
    double changeY;
    double time;
    double microseconds;
    gettimeofday(&current_time, NULL);
    microseconds = (current_time.tv_usec - timer.tv_usec);
    if (microseconds != 0) {
        microseconds = microseconds/1000000;
    }
    time = (current_time.tv_sec - timer.tv_sec) + microseconds;
    changeY = (time * CENTIMETRES_PER_SECOND) * sin(current->next->p.angle);
    changeX = (time * CENTIMETRES_PER_SECOND) * cos(current->next->p.angle);
    current->p.lon = current->prev->p.lon + changeX;
    current->p.lat = current->prev->p.lat + changeY;
}
static void sendCommand(void) {
	double angle;
    //N 90 E 180 S -90 W -180
    if (current->next->p.angle > 0) {
    	angle = -(current->next->p.angle / (M_PI / 180));
        printf("Move at angle %.5f\n", angle);
    }
    else {
    	angle = current->next->p.angle / (M_PI/180) + 180;
        printf("Move at angle %.5f\n", current->next->p.angle / (M_PI / 180) +
        180);
    }
    // sendautomovementcommand(3, SAFE_HEIGHT, current->next->p.distance, angle);
}
static void sendPosition(pixel *pos) {
    printf("Longitude = %d\tLatitude = %d\n", pos->lon, pos->lat);
}
static void sendExpectedPath(positionList *path) {
    //Give corelogic the calculated path.
    printf("This is the path given by path calc.\n");
    printf("Lines should be drawn between each point in list.\n");
}
static void sendActualPath(progressiveNode *first) {
    //Give corelogic the finalized path after destination reached.
    printf("This is the path actually taken to until ");
    printf("destination reached/nav interrupted.\n");
}
void stopIndoorNavigation(void) {
    //Tell corelogic to tell movement to stop
    printf("Destination reached or indoor navigation interrupted.\n");
    running = 0;
    sendActualPath(first);
    freeProgressiveList();
}
//Send start and end point received from corelogic
//to path calculation.
void initPath(position *start, position *end) {
    int32_t counterUp;
    running = 1;
    count = 0;
    // sendautomovementcommand(1, SAFE_HEIGHT, 0, 0);
    if (ALGORITHM == 0) {
        printf("Dijkstra\n");
        route = indoorDijkstra(start, end);
    }
    else {
        printf("Astar\n");
        route = indoorAstar(start, end);
    }
    for (counterUp = 0; counterUp < route.num; counterUp++) {
        printf("final.x: %d ", route.list[counterUp].lon);
        printf("final.Y: %d\n", route.list[counterUp].lat);
    }
    printf("num: %d\n", route.num);
    // insert first node and next node for current destination calculation
    insertProgressiveNode();
    sendExpectedPath(&route);
    navigatePath();

}
static void resetTimer(void) {
    gettimeofday(&timer, NULL);
}
static void compareTile(void) {
    if ((current->p.lon - TILE_CENTER)/CENTIMETRES_PER_TILE !=
    (current->prev->p.lon - TILE_CENTER)/CENTIMETRES_PER_TILE ||
    (current->p.lat - TILE_CENTER)/CENTIMETRES_PER_TILE !=
    (current->prev->p.lat - TILE_CENTER)/CENTIMETRES_PER_TILE)
    {
        current->prev = current;
    }
}
static void recalc(void) {
    position a;
    position b;
    a.x = (current->prev->p.lon - TILE_CENTER) / CENTIMETRES_PER_TILE;
    a.y = (current->prev->p.lat - TILE_CENTER) / CENTIMETRES_PER_TILE;
    b.x = (route.list[route.num-1].lon - TILE_CENTER) / CENTIMETRES_PER_TILE;
    b.y = (route.list[route.num-1].lat - TILE_CENTER) / CENTIMETRES_PER_TILE;
    if (ALGORITHM == 0) {
        printf("Dijkstra\n");
        route = indoorDijkstra(&a, &b);
    }
    else {
        printf("Astar\n");
        route = indoorAstar(&a, &b);
    }
    count = 1;
    current->next->p = route.list[count];
    running = 1;
    sendExpectedPath(&route);
    navigatePath();
}
void collisionAvoided(double direction, struct timeval time) {
    running = 0;
    timer = time;
    free(route.list);
    compareTile();
    current->next->p.angle = direction;
    updatePosition();
    compareTile();
    recalc();
}
static int32_t check(pixel a, pixel b){
    double diffX;
    double diffY;
    diffX = fabs(a.lon - b.lon);
    diffY = fabs(a.lat - b.lat);
    if ((diffX + diffY) < PRECISION){
        return 1;
    }
    else{
        return 0;
    }
}
static void navigatePath(void){
    int32_t bool;
    struct timespec wait;
    wait.tv_sec = 0;
    wait.tv_nsec = SLEEP_DURATION;
    resetTimer();
    setDirection();
    setDistance();
    sendCommand();
    
    /*
     *  Infinite loop until it either reaches point,collision avoidance occurs
     *  or indoor navigation is stopped externally.
     */
    while (running == 1) {
        updatePosition();
        sendPosition(&current->p);

        if (check(current->p, current->next->p) == 1) {
            if (check(current->p, route.list[route.num-1]) == 1) {
                count++;
                stopIndoorNavigation();
                bool = 0;
                break;
            }
            else {
                insertProgressiveNode();
                bool = 1;
                break;
            }
        }
        nanosleep(&wait, NULL);
    }
    if (bool == 1 && running == 1) {
        navigatePath();
    }
}
// 
// int main(){
//     position a, b;
//     a.x = 1;
//     a.y = 1;
//     b.x = 9;
//     b.y = 3;
//     initPath(&a, &b);
//     return 0;
// }
