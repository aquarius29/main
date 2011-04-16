/*
 * Dijkstra.h
 *
 *  Created on: Apr 10, 2011
 *      Author: Jon Fridehn
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define MAP_Y 14
#define MAP_X 12
#define NUM_ADJACENT 8

typedef struct{
	int y;
	int x;
}position;

typedef struct node
{
	position pos;
	int totalCost;
	position previous;
}node;

typedef struct {
	node * list;
	int count;
}nodeList;

typedef struct {
	position * list;
	int count;
}positionList;

void AddNodeToOpen(node * current, nodeList * open);
void RemoveNodeFromOpen(node * current, nodeList * open);
void AddNeighborsToOpen(node * current, nodeList * open, nodeList * closed, int map[][MAP_X]);
void FreeAllocatedList(nodeList * list);
positionList * Dijkstra(const position * start, const position * end, int map[][MAP_X]);
int8_t ListMemoryAllocation(nodeList ** open, nodeList ** closed);
positionList * CreateFinalList(nodeList * closed, const position * goal, const position * drone);
int8_t NodeInClosed(const int * nodeY, const int * nodeX, nodeList * closed);
int8_t NodeInOpen(const int * nodeY, const int * nodeX, nodeList * open);
node * AddNodeToClosed(node * current, nodeList * closed);

#endif	// DIJKSTRA_H
