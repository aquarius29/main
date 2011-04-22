/*
 * indoor_djikstra.c
 *
 *  Created on: Mar 27, 2011
 *      Author: jon
 */
#include <stdio.h>
#include <stdlib.h>
#include "indoor_algorithms.h"
#include "path_structure.h"

static position_list final;
/*
 * Takes the drone position, goal position, and a tile map
 * If the goal is found a dynamic list of the nodes making up the
 * shortest path is returned, which must be freed after it's used
 * If the goal is not reachable or if there is a problem to allocate
 * memory NULL is returned
 */
position_list indoor_dijkstra(const position * start, const position * end, int map[MAP_Y][MAP_X])
{
	nodeList * open, * closed;	// open and closed list
	node startNode;				// the starting node

	// Allocate space for both the open and the closed list
	if(!ListMemoryAllocation(&open, &closed)) {
		return final;
	}
	// Create the first node (start) to go into the open list
	startNode.pos.y = start->y;
	startNode.pos.x = start->x;
	startNode.totalCost = 0;
	AddNodeToOpen(&startNode, open);
	while(open->count > 0)
	{
		// Check if we have reach the goal
		if(open->list[0].pos.x == end->x
				&& open->list[0].pos.y == end->y)
		{
			// If so, add the goal node to the closed list and stop looping
			closed->list = AddNodeToClosed(&open->list[0], closed);
			break;
		}

		// Check the neighbors of the first node in the open list
		dijkstra_AddNeighborsToOpen(&open->list[0], open, closed, map);

		// Add the check node to the closed list and remove it
		// from the open list
		closed->list = AddNodeToClosed(&open->list[0], closed);
		RemoveNodeFromOpen(&open->list[0], open);
	}
	// If we found the goal, a list with the shortest path will be created
	if(closed->list[closed->count - 1].pos.x == end->x
			&& closed->list[closed->count - 1].pos.y == end->y) 	{
		// Create final list and return it to the caller
		printf("222\n");
		final = CreateFinalList(closed, end, start);
		FreeAllocatedList(open);
		FreeAllocatedList(closed);
		return final;
	}
	// If we could not get to the goal, there is no solution
	else {
		printf("Could not find goal!\n");
		FreeAllocatedList(open);
		FreeAllocatedList(closed);
		return final;
	}
}

/*
 * Goes through the current node's surrounding neighbor nodes and
 * adds reachable nodes to the open list
 */
void dijkstra_AddNeighborsToOpen(node * current, nodeList * open, nodeList * closed,
		int map[MAP_Y][MAP_X]) {
	int y, x, mapCost, counter;
	int openListIndex, endNodeCost, neighborY, neighborX;
	node adjacentNode, * p_adjacentNode;

	counter = 0;  // used for checking if a neighbor node is diagonally placed
	enum diagonal {
		north_west = 0,
		north_east = 2,
		south_west = 6,
		south_east = 8,
	};

	// Loop through the neighbor nodes
	for(y = -1; y < 2; y++) {
		for(x = -1; x < 2; x++, counter++) {
			neighborY = current->pos.y + y;
			neighborX = current->pos.x + x;

			// If x and y is 0 we have the current node
			// and skips to next loop iteration
			if(neighborY == current->pos.y
					&& neighborX == current->pos.x)
				continue;

			// If the node is inside the map boundaries we get the map
			// cost for that node
			if((neighborY >= 0 && neighborY < MAP_Y)
					&& (neighborX >= 0 && neighborX < MAP_X)) {
				mapCost = map[neighborY][neighborX];
			}
			else { // If we're outside the map, we check the next neighbor
				continue;
			}

			if(mapCost == 5) { // We hit a wall so we try the next connection
				continue;
			}
			// Check diagonal move for blocking neighbor nodes
			// The condition evaluation will yield zero for diagonal neighbors
			else if(counter % 2 == 0) {
				if(counter == north_west) {
					if(map[neighborY + 1][neighborX] == 5 	// west
							|| map[neighborY][neighborX + 1] == 5)	// north
						continue;
				}
				else if(counter == north_east) {
					if(map[neighborY][neighborX - 1] == 5 	// North
							|| map[neighborY + 1][neighborX] == 5)	// East
						continue;
				}
				else if(counter == south_east) {
					if(map[neighborY - 1][neighborX] == 5 	// East
							|| map[neighborY][neighborX - 1] == 5)	// South
						continue;
				}
				else if(counter == south_west) {
					if(map[neighborY][neighborX + 1] == 5 	// South
							|| map[neighborY - 1][neighborX] == 5)	// West
						continue;
				}
			}

			// Calculate the cost to get to the neighbor node
			if(counter % 2 == 0) // move diagonally
				endNodeCost = current->totalCost + (mapCost * 10) + 4;
			else // move straight
				endNodeCost = current->totalCost + (mapCost * 10);


			// If the node is already in the closed list we don't check it
			if(NodeInClosed(&neighborY, &neighborX, closed)) {
				continue;
			}
			// If node is already in the open list
			else if((openListIndex = NodeInOpen(&neighborY, &neighborX, open))) {
				p_adjacentNode = &open->list[openListIndex - 1];

				// Check if it's closer to get the to open list node
				// from the node we're checking
				if(endNodeCost >= p_adjacentNode->totalCost)
					continue;
			}
			// If the node is not an obstacle and cannot be found in
			// the open list we create it
			else {
				// Get adjacent node's position
				p_adjacentNode = &adjacentNode;
				p_adjacentNode->pos.y = neighborY;
				p_adjacentNode->pos.x = neighborX;
			}

			// Update values for node in open list or add values for new node
			p_adjacentNode->totalCost = endNodeCost;
			p_adjacentNode->previous = current->pos;

			// If the node was not previously in the open list we
			// add it
			if(!NodeInOpen(&neighborY, &neighborX, open)) {
				AddNodeToOpen(p_adjacentNode, open);
			}
		}
	}
}

