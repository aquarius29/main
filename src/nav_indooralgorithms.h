/*
 * indoor_algorithms.h
 *
 *  Created on: Apr 10, 2011
 *      Author: Jon Fridehn
 */
#ifndef NAV_INDOORALGORITHMS_H
#define NAV_INDOORALGORITHMS_H
#include "nav_indoorstructure.h"

void AddNodeToOpen(node *current, nodeList *open);
void RemoveNodeFromOpen(node *current, nodeList *open);
void FreeAllocatedList(nodeList *list);
int32_t ListMemoryAllocation(nodeList **open, nodeList **closed);
positionList CreateFinalList(nodeList *closed, const position *goal,
const position *drone);
int32_t NodeInClosed(const int32_t *nodeY, const int32_t *nodeX,
nodeList *closed);
int32_t NodeInOpen(const int32_t *nodeY, const int32_t *nodeX,
nodeList *open);
node * AddNodeToClosed(node *current, nodeList *closed);

#endif	// NAV_INDOORALGORITHMS_H
