/*
 * Djikstra.c
 *
 *      Author: jon
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "AStar.h"

int main(void) {
    uint16_t counterUp = 0;
    positionList *final;
    position drone = {1, 1};
    position goal = {4, 7};

    int8_t map[MAP_Y][MAP_X] = {  // rows, columns
      // 0  1  2  3  4  5  6  7  8  9 10 11
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},  // 0
        {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},  // 1
        {5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5},  // 2
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 5},  // 3
        {5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5},  // 4
        {5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5},  // 5
        {5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5},  // 6
        {5, 1, 5, 5, 5, 1, 5, 5, 5, 1, 1, 5},  // 7
        {5, 1, 5, 1, 1, 1, 1, 1, 5, 1, 1, 5},  // 8
        {5, 1, 5, 1, 1, 1, 1, 1, 5, 1, 1, 5},  // 9
        {5, 1, 5, 1, 1, 1, 5, 5, 1, 1, 1, 5},  // 10
        {5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5},  // 11
        {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},  // 12
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}   // 13
    };
    /*
     * 1 = normal walk
     * 5 = wall
     */

    final = AStar(&drone, &goal, map);
    if(final == NULL) {
        printf("No goal could be found!\n");
    }
    else {	// A list is found
        for(counterUp = 0; counterUp < final->count; counterUp++) {
            printf("final.y: %d ", final->list[counterUp].y);
            printf("final.x: %d\n", final->list[counterUp].x);
        }
        printf("final->count: %d\n", final->count);

        free(final->list);
        free(final);
    }

    return 0;
}

/*
 * Takes the drone position, goal position, and a tile map
 * If the goal is found a dynamic list of the nodes making up the
 * shortest path is returned, which must be freed after it's used
 * If the goal is not reachable or if there is a problem to allocate
 * memory NULL is returned
 */
positionList * AStar(const position * start, const position * end,
        int8_t map[][MAP_X])
{
    nodeList * open;            // open list
    nodeList * closed;          // closed list
    node currentNode;           // the starting node
    positionList * final;       // the shortest path

    // Allocate space for both the open and the closed list
    if(!ListMemoryAllocation(&open, &closed)) {
        return NULL;
    }

    // Add values for the first node in the open list
    open->count++;
    open->list[0].pos = *start;
    open->list[0].previous.y = -1;
    open->list[0].previous.x = -1;
    open->list[0].totalCost = 0;
    open->list[0].heuristic = GetHeuristicCost(&open->list[0].pos, end);

    while(open->count > 0) {
        // Check if we have reach the goal
        if(open->list[0].pos.x == end->x
        && open->list[0].pos.y == end->y)
        {
            // If so, add the goal node to the closed list and stop looping
            closed->list = AddNodeToClosed(&open->list[0], closed);
            break;
        }

        // Copy the values from the first node in the open list
        currentNode = open->list[0];

        // Add the check node to the closed list and remove it
        // from the open list
        closed->list = AddNodeToClosed(&currentNode, closed);
        RemoveNodeFromOpen(&currentNode, open);

        // Check the neighbors of the first node in the open list
        AddNeighborsToOpen(&currentNode, open, closed, map, end);
    }

    // If we found the goal, a list with the shortest path will be created
    if(closed->list[closed->count - 1].pos.x == end->x
    && closed->list[closed->count - 1].pos.y == end->y)
    {
        // Create final list and return it to the caller
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
        return NULL;
    }
}

/*
 * Goes through the current node's surrounding neighbor nodes and
 * adds reachable nodes to the open list
 */
