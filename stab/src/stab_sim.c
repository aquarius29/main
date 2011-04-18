/*************************************************************************
  File: stab_sim.c
  Description: This is a small simulator that creates random value as output
               the gyroscope and acceleometer. The simulator returns a vector
               with x, y and z values randomly generated.
  Authors: Adam Debbiche 	       
  Created: 05/04/2011
  Log: 
     04/04/2011: Initial version // Adam
     08/04/2011: Removed the pipe version, the sim now works when it is
                 invoked. Added comments to each function.
                 Added time as seed so values are always random.This was 
                 a bug before. //Adam
     11/04/2011: Renamed file to stab_sim (was stab_gyro_sim) // Adam
*************************************************************************/
#ifdef PC
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "stab.h"
//#include <ltstdlib.h>

/* Function prototype*/
float gen_val(float a, float b);
struct vector init_sim(void);


/* A vector struct that is returned by the simulator when invoked*/
struct vector
{
  float x;
  float y;
  float z;
};


/*
  Function to be called by other c files when a vector needs to be generated
*/
struct vector init_sim(void)
{
  struct vector vect;

  vect.x = gen_val(-180.0, 360.0);
  vect.y = gen_val(-180.0, 360.0);
  vect.z = gen_val(-180.0, 360.0);

  
  return vect;
}


/*
  Function that generates the actual random float
*/
float gen_val(float start, float end)
{ 
  srand(time(NULL));
  return start + (int)( end * rand() / ( RAND_MAX + 1.0 ) );
}

#endif
