/*
* Author: Jarryd Hall
* Purpose: Drone Movement Commands
* TODO: Include protocol source and use it to send data to movement
*/

#include "movementCommands.h"

// Create a movement command 
void sendMovementCommand(char* _command, int _direction, int _height)
{
	moveCommand *move = malloc(sizeof(movementCommand));
	if (move == NULL)
	{
		printf("Memory couldnt be allocated for move command\n");
	}
	else 
	{
		move->command = _command;
		move->direction = _direction;
		move->height = _height;
		// Function from interface to send order goes here 
		// e.g. InterfaceSendOrder(order);
		free(move);
	}
}
