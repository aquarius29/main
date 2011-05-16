/*
<<<<<<< HEAD
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
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
  .     IR1(FRONT)

  IR3(LEFT)   IR4(RIGHT)

  .     IR2(BACK)

  {front, back, left, right,hover}

*/
<<<<<<< HEAD
=======
  /*****************************************************************************
  * Product: collision_logic.c
  * Version: 0.1
  * Creators: Jin, Amber
  * Created: March 29 2011
  * History:
  * March 30th, 2011 - Amber: Changed int types to unsigned char for booleans.
  *                           Changed to bitwise operation for changing values
  *                      Jin: Add method to get the final destination
  * March 31st, 2011 -   Jin: Add moving_closer_filter mothod
  *
  * Movement/CA Group
  *****************************************************************************/
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16

#include <stdlib.h>
#include <stdio.h>

#include "ca_interface.h"

<<<<<<< HEAD
/* the speed control variables */
=======
//the speed control variables
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
#define HOVERSPEED 5
#define SLOWSPEED 25
#define MEDIUMSPEED 50
#define FASTSPEED 75

<<<<<<< HEAD
/* the dangerzone varibales according to the speed */
=======
//the dangerzone varibales according to the speed
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
#define HOVERZONE 20
#define SLOWZONE 50
#define MEDIUMZONE 75
#define FASTZONE 100
#define MADZONE 150

<<<<<<< HEAD
/* the current flying directions */
=======
//the current flying directions
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
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
<<<<<<< HEAD
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
=======
  int dangerzone;

  if(speed<HOVERSPEED)
    dangerzone=HOVERZONE;
  else if(speed<SLOWSPEED && speed>=HOVERSPEED)
    dangerzone=SLOWZONE;
  else if(speed<MEDIUMSPEED&&speed>=SLOWSPEED)
    dangerzone=MEDIUMZONE;
  else if(speed<FASTSPEED&&speed>=MEDIUMSPEED)
    dangerzone=FASTZONE;
  else
    dangerzone = MADZONE;
  
  return dangerzone;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
}


/*
 * Decides if each ir is triggered or not
 * take the distance the ir measured, and the distance of the dangerzone
 * return 0 if the ir is NOT triggered, 1 as triggered
 * return an array of irs.
 */
<<<<<<< HEAD
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
=======
unsigned char* distance_filter(int dangerzone,int ir1, int ir2, int ir3,int ir4)
{

  unsigned char irBoolean1 = 1;
  unsigned char irBoolean2 = 1;
  unsigned char irBoolean3 = 1;
  unsigned char irBoolean4 = 1;

  if(ir1>dangerzone)
    irBoolean1 = 0;

  if(ir2>dangerzone)
    irBoolean2 = 0;

  if(ir3>dangerzone)
    irBoolean3 = 0;

  if(ir4>dangerzone)
    irBoolean4 = 0;

  //Allocates an array of 4 unsigned characters
  unsigned char *irBooleans= (unsigned char *)calloc(4, sizeof(unsigned char)) ;
  *irBooleans=irBoolean1;
  *(irBooleans+1)=irBoolean2;
  *(irBooleans+2)=irBoolean3;
  *(irBooleans+3)=irBoolean4;
    
  //returns the unsigned char array of 0 or 1 for each IR sensor
  return irBooleans;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
}


/*
 * Filter the directions options for the quadrocopter
 * according to the boolean value of four irs
 * return the boolean value of 5 directions (front, back, left, right, hover)
 */
<<<<<<< HEAD
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
=======
unsigned char* ir_filter(unsigned char *irBooleans)
{
  unsigned char front = 1;
  unsigned char back = 1;
  unsigned char left = 1;
  unsigned char right = 1;
  unsigned char hover = 1;
 
  //ir1 detects collision
  if (*irBooleans==1)
    front = 0;

  //ir2 detects collision
  if(*(irBooleans+1)==1)
    back =0;

  //ir3 detects collision
  if(*(irBooleans+2)==1)
    left =0;

  //ir4 detects collsion
  if(*(irBooleans+3)==1)
    right =0;

  unsigned char *directions=(unsigned char *) calloc(5, sizeof(unsigned char)) ;
  *directions=front;
  *(directions+1)=back;
  *(directions+2)=left;
  *(directions+3)=right;
  *(directions+4)=hover;

  return directions;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
}


