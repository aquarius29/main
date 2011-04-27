/*************************************************************************
 * @file stab_main.c 
 * @brief This is the main file that contains the init and run 
 *              functiion for the other groups to call (scheduler)
 *              
 * @author Adam Debbiche 	       
 * @date 05/04/2011
 * @history 
 *    05/04/2011: Initial version //Adam
 *    06/04/2011: Added description and comments //Adam
 *    18/04/2011: Updated the ifdef to reflect new scheduler code //Adam
 *                Updated code to reflect coding standards
 *    26/04/2011: Magn and accel is now read from here / integrated //Adam
 *    27/04/2011: Barometer code included //Adam
 **************************************************************************/
#ifdef PC 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stab_interface.h"
#include "stab.h"
#include "math.h"
#elif defined ARDUINO 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stab_interface.h"
#include "stab.h"
#include <Wire.h>
#include <WProgram.h>
#include "math.h"
#endif 
/************************************************************
 * Global variables used to save input/output of the algorithm:
 *    acc_vector: Holds the values of the accelerometer output (x, y, z)
 *    gyro_vector: Holds the values of the gyroscope output (x, y, z)
 *    filter_est: Output of the algorithm with (estimated vector) 
 ************************************************************/
struct vector
{
  float x;
  float y;
  float z;
};

struct baro_data
{
  int temp;
  long pressure;
};

struct vector gyro_vect;
struct vector accel_vect;
struct vector magn_vect;
struct baro_data baro;
struct vector filter_vect;
float heading; // heading from magnetometer
void convert_accel_raw_to_deg();
/*
 * Inits the main hardware components of the shield
 * A LOT OF CHANGES EXPECTED 
 */
int16_t stab_init(void)
{
  // code to init the hardware goes in here as well
#if defined PC 
  init_filter();
#elif defined ARDUINO
  init();
  Serial.begin(9600);
  Wire.begin();
  init_gyro_hardware();
  init_magn_hardware();
  init_baro_hardware();
#endif
  return 0; 

}

/*
 *  Runs the code when the scheduler calls it
 */
int16_t stab_run(void)
{
#ifdef PC
  gyro_vect = init_sim();
  accel_vect = init_sim();
  
  filter_vect.x = comp_filter(accel_vect.x, gyro_vect.y, filter_vect.x); // filtered pitch angle
  filter_vect.y = comp_filter(accel_vect.y, gyro_vect.x, filter_vect.y); // filtered roll angle
  //filter_est[2] = comp_filter(acc_vector[2], gyro_vect[2], filter_est[2]);
  filter_vect.z = gyro_vect.z;
  
  printf("ESTIMATED X %f\n", filter_vect.x);
  printf("ESTMIATED Y %f\n", filter_vect.y);
  printf("ESTMIATED Z %f\n", filter_vect.z);
  
#elif defined ARDUINO
  while(1)
    {
      gyro_vect =  read_gyro_data();
      accel_vect = readAccel();
      convert_accel_raw_to_deg();
      magn_vect = read_magn_data();
      heading = (atan2(magn_vect.y , magn_vect.x)+M_PI)*180/M_PI;
      baro = read_baro_data();
      
      Serial.println("Gyro data now:");
      Serial.println(gyro_vect.x);
      Serial.println(gyro_vect.y);
      Serial.println(gyro_vect.z);
      Serial.println();
      
      Serial.println("Accel data now:");
      Serial.println(accel_vect.x);
      Serial.println(accel_vect.y);
      Serial.println(accel_vect.z);
      Serial.println(); 
      
      Serial.println("Magnetometer data now:");
      Serial.println(magn_vect.x);
      Serial.println(magn_vect.y);
      Serial.println(magn_vect.z);
      Serial.println(heading);
      Serial.println();

      Serial.println("Barometer data now:");
      Serial.println(baro.temp);
      Serial.println(baro.pressure);
      Serial.println();

      delay(1000);
    }
#endif
  
  return 0;
}


/************************************************************
* Converts the raw data from the accelerometer to the scaled value
* in degrees
************************************************************/
void convert_accel_raw_to_deg()
{
  float R = sqrt((pow(accel_vect.x, 2))+(pow(accel_vect.y, 2))+(pow(accel_vect.z, 2)));
  accel_vect.x = acos(accel_vect.x/R);
  accel_vect.y = acos(accel_vect.y/R);
  accel_vect.z = acos(accel_vect.z/R);

}
