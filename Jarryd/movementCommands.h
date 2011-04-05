/*
* Author: Jarryd Hall
* Purpose: Drone Controls
*
*/

// Control order struct 
typedef struct
{
	// order e.g. stop/move
	char* order;
	int direction;
	int height;
}
controlOrder;

void createMovementOrder(char* _order, int _direction, int _height);