/*
 * indoor_navigation.c
 *
 *  Created on: 2 apr 2011
 *      Author: Eric Britsman
 */
#include "path_structure.h"
#include <stdlib.h>
#include <stdio.h>
static int count, running;
static dijkstra_route route;
static progressive_route current;

//Send start and end point received from UI
//to Dijkstra calculation.
void init_path(position start, position end){
	running = 1;
	/*route = calc_path(start, end);
	(get first calculated dijkstra path here.)*/
	current.path = realloc(current.path,
	(sizeof(progressive_route) * 2));
	count = 1;
	current.num = 1;
	current.path[0] = route.path[0];
	current.ending_point = route.path[route.num-1];
	current.current_destination = route.path[count];
	current.current_point = route.path[0];
	navigate_path();
}
void send_direction(double *angle){
	//Tell movement which way we need to move.
	printf("Go .5%f.\n", *angle);
}
void send_distance(double *distance){
	//Send distance between two coords
	//so UI can display it.
	printf("Go for .5%f cm.\n", *distance);
}
void send_position(position *pos){
	printf("Longitude = %f\nLatitude = %f\n", pos->lon, pos->lat);
}
void send_stop(){
	//Tell movement to stop (for when we arrive at destination).
	printf("Destination reached.\n");
}
void send_ui_info(position *path){
	//Give ui the path they should draw.
}
void reset_timer() {
	gettimeofday(&current.timer, NULL);
}
void recalc(){
	//route = calc_path(current.path[current.num-1], current.ending_point);
	count=1;
	current.current_destination = route.path[count];
	running = 1;
	navigate_path();
}
void collision_avoided(double direction, struct timeval time){
	running = 0;
	current.timer = time;
	free(route.path);
	current.path = realloc(current.path, (sizeof(progressive_route) *
	current.num+2));
	current.path[current.num] = current.current_point;
	current.path[current.num].angle = current.current_destination.angle;
	current.current_destination.angle = direction;
	update_position(&current);
	current.path[current.num+1] = current.current_point;
	current.num+=2;
	recalc();
}
void navigate_path(){
	int bool;
	reset_timer();
	set_direction(&current);
	set_distance(&current);
	send_direction(&current.current_destination.angle);
	send_distance(&current.current_destination.distance);
	while(running == 1){//Infinite loop until it reaches point or collision avoidance occurs.
		update_position(&current);
		send_position(&current.current_point);
		if(current.current_point.lon == current.current_destination.lon &&
		current.current_point.lat == current.current_destination.lat){
			if(current.current_point.lon == current.ending_point.lon &&
			   current.current_point.lat == current.ending_point.lat){
				send_stop();
				bool = 0;
				free(current.path);
				free(route.path);
				break;
			}
			else{
			   current.path[current.num] = current.current_destination;
			   current.num++;
			   count++;
			   current.path = realloc(current.path, (sizeof(progressive_route) * current.num+1));
			   current.current_destination = route.path[count];
			   bool = 1;
			   break;
			}
		}
		//Wait x milliseconds
	}
	if(bool == 1 && running == 1){
	navigate_path();
	}
}
