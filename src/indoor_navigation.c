/*
* indoor_navigation.c
*
*  Created on: 2 apr 2011
*      Author: Eric Britsman
*/
#include "path_structure.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define PRECISION 5
#define SLEEP_DURATION (0.3 * 1000000000)
#define ALGORITHM 0
#define CENTIMETRES_PER_SECOND 20

static int count, running;
static position_list route;

static struct timeval timer;
static progressive_node *first, *current;
// static progressive_node *first, *checkpoint, *current;
// checkpoint = path->path[path->num-1]

void insert_progressive_node() {
    
    if (first == 0) {
        first = calloc(1, sizeof(progressive_node));
        first->prev = 0;
        first->p = route.list[0];
        current = first;
        insert_progressive_node();
    }
    else {
        count++;

        progressive_node *temp;
        temp = calloc(1, sizeof(progressive_node));
        current->next = temp;
        temp->prev = current;
        current = temp;

        current->next = calloc(1, sizeof(progressive_node));
        current->next->p = route.list[count];
        current->next->next = 0;
    }
}

void free_progressive_list() {

    progressive_node *temp;

    while (first != 0) {
        temp = first->next;
        free(first);
        first = temp;
    }
}

void set_direction() {
    current->next->p.angle =
        atan2((current->next->p.lat - current->prev->p.lat),
        (current->next->p.lon - current->prev->p.lon));
}
void set_distance() {

    current->next->p.distance = (sqrt((current->next->p.lon -
        current->prev->p.lon) * (current->next->p.lon -
        current->prev->p.lon) + (current->next->p.lat -
        current->prev->p.lat) * (current->next->p.lat -
        current->prev->p.lat)));
}
void update_position() {
    struct timeval current_time;
    double change_x, change_y, time, microseconds;
    gettimeofday(&current_time, NULL);
    microseconds = (current_time.tv_usec - timer.tv_usec);
    if(microseconds != 0){
        microseconds = microseconds/1000000;
    }
    time = (current_time.tv_sec - timer.tv_sec) + microseconds;
    change_y = (time * CENTIMETRES_PER_SECOND) *
        sin(current->next->p.angle);
    change_x = (time * CENTIMETRES_PER_SECOND) *
        cos(current->next->p.angle);
    current->p.lon = current->prev->p.lon + change_x;
    current->p.lat = current->prev->p.lat + change_y;
}


void send_direction(double *angle) {
    //Give angle to core logic, so it can tell movement
    //which way we need to move.
    //N 90 E 180 S -90 W -180
    if(*angle > 0) {
        printf("Move at angle %.5f\n", -(*angle/ (M_PI/180)));
    }
    else {
        printf("Move at angle %.5f\n", *angle / (M_PI/180) + 180);
    }
}
void send_distance(double *distance) {
    //Send distance between two coords to corelogic
    printf("Go for %.5f cm.\n", *distance);
}
void send_position(pixel *pos){
    printf("Longitude = %f\nLatitude = %f\n", pos->lon, pos->lat);
}
void send_expected_path(position_list *path) {
    //Give corelogic the calculated path.
    printf("This is the path given by path calc.\nLines should be drawn between each point in list.\n");
}
// void send_actual_path(progressive_route *path){
void send_actual_path(progressive_node *first){
    //Give corelogic the finalized path after destination reached.
    printf("This is the path actually taken to until destination reached/nav interrupted.\n");
}
void send_stop(){
    //Tell corelogic to tell movement to stop (for when we arrive at destination).
    printf("Destination reached or indoor navigation interrupted.\n");
    send_actual_path(first);

    free_progressive_list();
}
//Send start and end point received from corelogic
//to path calculation.
void init_path(position start, position end){
    int counterUp;
    running = 1;
    count = 0;

    if(ALGORITHM == 0) {
        printf("Dijkstra\n");
        route = indoor_dijkstra(&start, &end);
    }
    else{
        printf("Astar\n");
        route = indoor_astar(&start, &end);
    }
    for(counterUp = 0; counterUp < route.num; counterUp++) {
        printf("final.x: %f ", route.list[counterUp].lon);
        printf("final.Y: %f\n", route.list[counterUp].lat);
    }
    printf("num: %d\n", route.num);
    
    // insert first node and next node for 
    // current destination calculation
    insert_progressive_node(); 
    
    send_expected_path(&route);
    navigate_path();

}
void reset_timer() {
    gettimeofday(&timer, NULL);
}
void compare_tile(){
    if((current->p.lon - TILE_CENTER)/CENTIMETRES_PER_TILE
        != (current->prev->p.lon - TILE_CENTER)/CENTIMETRES_PER_TILE
        || (current->p.lat - TILE_CENTER)/CENTIMETRES_PER_TILE
        != (current->prev->p.lat - TILE_CENTER)/CENTIMETRES_PER_TILE)
    {
        current->prev = current;
    }
}
void recalc(){
    position a, b;
    a.x = (current->prev->p.lon - TILE_CENTER) / CENTIMETRES_PER_TILE;
    a.y = (current->prev->p.lat - TILE_CENTER) / CENTIMETRES_PER_TILE;
    b.x = (route.list[route.num-1].lon - TILE_CENTER) / CENTIMETRES_PER_TILE;
    b.y = (route.list[route.num-1].lat - TILE_CENTER) / CENTIMETRES_PER_TILE;
    route = indoor_dijkstra(&a, &b);
    count=1;
    current->next->p = route.list[count];
    running = 1;
    send_expected_path(&route);
    navigate_path();
}
void collision_avoided(double direction, struct timeval time){
    running = 0;
    timer = time;
    free(route.list);
    compare_tile();
    current->next->p.angle = direction;
    update_position();
    compare_tile();
    recalc();
}
int check(pixel a, pixel b){
    double diff_x, diff_y;
    diff_x = fabs(a.lon - b.lon);
    diff_y = fabs(a.lat - b.lat);
    if ((diff_x + diff_y) < PRECISION){
        return 1;
    }
    else{
        return 0;
    }
}
void navigate_path(){
    int bool;
    struct timespec wait;
    wait.tv_sec = 0;
    wait.tv_nsec = SLEEP_DURATION;
    reset_timer();
    set_direction();
    set_distance();
    send_direction(&current->next->p.angle);
    send_distance(&current->next->p.distance);

    while(running == 1){//Infinite loop until it reaches point or collision avoidance occurs.
        update_position();
        send_position(&current->p);

        if(check(current->p, current->next->p) == 1){
            if(check(current->p, route.list[route.num-1]) == 1){
                current->prev->p = current->next->p;
                count++;
                free_progressive_list();
                send_stop();
                bool = 0;
                break;
            }
            else{
                insert_progressive_node();
                bool = 1;
                break;
            }
        }
        nanosleep(&wait, NULL);
    }
    if(bool == 1 && running == 1){
        navigate_path();
    }
}

int main(){
    position a, b;
    a.x = 1;
    a.y = 1;
    b.x = 9;
    b.y = 5;
    init_path(a, b);
    // return 1;
    return 0;
}
