/*
 * indoor_astar.c
 *
 * Author: Jon Fridehn
 */
#include <stdio.h>
#include <stdlib.h>
#include "nav_indooralgorithms.h"
#include "nav_indoorstructure.h"
#include "nav_tilemap.h"

static void astarAddNeighborsToOpen(node *current, nodeList *open,
nodeList *closed, const position *end);
static int32_t GetHeuristicCost(const position *currentNode,
const position *goalNode);
static positionList final;
static ThreeDWorld map;
/*
 * Takes the drone position, goal position, and a tile map
 * If the goal is found a dynamic list of the nodes making up the
 * shortest path is returned, which must be freed after it's used
 * If the goal is not reachable or if there is a problem to allocate
 * memory NULL is returned
 */
positionList indoorAstar(const position *start, const position *end)
{
	int32_t i = 0;
    nodeList *open = NULL;            /* open list */
    nodeList *closed = NULL;          /* closed list */
    node currentNode;           /* the starting node */
    fill_map(&map);
    final.num = 0;
    /* Allocate space for both the open and the closed list */
    if (!ListMemoryAllocation(&open, &closed)) {
        return final;
    }
    /* Add values for the first node in the open list */
    open->count++;
    open->list[0].pos = *start;
    open->list[0].previous.y = -1;
    open->list[0].previous.x = -1;
    open->list[0].totalCost = 0;
    open->list[0].heuristic = GetHeuristicCost(&open->list[0].pos, end);
    while (open->count > 0) {
        /* Check if we have reach the goal */
        if (open->list[0].pos.x == end->x && open->list[0].pos.y == end->y) {
            /* If so, add the goal node to the closed list and stop looping */
            closed->list = AddNodeToClosed(&open->list[0], closed);
            break;
        }
        /* Copy the values from the first node in the open list */
        currentNode = open->list[0];
        /*
         * Add the check node to the closed list and remove it
         * from the open list
         */
        closed->list = AddNodeToClosed(&currentNode, closed);
        RemoveNodeFromOpen(&currentNode, open);

        /* Check the neighbors of the first node in the open list */
        astarAddNeighborsToOpen(&currentNode, open, closed, end);
    }
    /* If we found the goal, a list with the shortest path will be created */
    if (closed->list[closed->count - 1].pos.x == end->x &&
    closed->list[closed->count - 1].pos.y == end->y)
    {
        /* Create final list and return it to the caller */
        final = CreateFinalList(closed, end, start);
        FreeAllocatedList(&open);
        FreeAllocatedList(&closed);
        return final;
    }
    /* If we could not get to the goal, there is no solution */
    else {
        printf("Could not find goal!\n");
        FreeAllocatedList(&open);
        FreeAllocatedList(&closed);
        return final;
    }
    for (i = 0; i < map.mapHeight; i++ )
    {
        free(map.representation[i]);
    }
    free(map.representation);
}
/*
 * Goes through the current node's surrounding neighbor nodes and
 * adds reachable nodes to the open list
 */
