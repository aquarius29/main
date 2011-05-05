/*
 * path_structure.h
 *
 * Authors: Jon Fridéhn Eric Britsman Shan Huang
 */
#ifndef NAV_INDOORSTRUCTURE_H
#define NAV_INDOORSTRUCTURE_H

#include <stdint.h>
#include <sys/time.h>
#include <math.h>

#define MAP_Y 12
#define MAP_X 10
#define NUM_ADJACENT 8
#define CENTIMETRES_PER_TILE 108
#define TILE_CENTER (CENTIMETRES_PER_TILE/2)

typedef struct {
	int32_t lat;
	int32_t lon;
    double angle;
    double distance;
} pixel;
typedef struct progressiveNode {
    pixel p;
	struct progressiveNode *prev;
	struct progressiveNode *next;
} progressiveNode;
typedef struct {
	int32_t y;
	int32_t x;
}position;
typedef struct node {
	position pos;
	int32_t totalCost, heuristic;
	position previous;
}node;
typedef struct {
	node * list;
	int32_t count;
}nodeList;
typedef struct {
	pixel * list;
	int32_t num;
}positionList;

positionList indoorDijkstra(const position *start, const position *end);
positionList indoorAstar(const position *start, const position *end);
void initPath(position *start, position *end);
void stopIndoorNavigation(void);
void collisionAvoided(double direction, struct timeval time);

#endif /* NAV_INDOORSTRUCTURE_H */
