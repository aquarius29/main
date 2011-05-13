/*
 * indoor_navigation.c
 *
 *  Created on: 2 apr 2011
 @Author Eric Britsman
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "nav_indoorstructure.h"
//#include "movementcommands.h"

#define PRECISION 5
#define SLEEP_DURATION (0.05 * 1000000000)
#define ALGORITHM 0
#define TRUE_NORTH 100 + 90
#define AVOID_DISTANCE 100
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
    current->next = calloc(1, sizeof(progressiveNode));
    current->next->p = route.list[count];
    current->next->prev = current;
    current->next->next = 0;
    count++;
}
static void insertProgressiveNode(void) {
    current->next->p = route.list[count];
    current->next->prev = current;
    current = current->next;
    insertCurrentDestinationNode();
}
static void insertInterruptedNode(void) {
    current->next = realloc(1, sizeof(progressiveNode));
    current->next->p = current->p;
    current->next->prev = current;
    current = current->next;
    current->next = 0;
}
static void freeProgressiveList(void) {
    progressiveNode *temp = 0;
    while (first != 0) {
        temp = first->next;
        free(first);
        first = temp;
    }
}
static void setDirection(void) {
	printf("%f    %f\n", current->next->p.lon, current->next->p.lat);
    current->next->p.angle = ((int32_t)((atan2((double)(current->next->p.lat -
    current->prev->p.lat), (double)(current->next->p.lon -
    current->prev->p.lon)) / (M_PI/180)))) * (M_PI/180);
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
    double changeX = 0;
    double changeY = 0;
    double time = 0;
    double microseconds = 0;
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

//temp function until we actually read from protocol
static int8_t commandHandled (void) {
    return 1;
}
static void sendCommand(void) {
    setDirection();
    setDistance();
    int32_t angle = (current->next->p.angle / (M_PI/180)) + TRUE_NORTH;
    if (angle > 359) {
        angle -= 360;
    }
    printf("Move at angle %d\n", angle);
    /*sendautomovementcommand(1, SAFE_HEIGHT, current->next->p.distance,
    angle);*/
    for (;;) {
        int8_t bin = commandHandled();
        if (bin == 1) {
            navigatePath();
            break;
        }
    }
}
static void sendPosition(roomPosition *pos) {
    // printf("Longitude = %d\tLatitude = %d\n", pos->lon, pos->lat);
    //nav_sendCurrentIndoorPositionToGui(pos);
}
static void sendExpectedPath(positionList *path) {
    /* Free path & path->list in corelogic */
    //path = realloc(path, sizeof(positionList));
    printf("This is the path given by path calc.\n");
    printf("Lines should be drawn between each point in list.\n");
    //nav_sendIndoorPathToGui(path)
}
static void sendActualPath(progressiveNode *first) {
    /* Free path & path->list in corelogic */
   /* progressiveNode temp = *first;
    positionList *path = malloc(sizeof(positionList));
    path->num = 1;
    path->list = malloc(sizeof(pixel) * 2);
    path->list[0] = temp.p;
    // creating positionList from linked list, must be freed in UI.
    while (temp.next != 0) {
        path->list[path->num] = temp.next->p;
        path->num++;
        path->list = realloc(path->list, sizeof(pixel) * path->num + 1);
        temp = *temp.next;
    }
    */
    //Give corelogic the finalized path after destination reached.
    printf("This is the path actually taken until ");
    printf("destination reached/nav interrupted.\n");
    //nav_sendIndoorPathToGui(path);
    }
void stopIndoorNavigation(void) {
    //Tell corelogic to tell movement to stop
    printf("Destination reached or indoor navigation interrupted.\n");
    running = 0;
    sendActualPath(first);
    freeProgressiveList();
    free(route.list);
}
//Send start and end point received from corelogic
//to path calculation.
void initPath(tile *start, tile *end) {
    int32_t counterUp = 0;
    running = 1;
    count = 0;
    // sendautomovementcommand(0, SAFE_HEIGHT, 0, 0);
    if (ALGORITHM == 0) {
        printf("Dijkstra\n");
        route = indoorDijkstra(start, end);
    }
    else {
        printf("Astar\n");
        route = indoorAstar(start, end);
    }
    for (counterUp = 0; counterUp < route.num; counterUp++) {
        printf("final.x: %f ", route.list[counterUp].lon);
        printf("final.Y: %f\n", route.list[counterUp].lat);
    }
    printf("num: %d\n", route.num);
    // insert first node and next node for current destination calculation
    first = calloc(1, sizeof(progressiveNode));
    first->p = route.list[count];
    first->prev = 0;
    current = first;
    insertCurrentDestinationNode();
    insertProgressiveNode();
    sendExpectedPath(&route);
    sendCommand();
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
    tile a;
    tile b;
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
    sendCommand();
}
void collisionAvoided(double direction) {
    double changeX = 0;
    double changeY = 0;
    running = 0;
    free(route.list);
    compareTile();
    current->next->p.angle = direction;
    changeY = AVOID_DISTANCE * sin(current->next->p.angle);
    changeX = AVOID_DISTANCE * cos(current->next->p.angle);
    current->p.lon = current->prev->p.lon + changeX;
    current->p.lat = current->prev->p.lat + changeY;
    compareTile();
    recalc();
}
void getPositionAfterManual(int32_t direction, int32_t distance) {
    changeX = distance * cos(direction);
    changeY = distance * sin(direction);
    current->p.lon = current->prev->p.lon + changeX;
    current->p.lat = current->prev->p.lat + changeY;
}

static int32_t check(roomPosition a, roomPosition b){
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
    int32_t bool = 0;
    struct timespec wait;
    wait.tv_sec = 0;
    wait.tv_nsec = SLEEP_DURATION;
    resetTimer();
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
        sendCommand();
    }
}
/*int main(){
    tile a, b;
    a.x = 1;
    a.y = 1;
    b.x = 9;
    b.y = 5;
    initPath(&a, &b);
    return 0;
}*/