static void astarAddNeighborsToOpen(node *current, nodeList *open,
nodeList *closed, const position *end)
{
    int32_t sortCounter = 0;
    int32_t y = 0;
    int32_t x = 0;
    int32_t mapCost = 0;
    int32_t openListIndex = 0;
    int32_t neighborY = 0;
    int32_t neighborX = 0;
    int32_t endNodeCost = 0;
    node adjacentNode;
    node tempNode;
    node *p_adjacentNode = NULL;
    /* Used for checking if a neighbor node is diagonally placed */
    int32_t counter = 0;
    enum diagonal {
        north_west = 0,
        north_east = 2,
        south_west = 6,
        south_east = 8,
    };
    /*
     * Loop through the neighbor nodes, from top-left (north-west)
     * down to bottom-right (south-east)
     */
    for (y = -1; y < 2; y++) {
        for (x = -1; x < 2; x++, counter++) {
            neighborY = current->pos.y + y;
            neighborX = current->pos.x + x;

            /*
             * If x and y is 0 we have the current node and skips to next
             * loop iteration
             */
            if (neighborY == current->pos.y && neighborX == current->pos.x) {
                continue;
            }
            /* If the node is inside the map boundaries we get the map
             * cost for that node
             */
            if((neighborY >= 0 && neighborY < MAP_Y) &&
            (neighborX >= 0 && neighborX < MAP_X))
            {
                mapCost = map.representation[neighborY][neighborX];
            }
            else { /* If we're outside the map, we check the next neighbor */
                continue;
            }

            if (mapCost == 1) { /* hit a wall so we try the next connection */
                continue;
            }
            /*
             * Check diagonal move for blocking neighbor nodes
             * Condition evaluation will yield zero for diagonal neighbors
             */
            else if (counter % 2 == 0) {
                if (counter == north_west) {
                    if (map.representation[neighborY + 1][neighborX] == 1 ||
                    map.representation[neighborY][neighborX + 1] == 1)
                    {
                        continue;
                    }
                }
                else if (counter == north_east) {
                    if (map.representation[neighborY][neighborX - 1] == 1 ||
                    map.representation[neighborY + 1][neighborX] == 1)
                    {
                        continue;
                    }
                }
                else if(counter == south_east) {
                    if(map.representation[neighborY - 1][neighborX] == 1 ||
                    map.representation[neighborY][neighborX - 1] == 1)
                    {
                        continue;
                    }
                }
                else if(counter == south_west) {
                    if(map.representation[neighborY][neighborX + 1] == 1 ||
                    map.representation[neighborY - 1][neighborX] == 1)
                    {
                        continue;
                    }
                }
            }
            /* Calculate the cost to get to the neighbor node */
            if (counter % 2 == 0) {  // move diagonally
                endNodeCost = current->totalCost + 1;
            }
            else {  // move straight
                endNodeCost = current->totalCost + 1;
            }

            /* If the node is already in the closed list we don't check it */
            if (NodeInClosed(&neighborY, &neighborX, closed)) {
                continue;
            }
            /* If node is already in the open list */
            else if ((openListIndex = NodeInOpen(&neighborY, &neighborX,
            open)))
            {
                p_adjacentNode = &open->list[openListIndex - 1];
                /*
                 * Check if it's closer to get the to open list node from
                 * the node we're checking
                 */
                if (endNodeCost >= p_adjacentNode->totalCost) {
                    continue;
                }
            }
            /*
             * If the node is not an obstacle and cannot be found in the open
             * list we create it
             */
            else {
                /* Get adjacent node's position and heuristic cost */
                p_adjacentNode = &adjacentNode;
                p_adjacentNode->pos.y = neighborY;
                p_adjacentNode->pos.x = neighborX;
                p_adjacentNode->heuristic =
                GetHeuristicCost(&p_adjacentNode->pos, end);
            }
            /* Update values for node in open list or add values for new
             * node
             */
            p_adjacentNode->totalCost = endNodeCost;
            p_adjacentNode->previous = current->pos;

            /* If the node was not previously in the open list we add it */
            if (!NodeInOpen(&neighborY, &neighborX, open)) {
                AddNodeToOpen(p_adjacentNode, open);
                /*
                 * Sort the open list so the node with the smallest cost,
                 * including the heuristic cost, is the first node
                 */
                for (sortCounter = 0; sortCounter < open->count;
                sortCounter++)
                {
                    if ((p_adjacentNode->totalCost +
                    p_adjacentNode->heuristic) <
                    (open->list[sortCounter].totalCost +
                    open->list[sortCounter].heuristic))
                    {
                        tempNode = open->list[sortCounter];
                        open->list[sortCounter] = open->list[open->count - 1];
                        open->list[open->count - 1] = tempNode;
                    }
                }
            }
        }
    }
}
/* Get the heuristic cost from a node to the goal node */
static int32_t GetHeuristicCost(const position *currentNode,
const position *goalNode)
{
    int32_t h = (fabs(currentNode->y - goalNode->y) + fabs(currentNode->x -
    goalNode->x)) * 10;
    return h;
}