void AddNeighborsToOpen(node * current, nodeList * open, nodeList * closed,
        int8_t map[][MAP_X], const position * end) {
    int8_t sortCounter = 0;
    int8_t y = 0;
    int8_t x = 0;
    int8_t mapCost = 0;
    uint16_t openListIndex = 0;
    uint16_t neighborY = 0;
    uint16_t neighborX = 0;
    uint32_t endNodeCost = 0;
    node adjacentNode;
    node tempNode;
    node *p_adjacentNode;

    // Used for checking if a neighbor node is diagonally placed
    int8_t counter = 0;

    enum diagonal {
        north_west = 0,
        north_east = 2,
        south_west = 6,
        south_east = 8,
    };

    // Loop through the neighbor nodes, from top-left (north-west)
    // down to bottom-right (south-east)
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
            && (neighborX >= 0 && neighborX < MAP_X))
            {
                mapCost = map[neighborY][neighborX];
            }
            else { // If we're outside the map, we check the next neighbor
                continue;
            }

            if(mapCost == 5) { // We hit a wall so we try the next connection
                continue;
            }
            // Check diagonal move for blocking neighbor nodes
            // Condition evaluation will yield zero for diagonal neighbors
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
            if(counter % 2 == 0) {  // move diagonally
                endNodeCost = current->totalCost + (mapCost * 10) + 4;
            }
            else {  // move straight
                endNodeCost = current->totalCost + (mapCost * 10);
            }

            // If the node is already in the closed list we don't check it
            if(NodeInClosed(&neighborY, &neighborX, closed)) {
                continue;
            }
            // If node is already in the open list
            else if((openListIndex = NodeInOpen(&neighborY,
                                                &neighborX, open)))
            {
                p_adjacentNode = &open->list[openListIndex - 1];

                // Check if it's closer to get the to open list node
                // from the node we're checking
                if(endNodeCost >= p_adjacentNode->totalCost) {
                    continue;
                }
            }
            // If the node is not an obstacle and cannot be found in
            // the open list we create it
            else {
				// Get adjacent node's position and heuristic cost
                p_adjacentNode = &adjacentNode;
                p_adjacentNode->pos.y = neighborY;
                p_adjacentNode->pos.x = neighborX;
                p_adjacentNode->heuristic =
                		GetHeuristicCost(&p_adjacentNode->pos, end);
            }

            // Update values for node in open list or add values for new node
            p_adjacentNode->totalCost = endNodeCost;
            p_adjacentNode->previous = current->pos;

            // If the node was not previously in the open list we
            // add it
            if(!NodeInOpen(&neighborY, &neighborX, open)) {
                AddNodeToOpen(p_adjacentNode, open);

                // Sort the open list so the node with the smallest cost,
                // including the heuristic cost, is the first node
                for(sortCounter = 0; sortCounter < open->count;
                    sortCounter++)
                {
                    if((p_adjacentNode->totalCost +
                        p_adjacentNode->heuristic) <
                       (open->list[sortCounter].totalCost +
                        open->list[sortCounter].heuristic))
                    {
                        tempNode = open->list[sortCounter];
                        open->list[sortCounter] =
                            open->list[open->count - 1];
                        open->list[open->count - 1] = tempNode;
                    }
                }
            }
        }
    }
}

/*
 * Creates the final list and returns a pointer to it
 */
positionList * CreateFinalList(nodeList * closed, const position * goal,
        const position * drone)
{
    position temp;  // used to reverse the final list
    positionList * final;
    uint16_t counterUp;
    uint16_t counterDown;
    uint16_t closedIndex;

    final = calloc(1, sizeof(positionList));
    if(final == NULL) {
        printf("Could not allocate memory for final list\n");
        return NULL;
    }
    final->list = calloc(closed->count, sizeof(position));
    final->list[0].y = goal->y;    // add the goal node to the final list
    final->list[0].x = goal->x;
    final->count++;

    closedIndex = closed->count - 1;

    // Loop through the nodes in the closed list and trace back to the drone
    // by using each node's "parent" x- and y-values
    for(counterUp = 1; counterUp < closed->count; counterUp++) {
        // Get the position of the "parent" node in the closed list
        closedIndex = NodeInClosed(&closed->list[closedIndex].previous.y,
                                   &closed->list[closedIndex].previous.x,
                                   closed) - 1;

        final->list[counterUp].y = closed->list[closedIndex].pos.y;
        final->list[counterUp].x = closed->list[closedIndex].pos.x;
        final->count++;

        // When the drone node is found in the closed list we stop looping
        if(final->list[counterUp].y == drone->y
        && final->list[counterUp].x == drone->x)
        {
            break;
        }
    }

    // Reverse the final list to get the nodes in the right order
    for(counterUp = 0, counterDown = final->count - 1;
        counterUp < counterDown; counterUp++, counterDown--)
    {
        temp = final->list[counterUp];
        final->list[counterUp] = final->list[counterDown];
        final->list[counterDown] = temp;
    }

    // Free node space that is not needed
    final->list = realloc(final->list, final->count * sizeof(position));
    return final;
}

/*
 * Get the heuristic cost from a node to the goal node
 */
int32_t GetHeuristicCost(const position * currentNode,
                         const position * goalNode)
{
    return (abs(currentNode->y - goalNode->y)
          + abs(currentNode->x - goalNode->x)) * 10;
}

/*
 * Dynamically allocates space for the open and closed list
 */
int8_t ListMemoryAllocation(nodeList ** open, nodeList ** closed) {
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
    int32_t counter;

    for(counter = 1; counter < open->count; counter++) {
        open->list[counter - 1] = open->list[counter];
    }

    open->count--;
}

/*
 * Check if a node is already in the closed list
 */
int8_t NodeInClosed(const uint16_t * nodeY, const uint16_t * nodeX,
        nodeList * closed)
{
	uint16_t closedCounter;

    for(closedCounter = 0; closedCounter < closed->count;
        closedCounter++)
    {
        if(closed->list[closedCounter].pos.y == *nodeY
        && closed->list[closedCounter].pos.x == *nodeX)
        {
            return closedCounter + 1; // true, add one to not get zero
        }
    }

    return 0;	//false
}

/*
 * Check if a node is already in the open list
 */
int8_t NodeInOpen(const uint16_t * nodeY, const uint16_t * nodeX, nodeList * open) {
    u_int32_t openCounter;
    for(openCounter = 0; openCounter < open->count; openCounter++) {
        if(open->list[openCounter].pos.y == *nodeY
        && open->list[openCounter].pos.x == *nodeX)
        {
            return openCounter + 1;	// true, add 1 to not get zero
        }
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
