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
void AddNeighborsToOpen(node * current, nodeList * open, nodeList * closed, int map[MAP_Y][MAP_X]);
void FreeAllocatedList(nodeList * list);
int ListMemoryAllocation(nodeList ** open, nodeList ** closed);
position_list CreateFinalList(nodeList * closed, const position * goal, const position * drone);
int NodeInClosed(const int * nodeY, const int * nodeX, nodeList * closed);
int NodeInOpen(const int * nodeY, const int * nodeX, nodeList * open);
node * AddNodeToClosed(node * current, nodeList * closed);
int GetHeuristicCost(const position * currentNode, const position * goalNode);

#endif	// INDOOR_ALGORITHMS_H
