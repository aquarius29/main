/*
 * file:         ca_object_calculation.c
 * brief:        calculations involved with objects movements detected.
 * author:       Amber
 * date:         2011-04-26
 * version:      0.1
 * history       2011-03-21 create the file
 *
 * detail:       
 */
#include <stdlib.h>
#include <stdio.h>
#include "ca_interface.h"

#define IGNORINGLITTLECHANGE 10

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
