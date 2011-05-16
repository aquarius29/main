<<<<<<< HEAD
/*************************************************************************
 * @file filter.c
 * @brief combines the data from the sensors (gyroscope/accelerometer)
 *        in order to eliminate the noise/drift
 * @author Adam Debbiche & Yuwen He	       
 * @date 05/04/2011
 * @history 
 *    05/04/2011: Initial version
 *    06/04/2011: Added description and comments
 *    18/04/2011: Updated code to reflect coding standards
 **************************************************************************/
=======
/******************************************************************************
  File: filter.c
  Description: combines the data from the sensors (gyroscope/accelerometer)
               in order to eliminate the noise/drift
  Authors: Adam Debbiche & Yuwen He	       
  Created: 05/04/2011
  Log: 
     05/04/2011: Initial version
     06/04/2011: Added description and comments
*******************************************************************************/
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stab.h"


/************************************************************
<<<<<<< HEAD
 * Gyro macros related to the complimentary filter:
 *   hpfc: high pass filter coefficient
 *   lpfc: low pass filter coefficient
 *   dt: rate of how often the data is read from the sensors
 *   SSF: Sensitivity scale factor
 *************************************************************/
=======
 Gyro macros related to the complimentary filter:
    hpfc: high pass filter coefficient
    lpfc: low pass filter coefficient
    dt: rate of how often the data is read from the sensors
    SSF: Sensitivity scale factor
*************************************************************/
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
#define hpfc 0.98 //To be changed 
#define lpfc 0.02 //To be changed 
#define time_constant 3 // To be changed
#define dt 0.06 // To be changed
#define SSF 14.375 // Gyro's Sensitivity Scale Factor


/************************************************************
<<<<<<< HEAD
 * Functions prototypes
 ************************************************************/
void init_filter(void);
float comp_filter(float acc_scal, float gyro_scal, float old_est);

/************************************************************
 * Global variables used to save input/output of the algorithm:
 *    acc_vector: Holds the values of the accelerometer output (x, y, z)
 *    gyro_vector: Holds the values of the gyroscope output (x, y, z)
 *    filter_est: Output of the algorithm with (estimated vector) 
 ************************************************************/
=======
  Functions prototypes
************************************************************/
void init_filter(void);
float comp_filter(float acc_scal, float gyro_scal, float old_est);
void convert_acce_raw_to_deg(float acc_x, float acc_y, float acc_z);
float convert_gyro_raw_to_deg_s(float a);


/************************************************************
  Global variables used to save input/output of the algorithm:
     acc_vector: Holds the values of the accelerometer output (x, y, z)
     gyro_vector: Holds the values of the gyroscope output (x, y, z)
     filter_est: Output of the algorithm with (estimated vector) 
************************************************************/
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
float acc_vector[2];
float gyro_vector[2];
float filter_est[2];


/************************************************************
<<<<<<< HEAD
 * This is where the algorithm calculates the best estimate by combining 
 * the data from the accelerometer and gyroscope together. The noise and 
 * drift from the sensors is eliminated here. 
=======
  Main method where the main loop of the algortihm is run
************************************************************/
/* int main(void) */
/* { */

/*   init_filter();   */
/*   float acc_x; */
/*   float acc_y; */
/*   float acc_z; */
  
/*   float gyro_x_raw; */
/*   float gyro_y_raw; */
/*   float gyro_z_raw; */

/*   float gyro_x = convert_gyro_raw_to_deg_s(gyro_x_raw); */
/*   float gyro_y = convert_gyro_raw_to_deg_s(gyro_y_raw); */
/*   float gyro_z = convert_gyro_raw_to_deg_s(gyro_z_raw); */

/*   while(1) */
/*     {   */
/*       scanf("%f", &gyro_x); */
/*       scanf("%f", &gyro_y); */
/*       scanf("%f", &gyro_z); */
      
/*       scanf("%f", &acc_x); */
/*       scanf("%f", &acc_y); */
/*       scanf("%f", &acc_z); */
      
/*       printf("Sim. Gyro x: %f\n", gyro_x); */
/*       printf("Sim. Gyro y: %f\n", gyro_y); */
/*       printf("Sim. Gyro z: %f\n", gyro_z); */
      
/*       printf("Sim. Acce x: %f\n", acc_x); */
/*       printf("Sim. Acce y:  %f\n", acc_y); */
/*       printf("Sim. Acce z: %f\n", acc_z); */
      
/*       convert_acce_raw_to_deg(acc_x, acc_y, acc_z); */
/*       filter_est[0] = comp_filter(acc_vector[0], gyro_vector[1], filter_est[0]); */
/*       filter_est[1] = comp_filter(acc_vector[1], gyro_vector[0], filter_est[1]); */
/*       //filter_est[2] = comp_filter(acc_vector[2], gyro_vect[2], filter_est[2]); */
/*       filter_est[2] = gyro_vector[2]; */
      
/*       printf("ESTIMATED X %f\n", filter_est[0]); */
/*       printf("ESTMIATED Y %f\n", filter_est[1]); */
/*       printf("ESTMIATED Z %f\n", filter_est[2]); */
      
/*       sleep(1); */
/*     } */
  
  
/*   return 0; */
  
/* } */


/************************************************************
  This is where the algorithm calculates the best estimate by combining 
  the data from the accelerometer and gyroscope together. The noise and drift 
  from the sensors is eliminated here. 
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
 ************************************************************/
float comp_filter(float acc_scal, float gyro_scal, float old_est)
{
  
  return ( 
	  hpfc * (old_est + (gyro_scal * dt)) + 
	  (lpfc * acc_scal) 
	   );  
}


/************************************************************
<<<<<<< HEAD
 * This method initializes the filter and sensors data before the algorithm
 * starts running
 ************************************************************/
=======
  This method initializes the filter and sensors data before the algorithm
  starts running
************************************************************/
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
void init_filter()
{
  int i;
  for(i=0; i<2; i++)
    {
      acc_vector[i] = 0;
      gyro_vector[i] = 0;
      filter_est[i] = 0;
    }  
}


<<<<<<< HEAD



=======
/************************************************************
  Converts the raw data from the gyroscope to the scaled value
  in degrees/s
************************************************************/
float convert_gyro_raw_to_deg_s(float a)
{
  return a / SSF;
}


/************************************************************
  Converts the raw data from the accelerometer to the scaled value 
  in degrees
************************************************************/
void convert_acce_raw_to_deg(float acc_x, float acc_y, float acc_z)
{
  float R = sqrt((acc_x*acc_x)*(acc_y*acc_y)*(acc_z*acc_z));
  acc_vector[0] = acos(acc_x/R);
  acc_vector[1] = acos(acc_y/R);
  acc_vector[2] = acos(acc_z/R);
}
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
