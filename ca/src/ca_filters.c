/*
 * file:         ca_filters.c
 * brief:
 * author:       Yanling Jin, Amber Olsson
 * date:         2011-04-26
 * version:      0.1
 * history       2011-03-29  Jin - create the file\n
 *               2011-03-30  Amber - Changed int types to unsigned char for booleans.
 *                                   Changed to bitwise operation for changing values
 *                           Jin - Add method to get the final destination
 *               2011-03-31  Jin - Add moving_closer_filter mothod
 * detail:
 */


/*
  .     IR1(FRONT)

  IR3(LEFT)   IR4(RIGHT)

  .     IR2(BACK)

  {front, back, left, right,hover}

*/

#include <stdlib.h>
#include <stdio.h>

#include "ca_interface.h"

/* the speed control variables */
#define HOVERSPEED 5
#define SLOWSPEED 50
#define MEDIUMSPEED 100
#define FASTSPEED 150

/* the dangerzone varibales according to the speed */
#define HOVERZONE 25
#define SLOWZONE 50
#define MEDIUMZONE 75
#define FASTZONE 100
#define MADZONE 130

/* the current flying directions */
#define FRONT 1
#define BACK 2
#define LEFT 3
#define RIGHT 4
#define HOVER 0


/*
 * filter the dangerous zone for the quadrocopter to react according to the speed
 * return the dangerous zone in "cm"
 */
int speed_filter(int speed)
{
    int dangerzone;

    if (speed < HOVERSPEED) {
		dangerzone = HOVERZONE;
    } else if (speed < SLOWSPEED && speed >= HOVERSPEED) {
		dangerzone = SLOWZONE;
    } else if (speed < MEDIUMSPEED && speed >= SLOWSPEED) {
		dangerzone = MEDIUMZONE;
    } else if (speed < FASTSPEED && speed >= MEDIUMSPEED) {
		dangerzone = FASTZONE;
    } else {
		dangerzone = MADZONE;
    }

    return dangerzone;
}


/*
 * Decides if each ir is triggered or not
 * take the distance the ir measured, and the distance of the dangerzone
 * return 0 if the ir is NOT triggered, 1 as triggered
 * return an array of irs.
 */
unsigned char *distance_filter(int dangerzone, int ir1, int ir2, int ir3, int ir4)
{

    unsigned char irBoolean1 = 1;
    unsigned char irBoolean2 = 1;
    unsigned char irBoolean3 = 1;
    unsigned char irBoolean4 = 1;

    if (ir1 > dangerzone) {
		irBoolean1 = 0;
	}

    if (ir2 > dangerzone) {
		irBoolean2 = 0;
	}

    if (ir3 > dangerzone) {
		irBoolean3 = 0;
	}

    if (ir4 > dangerzone) {
		irBoolean4 = 0;
	}

    /* Allocates an array of 4 unsigned characters */
    unsigned char *irBooleans = (unsigned char *) calloc(4, sizeof(unsigned char));
    *irBooleans = irBoolean1;
    *(irBooleans + 1) = irBoolean2;
    *(irBooleans + 2) = irBoolean3;
    *(irBooleans + 3) = irBoolean4;

    /* returns the unsigned char array of 0 or 1 for each IR sensor */
	return irBooleans;
}


/*
 * Filter the directions options for the quadrocopter
 * according to the boolean value of four irs
 * return the boolean value of 5 directions (front, back, left, right, hover)
 */
unsigned char *ir_filter(unsigned char *irBooleans)
{
	unsigned char front = 1;
	unsigned char back = 1;
	unsigned char left = 1;
	unsigned char right = 1;
	unsigned char hover = 1;

	/* ir1 detects collision */
	if (*irBooleans == 1) {
		front = 0;
	}

	/* ir2 detects collision */
	if (*(irBooleans + 1) == 1) {
		back = 0;
	}

	/* ir3 detects collision */
	if (*(irBooleans + 2) == 1) {
		left = 0;
	}

	/* ir4 detects collsion */
	if (*(irBooleans + 3) == 1) {
		right = 0;
	}

	unsigned char *directions = (unsigned char *) calloc(5, sizeof(unsigned char));
	*directions = front;
	*(directions + 1) = back;
	*(directions + 2) = left;
	*(directions + 3) = right;
	*(directions + 4) = hover;

	return directions;
}


/*
 *Filter the direction options for the quadrocopter
 *According to the direction the quadrocopter is flying towards
 *return the boolean value of 5 directions (front, back, left, right, hover)
 */
unsigned char *currentDirection_filter(int currentDirection, unsigned char *directions)
{
    if (currentDirection == FRONT) {
		*(directions + 1) = 0;
    }
    if (currentDirection == BACK) {
		*(directions) = 0;
    }
    if (currentDirection == LEFT) {
		*(directions + 3) = 0;
    }
    if (currentDirection == RIGHT) {
		*(directions + 2) = 0;
    }
    return directions;
}

/*
 *Filter the direction options for the quadrocopter
 *According to the objects which is moving towards
 *return the boolean value of 5 directions (front, back, left, right, hover)
 */
unsigned char *moving_closer_filter(unsigned char *is_moving, unsigned char *directions)
{
    /* moving towards front */
    if (*is_moving == 1) {
		*(directions) = 0;
		*(directions + 4) = 0;
    }
    /* moving towards back */
	if (*(is_moving + 1) == 1) {
		*(directions + 1) = 0;
		*(directions + 4) = 0;
    }
    /* moving towards left */
	if (*(is_moving + 2) == 1) {
		*(directions + 2) = 0;
		*(directions + 4) = 0;
    }
    /* moving towards right */
	if (*(is_moving + 3) == 1) {
		*(directions + 3) = 0;
		*(directions + 4) = 0;
    }
    return directions;
}

/*
 * Filter the direction options for the quadrocopter
 * return the first available direction in the list
 * return the integer, 1 front 2 back 3 left 4 right 0 hover
 */
int final_direction(int currentDir, unsigned char *directions)
{
    int i;
    int dir = 6;

    for (i = 0; i < 5; i++) {
		/* return the first one which fullfill the requirement */
	    if (*(directions + i) == 1) {
			if (i == 4) {
				dir = 0;
			} else {
				dir = i + 1;
			}
			break;
		}
    }

    if (*(directions + currentDir - 1) == 1) {
		dir = currentDir;
    }
    return dir;
}
