/*************************************************************************
 * @file stab_sim.c
 * @brief This is a small simulator that creates random value as 
 *               output the gyroscope and acceleometer. The simulator 
 *               returns a vector with x, y and z values randomly 
 *               generated.
 * @author Adam Debbiche 	       
 * @date 05/04/2011
 * @history 
 *    04/04/2011: Initial version // Adam
 *    08/04/2011: Removed the pipe version, the sim now works when it is
 *                invoked. Added comments to each function.
 *                Added time as seed so values are always random.This was 
 *                a bug before. //Adam
 *    11/04/2011: Renamed file to stab_sim (was stab_gyro_sim) // Adam
 *    18/04/2011: Updated code to reflect coding standards
 *************************************************************************/
#if defined(PC) || defined(STAB)
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "stab.h"

/* 
 * Function prototype
 */
float gen_val(float a, float b);
struct vector init_sim(void);


/*
 * A vector struct that is returned by the simulator when invoked
 */
struct vector
{
  float x;
  float y;
  float z;
};


/*
 * Function to be called by other c files when a vector needs 
 * to be generated
 */
struct vector init_sim(void)
{
  struct vector vect;
  srand(time(NULL));
  vect.x = gen_val(-180.0, 360.0);
  vect.y = gen_val(-180.0, 360.0);
  vect.z = gen_val(-180.0, 360.0);

  return vect;
}


/*
 * Function that generates the actual random float
 */
float gen_val(float start, float end)
{ 
  return start + (int)( end * rand() / ( RAND_MAX + 1.0 ) );
}
#endif
