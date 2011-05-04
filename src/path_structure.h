/*
 * path_structure.h
 *
 * Authors: Jon Fridéhn Eric Britsman Shan Huang
 */
#ifndef PATH_STRUCTURE_H
#define PATH_STRUCTURE_H

#include <sys/time.h>
#include <math.h>

#define MAP_Y 14
#define MAP_X 12
#define NUM_ADJACENT 8
#define CENTIMETRES_PER_TILE 108
#define TILE_CENTER (CENTIMETRES_PER_TILE/2)

typedef struct{
    double lat;
    double lon;
    double angle;
    double distance;
} pixel;
typedef struct progressive_node {
    pixel p;
	struct progressive_node *prev;
	struct progressive_node *next;
} progressive_node;
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
	pixel * list;
	int num;
}position_list;

position_list indoor_dijkstra(const position *start, const position *end);
position_list indoor_astar(const position *start, const position *end);
void init_path(position *start, position *end);
void stopIndoorNavigation(void);
void collision_avoided(double direction, struct timeval time);

#endif /* PATH_STRUCTURE_H */
