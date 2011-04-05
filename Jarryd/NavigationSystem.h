/*
* Author: Jarryd Hall
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

typedef struct
{
	// the angle/direction the drone moved
	int directionMoved;
	
	// distance moved on each axis
	int xAxisMovement;
	int yAxisMovement;
	int zAxisMovement;
}
movementPerformed;

void setNavigationSystem(char* navigationSystem);
void setupGPSSystem();
void setupIndoorNavigationSystem();
void createMovementOrder(char* _order, int _direction, int _height);