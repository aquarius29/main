/*
* Author: Jarryd Hall
* Purpose: Drone Controls
*
*/

#include "Controls.h"

// Create a movement order
void createMovementOrder(char* _order, int _direction, int _height)
{
	controlOrder *order = malloc(sizeof(controlOrder));
	order->order = _order;
	order->direction = _direction;
	order->height = _height;
	// Function from interface to send order goes here e.g. InterfaceSendOrder(order);
	free(order);
}
