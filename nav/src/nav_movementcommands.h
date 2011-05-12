/*!
* @author 	Jarryd Hall.
* @brief	Header file for access to movementcommands functions.
*/

#

#ifndef MOVEMENTCOMMANDS_H
#define MOVEMENTCOMMANDS_H

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

#endif /* MOVEMENTCOMMANDS_H */