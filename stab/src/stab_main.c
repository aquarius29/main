#ifdef PC
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stab_interface.h"
#include "stab.h"
#elif defined ARDUINO
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stab_interface.h"
#include "stab.h"
#include <Wire.h>
#include <WProgram.h>
#endif 
/************************************************************
  Global variables used to save input/output of the algorithm:
     acc_vector: Holds the values of the accelerometer output (x, y, z)
     gyro_vector: Holds the values of the gyroscope output (x, y, z)
     filter_est: Output of the algorithm with (estimated vector) 
************************************************************/
struct vector
{
  float x;
  float y;
  float z;
};

struct vector gyro_vect;
struct vector accel_vect;
struct vector filter_vect;


/*
  Inits the main hardware components of the shield
  A LOT OF CHANGES EXPECTED 
*/
int16_t stab_init(void)
{
  // code to init the hardware goes in here as well
#ifdef PC
  init_filter();
#elif defined ARDUINO
  init();
  Serial.begin(9600);
  Wire.begin();
  init_gyro_hardware();
#endif
  return 0; 

}

/*
  Runs the code when the scheduler calls it
*/
int16_t stab_run(void)
{
#ifdef PC 
  gyro_vect = init_sim();
  accel_vect = init_sim();
  
  filter_vect.x = comp_filter(accel_vect.x, gyro_vect.y, filter_vect.x);
  filter_vect.y = comp_filter(accel_vect.y, gyro_vect.x, filter_vect.y);
  //filter_est[2] = comp_filter(acc_vector[2], gyro_vect[2], filter_est[2]);
  filter_vect.z = gyro_vect.z;
  
  printf("ESTIMATED X %f\n", filter_vect.x);
  printf("ESTMIATED Y %f\n", filter_vect.y);
  printf("ESTMIATED Z %f\n", filter_vect.z);
  
#elif defined ARDUINO
  read_gyro_data();
  readAccel();
#endif
  
  return 0;
}