/*
 * Creates the final list and returns a pointer to it
 */
position_list CreateFinalList(nodeList * closed, const position * goal, const position * drone) {
	point temp;  // used to reverse the final list
	int counterUp, counterDown, closedIndex;
	final.list = calloc(closed->count, sizeof(point));
	final.list[0].lon = (double)((goal->x * CENTIMETRES_PER_TILE) + TILE_CENTER);
	final.list[0].lat = (double)((goal->y * CENTIMETRES_PER_TILE) + TILE_CENTER);
	final.num++;

	closedIndex = closed->count - 1;

	// Loop through the nodes in the closed list and trace back to the drone
	// by using each node's "parent" x- and y-values
	for(counterUp = 1; counterUp < closed->count; counterUp++)
	{
		// Get the position of the "parent" node in the closed list
		closedIndex = NodeInClosed(&closed->list[closedIndex].previous.y,
		&closed->list[closedIndex].previous.x, closed) - 1;

		final.list[counterUp].lon = (double)(closed->list[closedIndex].pos.x
		* CENTIMETRES_PER_TILE + TILE_CENTER);
		final.list[counterUp].lat = (double)(closed->list[closedIndex].pos.y
		* CENTIMETRES_PER_TILE + TILE_CENTER);
		final.num++;

		// When the drone node is found in the closed list we stop looping
		if((int)((final.list[counterUp].lat - TILE_CENTER) / CENTIMETRES_PER_TILE) == drone->y
			&& (int)((final.list[counterUp].lon - TILE_CENTER) / CENTIMETRES_PER_TILE) == drone->x)
		{
			break;
		}
	}

	// Reverse the final list to get the nodes in the right order
	for(counterUp = 0, counterDown = final.num-1;
			counterUp < counterDown; counterUp++, counterDown--)
	{
		temp = final.list[counterUp];
		final.list[counterUp] = final.list[counterDown];
		final.list[counterDown] = temp;
	}

	// Free node space that is not needed
	final.list = realloc(final.list, (final.num) * sizeof(point));
	//final.num = final.num/2 + 1;
	return final;
}

/*
 * Dynamically allocates space for the open and closed list
 */
int ListMemoryAllocation(nodeList ** open, nodeList ** closed) {
	*open = calloc(1, sizeof(nodeList));
	if(open == NULL) {
		printf("Could not allocate memory for the open list struct\n");
		return 0;
	}
	(*open)->list = calloc(MAP_X * MAP_Y, sizeof(node));
	if((*open)->list == NULL) {
		printf("Could not allocate memory for the open list\n");
		return 0;
	}
	*closed = calloc(1, sizeof(nodeList));
	if(closed == NULL) {
		printf("Could not allocate memory for the closed struct\n");
		return 0;
	}
	(*closed)->list = calloc(1, sizeof(node));
	if((*closed)->list == NULL) {
		printf("Could not allocate memory for the closed list\n");
		return 0;
	}

	return 1;
}

/*
 * Add node to the open list
 */
void AddNodeToOpen(node * current, nodeList * open) {
	open->count++;

	open->list[open->count - 1] = *current;
}

/*
 * Add a node to the closed list
 */
node * AddNodeToClosed(node * current, nodeList * closed) {
	closed->count++;

	closed->list = realloc(closed->list, closed->count * sizeof(node));
	closed->list[closed->count - 1] = *current;

	return closed->list;
}

/*
 * Remove a node from the open list
 */
void RemoveNodeFromOpen(node * current, nodeList * open) {
	int counter;

	for(counter = 1; counter < open->count; counter++) {
		open->list[counter - 1] = open->list[counter];
	}

	open->count--;
}

/*
 * Check if a node is already in the closed list
 */
int NodeInClosed(const int * nodeY, const int * nodeX, nodeList * closed)
{
	int closedCounter;

	for(closedCounter = 0; closedCounter < closed->count; closedCounter++)
	{
		if(closed->list[closedCounter].pos.y == *nodeY
				&& closed->list[closedCounter].pos.x == *nodeX) {
			return closedCounter + 1; // true, add one to not get zero
		}
	}

	return 0;	//false
}

/*
 * Check if a node is already in the open list
 */
int NodeInOpen(const int * nodeY, const int * nodeX, nodeList * open)
{
	int openCounter;
	for(openCounter = 0; openCounter < open->count; openCounter++)
	{
		if(open->list[openCounter].pos.y == *nodeY
				&& open->list[openCounter].pos.x == *nodeX)
			return openCounter + 1;	// true, add 1 to not get zero
	}

	return 0;	// false
}

/*
 * Help function to free all memory for a node list
 */
void FreeAllocatedList(nodeList * list) {
	free(list->list);
	free(list);
}
