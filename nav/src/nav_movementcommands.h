/*!
* @author 	Jarryd Hall.
* @brief	Header file for access to movementcommands functions.
*
* manual mode height to change
* auto mode accumulated height
*/

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

/* Type value */
#define MANUAL ((uint8_t) 0)
#define AUTO ((uint8_t) 1)

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
void processMovementCommand(int identifier);

#endif /* MOVEMENTCOMMANDS_H */