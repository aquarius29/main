/*
 * file:         ca_object_calculation.c
 * brief:        calculations involved with objects movements detected.
 * author:       Amber Olsson
 * date:         2011-04-26
 * version:      0.1
 * history       2011-03-21 create the file
 *               2011-05-10 Yanling Jin- add method: distance_differ 
 *
 * detail:       
 */
#include <stdlib.h>
#include <stdio.h>
#include "ca_interface.h"

#define IGNORINGLITTLECHANGE 10

/*
 * Receives two sets of ir distances, 
 * First set is old ir distance, second one is the current distance measured by ir
 * return the distance difference of this two sets of distances
 * The resturn value is the input for method moving_closer
 */
int *distance_differ(int ir1, int ir2, int ir3, int ir4, 
							   int ir11, int ir22, int ir33, int ir44)
{
	int *distance_diff = (int *) calloc(4, sizeof(int));
    *distance_diff = ir11 - ir1;
    *(distance_diff + 1) = ir22 - ir2;
    *(distance_diff + 2) = ir33- ir3;
    *(distance_diff + 3) = ir44- ir4;

	return distance_diff;
}


/*
 * Receives array of differences where values are [Value2 - Value1, Value2 - Value1, Value2 - Value1]
 * where value1 is the first measurement and value2 is the second measurement. 
 * 0 is moving closer
 * 1 is moving farther away
 */
unsigned char* moving_closer (int* irDistances)
{
  
	//an array of 4 values 0 or 1, to be returned
	unsigned char *movements = (unsigned char *)calloc(4, sizeof(unsigned char) );

	unsigned char i;
	for(i = 0; i < 4; i++)
		{
			//** The IGNORINGLITTLECHANGE helps ignore sensor variations
			if(*(irDistances + i) + IGNORINGLITTLECHANGE <= 0) 
				*(movements + i)= 1;	
			else
				*(movements + i) = 0;
		}

	return movements;
}
