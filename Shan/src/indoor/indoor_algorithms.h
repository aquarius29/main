/*
 * indoor_algorithms.h
 *
 *  Created on: Apr 10, 2011
 *      Author: Jon Fridehn
 */

#ifndef INDOOR_ALGORITHMS_H
#define INDOOR_ALGORITHMS_H
#include "path_structure.h"

void AddNodeToOpen(node * current, nodeList * open);
void RemoveNodeFromOpen(node * current, nodeList * open);
void dijkstra_AddNeighborsToOpen(node * current, nodeList * open, nodeList * closed);
void astar_AddNeighborsToOpen(node * current, nodeList * open, nodeList * closed, const position * end);
void FreeAllocatedList(nodeList * list);
int ListMemoryAllocation(nodeList ** open, nodeList ** closed);
position_list CreateFinalList(nodeList * closed, const position * goal, const position * drone);
int NodeInClosed(const int * nodeY, const int * nodeX, nodeList * closed);
int NodeInOpen(const int * nodeY, const int * nodeX, nodeList * open);
node * AddNodeToClosed(node * current, nodeList * closed);
int GetHeuristicCost(const position * currentNode, const position * goalNode);

int selected_tiles_are_valid_for_dijkstra(const position * start, const position * end);
int selected_tiles_are_valid_for_astar(const position * start, const position * end);

#endif	// INDOOR_ALGORITHMS_H
