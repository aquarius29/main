/*!
* @author 	Jarryd Hall.
* @brief 	Drone Movement Commands.
* @details  A module for creating and sending auto movement commands.
*           This is used by the navigation systems to generate movement commands
*		    from their path calculations.
*/

#include <stdlib.h>
#include <stdio.h>
#include "nav_movementcommands.h"

//! Create a movement command.
/*!
* Function to be used by the navigation systems to create auto movement commands.
*
* @param order 0 = hover, 1 = moving, 2 = landing.
* @param height The height the drone should be at.
* @param distance The distance to move the drone.
* @param yaw The direction to move the drone in.
*
* @see nav_sendAutoMovementCommand().
*/
void sendautomovementcommand(uint8_t order , int16_t height, uint16_t distance, int16_t yaw)
{
	struct movCommand *move = malloc(sizeof(struct movCommand));
	if (move == NULL)
	{
		printf("Memory couldnt be allocated for move command\n");
	}
	else 
	{
		move->type = AUTO;
		move->order = order;
		move->height = height;
		move->distance = distance;
		move->yaw = yaw;
        
		printf("Sending Auto Movement Command");
		nav_sendAutoMovementCommand(move);
		
		free(move);
	}
}

void sendManualMovementCommand(int identifier)
{
	struct movCommand *move = malloc(sizeof(struct movCommand));
	if (move == NULL)
	{
		printf("Memory couldnt be allocated for move command\n");
	}
	else 
	{
		move->type = MANUAL;
		
		switch (identifier)
		{
			case FORWARD: 
				move->order = FORWARD_COMMAND;
				move->distance = MOVE_FORWARD_COMMAND_VALUE;
				move->height = ;
				move->yaw = MOVE_FORWARD_COMMAND_DIRECTION;
				break;	
			case BACK:
				move->order = BACKWARD_COMMAND;
				move->distance = MOVE_BACKWARD_COMMAND_VALUE;
				move->height = ;
				move->yaw = MOVE_BACKWARD_COMMAND_DIRECTION;
				break;
			case LEFT:
				move->order = LEFT_COMMAND;
				move->distance = MOVE_LEFT_COMMAND_VALUE;
				move->height = ;
				move->yaw = MOVE_LEFT_COMMAND_DIRECTION;
				break;
			case RIGHT:
				move->order = RIGHT_COMMAND;
				move->distance = MOVE_RIGHT_COMMAND_VALUE;
				move->height = ;
				move->yaw = MOVE_RIGHT_COMMAND_DIRECTION;
				break;
			case UP: /* Modify the height here */
				move->order = ;
				move->distance = ;
				move->height = MOVE_UP_COMMAND_VALUE;
				move->yaw = ;
				break;
			case DOWN: /* Modify the height here */
				move->order = ;
				move->distance = ;
				move->height = MOVE_DOWN_COMMAND_VALUE;
				move->yaw = ;
				break;
			case LAND:
				move->order = LANDING_COMMAND;
				break;
			case TAKE_OFF:
				move->order = LIFT_OFF_COMMAND;
				break;
				
		}
	}
}