
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
		
		free(move);
	}
}

/* 	@author Jarryd Hall
* 	@brief Function to create a manual movement command
*	@details Function creates a movement command
*	based on the identifier passed in.
*
*	@param identifier The id to identify the command requested
*/


void sendManualMovementCommand(int16_t height, int16_t distance, int16_t yaw, uint8_t order) {
	struct movCommand *move = malloc(sizeof(struct movCommand));
	if (move == NULL)
	{
		printf("Memory couldnt be allocated for move command\n");
	}
	else 
	{
		move->type = MANUAL;
		move->order = order;
		move->height = height;
		move->distance = distance;
		move->yaw = yaw;
		
        // printf("Sending Manual Movement Command\n");
		nav_sendManualMovementCommand(move);
		
		free(move);		
	}
}