/*!
* @author Jarryd Hall
* @brief Drone Movement Commands
* @details A module for creating and sending auto movement commands
*          This is used by the navigation systems to generate movement commands
*		   from their path calculations
*/

#include <stdlib.h>
#include <stdio.h>
#include "movementcommands.h"

//! Create a movement command.
/*!
* Function to be used by the navigation systems to create auto movement commands.
* @param order 0 = hover, 1 = moving, 2 = landing.
* @param height The height the drone should be at.
* @param distance The distance to move the drone.
* @param yaw The direction to move the drone in.
* @see nav_sendAutoMovementCommand().
*/
void sendautomovementcommand
(char order , int height, int distance, int yaw)
{
	movementCommand *move = malloc(sizeof(movementCommand));
	if (move == NULL)
	{
		printf("Memory couldnt be allocated for move command\n");
	}
	else 
	{
		move->type = 1; /* 1 for auto */
		move->order = order;
		move->height = height;
		move->distance = distance;
		move->yaw = yaw;
        
		printf("Sending Auto Movement Command");
		nav_sendAutoMovementCommand(move);
		
		free(move);
	}
}