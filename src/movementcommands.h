/*
* @author: Jarryd Hall
*/

#ifndef MOVEMENTCOMMANDS_H
#define MOVEMENTCOMMANDS_H

/* MovementCommand struct */
typedef struct 
 {
	char type;  /* (manual/auto) */
	char order; /* (lift off/ hovering/ moving/ land) */
	int height;
	int distance;
	int yaw; /* vertical */
}
movementCommand;

/* Create a movement command . 0 for manual(From UI), 1 for automatic(abstract navigation). */
void sendautomovementcommand(char type, char order , int height, int distance, int yaw);

#endif /* MOVEMENTCOMMANDS_H */