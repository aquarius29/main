/*
 * path_data.c
 *
 *  Created on: 31 mar 2011
 *      Authors: Eric Britsman Shan Huang
 *
	The following setter methods can be used for two scenarios.
	1.	To calculate initial path.
			Start position and end position will be
			inputed by user.
	2.	To calculate remaining path.
			The new start position will be obtained
			from the update_path method.
 *
 */
#include "path_structure.h"
#include <math.h>

#define CENTIMETRES_PER_SECOND 10
#define CENTIMETRES_PER_DEGREE 2

void set_direction(progressive_route *path) {
	path->current_destination.angle =
	atan2((path->current_destination.lat - path->path[path->num-1].lat),
	(path->current_destination.lon - path->path[path->num-1].lon)) * (180/ M_PI) + 180;
}
void set_distance(progressive_route *path) {
	path->current_destination.distance = (sqrt((path->current_destination.lon -
	path->path[path->num-1].lon) * (path->current_destination.lon -
	path->path[path->num-1].lon) + (path->current_destination.lat -
	path->path[path->num-1].lat) * (path->current_destination.lat -
	path->path[path->num-1].lat))) * CENTIMETRES_PER_DEGREE;
}
void update_position(progressive_route *path) {
	struct timeval current_time;
	double change_x, change_y, time, microseconds;
	gettimeofday(&current_time, NULL);
	microseconds = (current_time.tv_usec - path->timer.tv_usec);
	if(microseconds != 0){
		microseconds = microseconds/1000000;
	}
	time = (current_time.tv_sec - path->timer.tv_sec) + microseconds;
	change_y = (time * CENTIMETRES_PER_SECOND) *
	sin(path->current_destination.angle);
	change_x = change_y / tan(path->current_destination.angle);
	path->current_point.lon = path->path[path->num-1].lon + change_x;
	path->current_point.lat = path->path[path->num-1].lat + change_y;
}
