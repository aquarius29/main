
/*!
* @author 	Jarryd Hall.
* @brief 	Drone Movement Commands.
* @details  A module for creating and sending manual and auto movement commands.
*           This is used by the navigation systems to generate movement commands
*		    from their path calculations.
*/

#include <stdlib.h>
#include <stdio.h>
#include "nav_movementcommands.h"
#include "nav_corelogic.h"

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
        
		printf("Sending Auto Movement Command\n");
		nav_sendAutoMovementCommand(move);
		
<<<<<<< HEAD
		free(move);
=======
		//free(move);
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
	}
}

/* 	@author Jarryd Hall
* 	@brief Function to create a manual movement command
*	@details Function creates a movement command
*	based on the identifier passed in.
*
*	@param identifier The id to identify the command requested
*/
<<<<<<< HEAD
void processMovementCommand(int identifier)
{
=======


void sendManualMovementCommand(int16_t height, int16_t distance, int16_t yaw, uint8_t order) {
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
	struct movCommand *move = malloc(sizeof(struct movCommand));
	if (move == NULL)
	{
		printf("Memory couldnt be allocated for move command\n");
	}
	else 
	{
<<<<<<< HEAD
		move->type = (((uint8_t)MANUAL));
		
		switch (identifier)
		{
			case FORWARD: 
				move->order = 1;
				move->height = 0;
				move->distance = 10;
				move->yaw = 0;
				break;	
			/*
			case BACK:
				move->order = BACKWARD_COMMAND;
				move->height = (((int16_t)the value here));
				move->distance = MOVE_BACKWARD_COMMAND_VALUE;
				move->yaw = MOVE_BACKWARD_COMMAND_DIRECTION;
				break;
			*/
			case LEFT:
				move->order = 0;
				move->height = 0;
				move->distance = 0;
				move->yaw = -10;
				break;
			case RIGHT:
				move->order = 0;
				move->height = 0;
				move->distance = 0;
				move->yaw = 10;
				break;
			case UP: /* Modify the height here */
				move->order = 0;
				move->height = 10;
				move->distance = 0;
				move->yaw = 0;
				break;
			case DOWN: /* Modify the height here */
				move->order = 0;
				move->height = -10;
				move->distance = 0;
				move->yaw = 0;
				break;
			case LAND:
				move->order = 2;
				move->height = 0;
				move->distance = 0;
				move->yaw = 0;
				break;
			case TAKE_OFF:
				move->order = 0;
				move->height = 50;
				move->distance = 0;
				move->yaw = 0;
				break;		
		}
=======
		move->type = MANUAL;
		move->order = order;
		move->height = height;
		move->distance = distance;
		move->yaw = yaw;
		
        // printf("Sending Manual Movement Command\n");
		nav_sendManualMovementCommand(move);
		
		free(move);		
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
	}
}
