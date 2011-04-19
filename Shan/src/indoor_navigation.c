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
static int count, running;
static position_list route;
static progressive_route current;
static int map[MAP_Y][MAP_X] = {
{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},	// 0
{5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},
{5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5},
{5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 5},
{5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5},	// 4
{5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5},
{5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5},
{5, 5, 5, 5, 5, 5, 1, 5, 5, 1, 1, 5},
{5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5},	// 8
{5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5},
{5, 1, 1, 1, 1, 1, 5, 5, 5, 1, 1, 5},
{5, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 5},
{5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},	// 12
{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}
};

//Send start and end point received from UI
//to Dijkstra calculation.
void init_path(position start, position end){
	int counterUp;
	running = 1;
	count = 1;
	current.num = 1;
	route = indoor_dijkstra(&start, &end, map);
		for(counterUp = 0; counterUp < route.num; counterUp++)
		{
			printf("final.x: %f ", route.list[counterUp].lon);
			printf("final.Y: %f\n", route.list[counterUp].lat);
		}
		printf("num: %d\n", route.num);
		current.path = realloc(current.path,sizeof(point) * 2);
		current.path[0] = route.list[0];
		current.ending_point = route.list[route.num-1];
		current.current_destination = route.list[count];
		current.current_point = route.list[0];
		navigate_path();
}
void send_direction(double *angle){
	//Tell movement which way we need to move.
	printf("Move at angle %.5f\n", *angle);
}
void send_distance(double *distance){
	//Send distance between two coords
	//so UI can display it.
	printf("Go for %.5f cm.\n", *distance);
}
void send_position(point *pos){
	printf("Longitude = %f\nLatitude = %f\n", pos->lon, pos->lat);
}
void send_stop(){
	//Tell movement to stop (for when we arrive at destination).
	printf("Destination reached.\n");
}
void send_ui_info(point *path){
	//Give ui the path they should draw.
}
void reset_timer() {
	gettimeofday(&current.timer, NULL);
}
void compare_tile(){
	if((int)(current.current_point.lon) != (int)(current.path[current.num-1].lon)
	|| (int)(current.current_point.lat) != (int)(current.path[current.num-1].lat))
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
	a.x = (current.path[current.num-1].lon/CENTIMETRES_PER_TILE) - TILE_CENTER;
	a.y = (current.path[current.num-1].lat/CENTIMETRES_PER_TILE) - TILE_CENTER;
	b.x = (current.ending_point.lon/CENTIMETRES_PER_TILE) - TILE_CENTER;
	b.y = (current.ending_point.lat/CENTIMETRES_PER_TILE) - TILE_CENTER;
	route = indoor_dijkstra(&a, &b, map);
	count=1;
	current.current_destination = route.list[count];
	running = 1;
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
				free(current.path);
				free(route.list);
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
int main(){
	position a, b;
	a.x = 1;
	a.y = 1;
	b.x = 9;
	b.y = 5;
	init_path(a, b);
	return 1;
}