/*
 *Filter the direction options for the quadrocopter
 *According to the direction the quadrocopter is flying towards
 *return the boolean value of 5 directions (front, back, left, right, hover)
 */
<<<<<<< HEAD
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
=======
unsigned char *currentDirection_filter(int currentDirection,unsigned char *directions)
{
  //face to sensor 1
  if(currentDirection==FRONT)
    *(directions+1)= 0;//back

  if(currentDirection==BACK)
    *(directions) = 0;//front

  if(currentDirection==LEFT)
    *(directions+3) = 0;//right

  if(currentDirection==RIGHT)
    *(directions+2) = 0;//left

  return directions;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
}

/*
 *Filter the direction options for the quadrocopter
 *According to the objects which is moving towards
 *return the boolean value of 5 directions (front, back, left, right, hover)
 */
<<<<<<< HEAD
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
=======
unsigned char *moving_closer_filter(unsigned char *is_moving, unsigned char*directions)
{

  if(*is_moving==1)//moving towards front
    {
      *(directions) = 0;//can't go front
      *(directions+4) = 0;//can't hover
    }
  if(*(is_moving+1)==1)//moving towards back
    {
      *(directions+1) = 0;//can't go back
      *(directions+4) = 0;//can't hover
    }
  if(*(is_moving+2)==1)//moving towards left
    {
      *(directions+2) = 0;//can't go left
      *(directions+4) = 0;//can't hover
    }
  if(*(is_moving+3)==1)//moving towards right
    {
      *(directions+3) = 0;//can't go right
      *(directions+4) = 0;//can't hover
    }

 return directions;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
}

/*
 * Filter the direction options for the quadrocopter
 * return the first available direction in the list
 * return the integer, 1 front 2 back 3 left 4 right 0 hover
 */
int final_direction(int currentDir, unsigned char *directions)
{
<<<<<<< HEAD
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
=======
  int i;
  int dir=6;

  for (i=0;i<5;i++)
    {
      //return the first one which fullfill the requirement 
      if(*(directions+i)==1){
	if(i==4)
	  {
	    dir= 0;
	  }
	else
	  {
	    dir=i+1;
	  }	
	break;
      }	
    }

  if(*(directions+currentDir-1)==1)
    {
      dir=currentDir;
    }

  return dir;
}


/*
 * translate the 0 and 1
 * return 0 as not ok, 1 as ok
 */
char * translate(int i)
{
  char *result;
  if (i==0)
    result ="not ok";
  else
    result ="ok";

  return result;
}

/*translate the output of IR*/
void outputIR(unsigned char *result)
{
  printf("\n detects an object at ");
  if(*result == 1)
    printf("\n Front ");

  if(*(result + 1) == 1)
    printf("\n Back ");

  if(*(result + 2) == 1)
    printf("\n Left ");

  if(*(result + 3) == 1)
    printf("\n Right ");
}

/*translate the current direction*/
void outputdirection(int direction)
{
  // {front, back, left, right,hover}
  switch (direction)
    {
    case 0:
      printf("Hover \n");
      break;
    case 1:
      printf("Front \n");
      break;
    case 2:
      printf("Back \n ");
      break;
    case 3:
      printf("Left \n ");
      break;
    case 4:
      printf("Right \n");
      break;
    default:
      printf("NO PLACE TO GO\n");
    }
}


/*translate the result of the directions options*/
void print_result(unsigned char *result)
{
  int i;
  char *answer;

  for (i=0;i<5;i++)
    {
      answer=translate ( *(result+i));

      if (i==0)
	printf("Front is %s\n",answer);
      
      if (i==1)
	printf("Back is %s\n",answer);
      
      if (i==2)
	printf("Left is %s\n", answer);
      
      if (i==3)
	printf("Right is %s\n",answer);
      
      if (i==4)
	printf("Hover is %s\n", answer);
    }
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
}
