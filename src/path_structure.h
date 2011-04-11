/*
 * path_structure.h
 *
 * Authors: Jon Fridéhn Eric Britsman Shan Huang
 */
#ifndef JOURNEYTRACKING_H
#define JOURNEYTRACKING_H

#define COORDINATE_LIMIT 4
#include <sys/time.h>
#include <math.h>

typedef struct{
    double lat;
    double lon;
    double angle;
    double distance;
} position;

typedef struct{
	position ending_point;
	position current_destination;
	position current_point;
    position *path;
    struct timeval timer;
    unsigned int num;
} progressive_route;

typedef struct{
	position ending_point;
	position starting_point;
    position *path;
    unsigned int num;
} dijkstra_route;

void DynAddCoordinates(float lat, float lon);
void StaAddCoordinates(float lat, float lon);
void FreePointer(dijkstra_route * route);
void Test();
dijkstra_route Dijkstra(const position * start, const position * end);
void set_direction(progressive_route *path);
void set_distance(progressive_route *path);
void update_position(progressive_route *path);
void init_path(position start, position end);
void navigate_path();

#endif /* JOURNEYTRACKING_H */
