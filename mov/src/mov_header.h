/*****************************************************************************
 * Product: mov_header.h
 * Version: 0.1
 * Created: April 4 2011
 *
 * Movement/CA Group
 *****************************************************************************/
#include <stdio.h>

int read_input(FILE *stdin);

/* This structure contains data which we desire to reach part of them we get
 * from navigation group, part from our group. Which data from what group
 * is commented
 */
struct data {

// This block of data from navigation group
	char *type;
	char *order;
	int height;
	int distance;
	int speed;

// This block of data from our group
	int yaw;
	int pitch;
	int roll;
};

