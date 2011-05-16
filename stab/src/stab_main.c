<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
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
<<<<<<< HEAD
 *    26/04/2011: Magn and accel is now read from here / integrated //Adam
 *    27/04/2011: Barometer code included //Adam
 *    08/05/2011: Removed some stuff and while loop //Adam
 *    09/05/2011: Completed message passing to protocol, 
 *                fixed some coding standards //My
 *    12/05/2011: Tiny changes..movement group wants raw data from Gyrosensor instead of Accelerometer //Yuwen
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
 **************************************************************************/
#ifdef PC 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stab_interface.h"
#include "stab.h"
<<<<<<< HEAD
#include "math.h"
//#include <proto_lib.h>

=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
#elif defined ARDUINO 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stab_interface.h"
#include "stab.h"
#include <Wire.h>
#include <WProgram.h>
<<<<<<< HEAD
#include "math.h"
/*#include <proto_lib.h>*/
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
#endif 
/************************************************************
 * Global variables used to save input/output of the algorithm:
 *    acc_vector: Holds the values of the accelerometer output (x, y, z)
 *    gyro_vector: Holds the values of the gyroscope output (x, y, z)
 *    filter_est: Output of the algorithm with (estimated vector) 
 ************************************************************/
struct vector
{
<<<<<<< HEAD
    float x;
    float y;
    float z;
};

struct baro_data
{
    int temp;
    long pressure;
    float height;
=======
#include "stab_sched.h"
#include "stab.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
  float x;
  float y;
  float z;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
};

struct vector gyro_vect;
struct vector accel_vect;
<<<<<<< HEAD
<<<<<<< HEAD
struct vector magn_vect;
struct baro_data baro;
struct vector filter_vect;
float heading; // heading from magnetometer
void convert_accel_raw_to_deg();
float data(float x, float y, float z);

=======
struct vector filter_vect;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16

/*
 * Inits the main hardware components of the shield
 * A LOT OF CHANGES EXPECTED 
 */
int16_t stab_init(void)
{
  // code to init the hardware goes in here as well
#if defined PC 
<<<<<<< HEAD
    //init_filter();
#elif defined ARDUINO
    init();
    init_filter();
    Serial.begin(9600);
    Wire.begin();
    init_gyro_hardware();
    init_magn_hardware();
    init_baro_hardware();
#endif
    return 0; 
=======
  init_filter();
#elif defined ARDUINO
  init();
  Serial.begin(9600);
  Wire.begin();
  init_gyro_hardware();
#endif
  return 0; 
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16

}

/*
 *  Runs the code when the scheduler calls it
<<<<<<< HEAD
 *  The PC version uses a simulator that only includes 
 *  the gyroscope and accelerometer so the output
 *  is less accurate than the actual IMU hardware
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
 */
int16_t stab_run(void)
{
#ifdef PC
<<<<<<< HEAD
    gyro_vect = sim_vector();
    accel_vect = sim_vector();
    heading = sim_heading();
    baro = sim_baro();
    
    //UNCOMMENT THE FOLLOWING proto_ CALLS TO ACTIVATE MESSAGE SENDING.
    // THIS REQUIRES THE PROTOCOL CODE TO BE ACCESSIBLE
/*    proto_stabWriteAttitude(gyro_vect.y, gyro_vect.x, gyro_vect.z);*/
/*    proto_stabWriteGyro(gyro_vect.x, gyro_vect.y, gyro_vect.z);*/
/*    proto_stabWriteHeading(heading);*/
/*    proto_stabWriteHeight(baro.height);*/
    
    
    //gyro_vect = init_sim();
    //accel_vect = init_sim();
  
/*    filter_vect.x = comp_filter(accel_vect.x, gyro_vect.y, filter_vect.x); // filtered pitch angle*/
/*    filter_vect.y = comp_filter(accel_vect.y, gyro_vect.x, filter_vect.y); // filtered roll angle*/
/*    filter_est[2] = comp_filter(acc_vector[2], gyro_vect[2], filter_est[2]); // filtered yaw angle*/
/*    filter_vect.z = gyro_vect.z;*/

/*    printf("ESTIMATED X %f\n", filter_vect.x);*/
/*    printf("ESTMIATED Y %f\n", filter_vect.y);*/
/*    printf("ESTMIATED Z %f\n", filter_vect.z);*/
  
#elif defined ARDUINO
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
    
    float d = data(magn_vect.x, magn_vect.y, magn_vect.z);
    Serial.println("Magnetometer data now:");
    Serial.println(magn_vect.x);
    Serial.println(magn_vect.y);
    Serial.println(magn_vect.z);
    Serial.println(heading);
    Serial.print("The constant is: ");
    Serial.println(d);
    Serial.println();

    Serial.println("Barometer data now:");
    Serial.println(baro.temp);
    Serial.println(baro.pressure);
    Serial.println();
    filter_vect.x = comp_filter(accel_vect.x, gyro_vect.y, filter_vect.x); // filtered pitch angle
    filter_vect.y = comp_filter(accel_vect.y, gyro_vect.x, filter_vect.y); // filtered roll angle
    filter_vect.z = comp_filter(heading, gyro_vect.z, filter_vect.z); // filtered yaw angle
     
/*    proto_stabWriteAttitude(filter_vect.y, filter_vect.x, filter_vect.z);*/
/*    proto_stabWriteGyro(gyro_vect.x, gyro_vect.y, gyro_vect.z);*/
/*    proto_stabWriteHeading((int)heading);*/
/*    proto_stabWriteHeight(baro.height);*/
      
    Serial.println("Filtered data now:");
    Serial.println(filter_vect.x);
    Serial.println(filter_vect.y);
    Serial.println(filter_vect.z);
    Serial.println();

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

float data(float x, float y, float z)
{
    return sqrt((pow(x, 2))+(pow(y, 2))+(pow(z, 2)));
=======
struct vector filter_vect;


int16_t stab_init(void)
{
  // code to init the hardware goes in here as well
  init_filter();
  return 0; 

}


int16_t stab_run(void)
{
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
  gyro_vect = init_sim();
  accel_vect = init_sim();
  
  filter_vect.x = comp_filter(accel_vect.x, gyro_vect.y, filter_vect.x);
  filter_vect.y = comp_filter(accel_vect.y, gyro_vect.x, filter_vect.y);
  //filter_est[2] = comp_filter(acc_vector[2], gyro_vect[2], filter_est[2]);
  filter_vect.z = gyro_vect.z;
  
<<<<<<< HEAD
  //#ifdef DEBUG 
  printf("*** Inside the actual stab_run in stan_main.c\n");
  printf("ESTIMATED X %f\n", filter_vect.x);
  printf("ESTMIATED Y %f\n", filter_vect.y);
  printf("ESTMIATED Z %f\n", filter_vect.z);
  //#endif /*DEBUG*/  
  
  return 0;
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
  printf("ESTIMATED X %f\n", filter_vect.x);
  printf("ESTMIATED Y %f\n", filter_vect.y);
  printf("ESTMIATED Z %f\n", filter_vect.z);
  
#elif defined ARDUINO
  gyro_vect =  read_gyro_data();
  Serial.println(gyro_vect.x);
  Serial.println(gyro_vect.y);
  Serial.println(gyro_vect.z);
  readAccel();
#endif
  
  return 0;
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
}
