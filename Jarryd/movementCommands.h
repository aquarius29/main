/*
* Author: Jarryd Hall
* Purpose: Drone Movement Commands
*
*/

#ifndef MOVEMENTCOMMANDS_H
#define MOVEMENTCOMMANDS_H

// MovementCommand struct 
typedef struct
{
	// command e.g. Take Off/ Land/ Hover/ Move
	char* command;
	int direction;
	int height;
}
moveCommand;

void sendMovementCommand(char* _command, int _direction, int _height);

#endif /* MOVEMENTCOMMANDS_H */