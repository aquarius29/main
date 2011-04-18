/*
 * Dijkstra.h
 * Author: Jon Fridehn
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define MAP_Y 14
#define MAP_X 12
#define NUM_ADJACENT 8 /* Number of neighbors */

typedef struct {
    uint16_t y;
    uint16_t x;
}position;

typedef struct node {
    position pos;
    uint32_t totalCost;
    uint32_t heuristic;
    position previous;
}node;

typedef struct {
    node * list;
    uint32_t count;
}nodeList;

typedef struct {
    position * list;
    uint16_t count;
}positionList;

void AddNodeToOpen(node * current, nodeList * open);
void RemoveNodeFromOpen(node * current, nodeList * open);
void AddNeighborsToOpen(node * current, nodeList * open, nodeList * closed,
                        int8_t map[][MAP_X], const position * end);
void FreeAllocatedList(nodeList * list);
positionList * AStar(const position * start, const position * end,
                     int8_t map[][MAP_X]);
int8_t ListMemoryAllocation(nodeList ** open, nodeList ** closed);
positionList * CreateFinalList(nodeList * closed, const position * goal,
                               const position * drone);
int8_t NodeInClosed(const uint16_t * nodeY, const uint16_t * nodeX,
                    nodeList * closed);
int8_t NodeInOpen(const uint16_t * nodeY, const uint16_t * nodeX,
                  nodeList * open);
node * AddNodeToClosed(node * current, nodeList * closed);
int32_t GetHeuristicCost(const position * currentNode,
                         const position * goalNode);

#endif	/* DIJKSTRA_H */
