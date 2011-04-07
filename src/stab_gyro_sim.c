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


/* int main(void) */
/* { */

/*   while(1) */
/*     { */
/*       float gyro_x = gen_val(-180.0, 360.0); */
/*       float gyro_y = gen_val(-180.0, 360.0); */
/*       float gyro_z = gen_val(-180.0, 360.0); */
      
      
/*       float acce_x = gen_val(-180.0, 360.0); */
/*       float acce_y = gen_val(-180.0, 360.0); */
/*       float acce_z = gen_val(-180.0, 360.0); */
      
/*       printf("%f\n", gyro_x); */
/*       printf("%f\n", gyro_y); */
/*       printf("%f\n", gyro_z); */

/*       printf("%f\n", acce_x); */
/*       printf("%f\n", acce_y); */
/*       printf("%f\n", acce_z); */
      
/*       fflush(stdout); */
/*       sleep(1); */
/*     } */

/*   return 0; */

/* } */

struct vector init_sim(void)
{
  //while(1)
  // {
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
      // }
}


float gen_val(float start, float end)
{ 
  return start + (int)( end * rand() / ( RAND_MAX + 1.0 ) );
}
