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

void addNodeToOpen(node * current, nodeList * open);
void removeNodeFromOpen(node * current, nodeList * open);
void addNeighborsToOpen(node * current, nodeList * open, nodeList * closed,
                        int8_t map[][MAP_X], const position * end);
void freeAllocatedList(nodeList * list);
positionList * aStar(const position * start, const position * end,
                     int8_t map[][MAP_X]);
int8_t listMemoryAllocation(nodeList ** open, nodeList ** closed);
positionList * createFinalList(nodeList * closed, const position * goal,
                               const position * drone);
int8_t nodeInClosed(const uint16_t * nodeY, const uint16_t * nodeX,
                    nodeList * closed);
int8_t nodeInOpen(const uint16_t * nodeY, const uint16_t * nodeX,
                  nodeList * open);
node * addNodeToClosed(node * current, nodeList * closed);
int32_t getHeuristicCost(const position * currentNode,
                         const position * goalNode);

#endif	/* DIJKSTRA_H */
