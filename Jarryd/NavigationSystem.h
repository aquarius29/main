/*
* Author: Jarryd Hall
*/

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

ThreeDWorld *world;

void setNavigationSystem(char* navigationSystem);
void setupGPSSystem();
void setupIndoorNavigationSystem();
void manualMovementCommand(char *_command);