/******************************************************************************
  File: filter.c
  Description: This is a small simulator that creates random value as output
               the gyroscope and acceleometer 
  Authors: Adam Debbiche 	       
  Created: 05/04/2011
  Log: 
     04/04/2011: Initia
     8/04/2011: Added description and comments
*******************************************************************************/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float gen_val(float a, float b);

struct vector
{
  float x;
  float y;
  float z;
};


struct vector init_sim(void)
{
  struct vector rand;
      rand.x = gen_val(-180.0, 360.0);
      rand.y = gen_val(-180.0, 360.0);
      rand.z = gen_val(-180.0, 360.0);
      
      printf("%f\n", rand.x);
      printf("%f\n", rand.y);
      printf("%f\n", rand.z);
      
      return rand;
      // fflush(stdout);
      //sleep(1);
  
}


float gen_val(float start, float end)
{ 
  return start + (int)( end * rand() / ( RAND_MAX + 1.0 ) );
}
