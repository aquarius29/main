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
	char type;  // (manual/auto)
	char order; //(lift off/ hovering/ moving/ land)
	int height;
	int distance;
	int yaw; // vertical
	int pitch; // lateral
	int roll; // longitudinal 
	int speed; 
}
movementCommand;

// Create a movement command . 0 for manual(From UI), 1 for automatic(abstract navigation).
void sendmovementcommand(char type, char order , int height, int distance, int yaw, int pitch , int roll, int speed);

#endif /* MOVEMENTCOMMANDS_H */