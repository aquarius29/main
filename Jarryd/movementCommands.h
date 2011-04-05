/*
* Author: Jarryd Hall
* Purpose: Drone Movement Commands
*
*/

// MovementCommand struct 
typedef struct
{
	// command e.g. stop/move
	char* command;
	int direction;
	int height;
}
moveCommand;

void sendMovementCommand(char* _command, int _direction, int _height);