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
static int count, running;
static position_list route;
static progressive_route current;

void send_direction(double *angle){
	//Give angle to core logic, so it can tell movement
	//which way we need to move.
	printf("Move at angle %.5f\n", *angle);
}
void send_distance(double *distance){
	//Send distance between two coords to corelogic
	printf("Go for %.5f cm.\n", *distance);
}
void send_position(point *pos){
	printf("Longitude = %f\nLatitude = %f\n", pos->lon, pos->lat);
}
void send_expected_path(position_list *path){
	//Give corelogic the calculated path.
	printf("This is the path given by path calc.\nLines should be drawn between" +
	"each point in list.\n");
}
void send_actual_path(progressive_route *path){
	//Give corelogic the finalized path after destination reached.
	printf("This is the path actually taken to until destination reached/" +
	"nav interrupted.\n");
}
void send_stop(){
	//Tell corelogic to tell movement to stop (for when we arrive at destination).
	printf("Destination reached or indoor navigation interrupted.\n");
	send_actual_path(&current);
	free(current.path);
	free(route.list);
}
//Send start and end point received from corelogic
//to path calculation.
void init_path(position start, position end){
	int counterUp;
	running = 1;
	count = 1;
	current.num = 1;
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
		current.path = realloc(current.path,sizeof(point) * 2);
		current.path[0] = route.list[0];
		current.ending_point = route.list[route.num-1];
		current.current_destination = route.list[count];
		current.current_point = route.list[0];
		send_expected_path(&route);
		navigate_path();
}
void reset_timer() {
	gettimeofday(&current.timer, NULL);
}
void compare_tile(){
	if((current.current_point.lon - TILE_CENTER)/CENTIMETRES_PER_TILE
	!= (current.path[current.num-1].lon - TILE_CENTER)/CENTIMETRES_PER_TILE
	|| (current.current_point.lat - TILE_CENTER)/CENTIMETRES_PER_TILE
	!= (current.path[current.num-1].lat - TILE_CENTER)/CENTIMETRES_PER_TILE)
	{
	current.path[current.num] = current.current_point;
	current.path[current.num].angle = current.current_destination.angle;
	current.num++;
	current.path = realloc(current.path, sizeof(point) *
	(current.num+1));
    	if(current.path == NULL){
    		printf("!!!!!\n");
    		send_stop();
    	}
	}
}
void recalc(){
	position a, b;
	a.x = (current.path[current.num-1].lon - TILE_CENTER) / CENTIMETRES_PER_TILE;
	a.y = (current.path[current.num-1].lat - TILE_CENTER) / CENTIMETRES_PER_TILE;
	b.x = (current.ending_point.lon - TILE_CENTER) / CENTIMETRES_PER_TILE;
	b.y = (current.ending_point.lat - TILE_CENTER) / CENTIMETRES_PER_TILE;
	route = indoor_dijkstra(&a, &b);
	count=1;
	current.current_destination = route.list[count];
	running = 1;
	send_expected_path(&route);
	navigate_path();
}
void collision_avoided(double direction, struct timeval time){
	running = 0;
	current.timer = time;
	free(route.list);
	compare_tile();
	current.current_destination.angle = direction;
	update_position(&current);
	compare_tile();
	recalc();
}
int check(point a, point b){
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
	set_direction(&current);
	set_distance(&current);
	send_direction(&current.current_destination.angle);
	send_distance(&current.current_destination.distance);
	while(running == 1){//Infinite loop until it reaches point or collision avoidance occurs.
		printf("%d\n", current.num);
		update_position(&current);
		send_position(&current.current_point);
		if(check(current.current_point, current.current_destination) == 1){
			if(check(current.current_point, current.ending_point) == 1){
				current.path[current.num] = current.current_destination;
				current.num++;
				count++;
				current.path = realloc(current.path, sizeof(point) * (current.num+1));
			    	if(current.path == NULL){
			    		printf("!!!!!\n");
			    		send_stop();
			    	}
				send_stop();
				bool = 0;
				break;
			}
			else{
			   current.path[current.num] = current.current_destination;
			   current.num++;
			   count++;
			   printf("%d\n", sizeof(position) * (current.num+1));
			   current.path = realloc(current.path, sizeof(point) * (current.num+1));
			    	if(current.path == NULL){
			    		printf("!!!!!\n");
			    		send_stop();
			    	}
			   current.current_destination = route.list[count];
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
/*int main(){
	position a, b;
	a.x = 1;
	a.y = 1;
	b.x = 9;
	b.y = 5;
	init_path(a, b);
	return 1;
}*/
