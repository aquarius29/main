/*!
* @author 	Jarryd Hall.
* @brief	Header file for access to movementcommands functions.
*/

#

#ifndef MOVEMENTCOMMANDS_H
#define MOVEMENTCOMMANDS_H

#define FORWARD 3
#define BACK 4
#define LEFT 5
#define RIGHT 6
#define UP 7
#define DOWN 8
#define LAND 9
#define TAKE_OFF 10

#define MANUAL 0
#define AUTO 1

#define HOVER_COMMAND 0
#define MOVING_COMMAND 1
#define LANDING_COMMAND 2
#define LIFT_OFF_COMMAND 3
#define FORWARD_COMMAND 4
#define BACKWARD_COMMAND 5
#define RIGHT_COMMAND 6
#define LEFT_COMMAND 7


#define MOVE_LEFT_COMMAND_VALUE 0 /* Set the value here */
#define MOVE_RIGHT_COMMAND_VALUE 0 /* Set the value here */
#define MOVE_FORWARD_COMMAND_VALUE 0 /* Set the value here */
#define MOVE_BACKWARD_COMMAND_VALUE 0 /* Set the value here */
#define MOVE_UP_COMMAND_VALUE 0
#define MOVE_DOWN_COMMAND_VALUE 0

#define MOVE_LEFT_COMMAND_DIRECTION 0
#define MOVE_RIGHT_COMMAND_DIRECTION 0
#define MOVE_FORWARD_COMMAND_DIRECTION 0
#define MOVE_BACKWARD_COMMAND_DIRECTION 0

#include <stdint.h>
//! MovementCommand struct 
/*!
* 
*
*/
struct movCommand
{
	uint8_t type; // (manual/auto)
	uint8_t order; //(hovering/ moving / landing / lift off / forward / backward / right / left)
	int16_t height;
	uint16_t distance;
	int16_t yaw;
};

/* Create a movement command . 0 for manual(From UI), 1 for automatic(abstract navigation). */
void sendautomovementcommand(uint8_t order , int16_t height, uint16_t distance, int16_t yaw);
void sendManualMovementCommand(int identifier);

#endif /* MOVEMENTCOMMANDS_H */