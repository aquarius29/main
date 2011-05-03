/*
* Author: Jarryd Hall
* Purpose: Drone Movement Commands
* TODO: Include protocol source and use it to send data to movement
*/

#include <stdlib.h>
#include <stdio.h>
#include "movementcommands.h"

/* Create a movement command */
void sendmovementcommand
(char type, char order , int height, int distance, int yaw)
{
	movementCommand *move = malloc(sizeof(movementCommand));
	if (move == NULL)
	{
		printf("Memory couldnt be allocated for move command\n");
	}
	else 
	{
		move->type = type;
		move->order = order;
		move->height = height;
		move->distance = distance;
		move->yaw = yaw;
        
        /* Function from interface to send order goes here */
		/* e.g. InterfaceSendOrder(order); */
		free(move);
	}
}
