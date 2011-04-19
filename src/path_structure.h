/*
 * path_structure.h
 *
 * Authors: Jon Fridéhn Eric Britsman Shan Huang
 */
#ifndef PATH_STRUCTURE_H
#define PATH_STRUCTURE_H

#include <sys/time.h>
#include <math.h>

#define COORDINATE_LIMIT 4
#define MAP_Y 14
#define MAP_X 12
#define NUM_ADJACENT 8
#define CENTIMETRES_PER_TILE 108
#define TILE_CENTER 0.54
#define NUM_ADJACENT 8

typedef struct{
    double lat;
    double lon;
    double angle;
    double distance;
} point;

typedef struct{
	point ending_point;
	point current_destination;
	point current_point;
	point *path;
    struct timeval timer;
    unsigned int num;
} progressive_route;

typedef struct{
	int y;
	int x;
}position;

typedef struct node
{
	position pos;
	int totalCost, heuristic;
	position previous;
}node;

typedef struct {
	node * list;
	int count;
}nodeList;

typedef struct {
	point * list;
	int num;
}position_list;

position_list indoor_dijkstra(const position * start, const position * end, int map[MAP_Y][MAP_X]);
position_list indoor_astar(const position * start, const position * end, int map[MAP_Y][MAP_X]);
void set_direction(progressive_route *path);
void set_distance(progressive_route *path);
void update_position(progressive_route *path);
void init_path(position start, position end);
void navigate_path();

#endif /* PATH_STRUCTURE_H */
