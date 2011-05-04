
#include "mov_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KP 1
#define KI  1
#define KD 1


/*
 * PID CONTROLLER -> ANGLES IN RADIANS
 */

extern int old_x_desired;
extern int old_y_desired;
extern int old_z_desired;

int measured_angleX;
int measured_angleY;
int measured_angleZ;

int old_angleX;
int old_angleY;
int old_angleZ;

int old_error_angleX = 0;
int old_error_angleY = 0;
int old_error_angleZ = 0;

int old_error_angleX2 = 0;
int old_error_angleY2 = 0;
int old_error_angleZ2 = 0;

int change_in_time;



void stabL(void){

    printf("stab!");
}

/*
 * PID system is based on the equation and information on wikipedia: http://en.wikipedia.org/wiki/PID_controller
 */

int error_calc(int desired, int measured)
{
  return  desired - measured;
}

//proportional gain
//The proportional response can be adjusted by multiplying the error by a constant Kp, called the proportional gain.
int gain(int old, int current){
    return KP * (current - old);
}

//integral gain
//The contribution from the integral term is proportional to both
//the magnitude of the error and the duration of the error. 
int integral(int errorX){
    return KI * duration * errorX;
}


//derivative gain
//The derivative of the process error is calculated by determining the slope of the error over time 
//and multiplying this rate of change by the derivative gain Kd.
int derivative(int gain, int newChange, int oldChange,int oldchange2){
    return  (KD/duration) * gain * (newChange - 2 * oldChange + oldchange2);
}


int pid_X(void)
{
  int desired_angleX = old_x_desired;
  int errorX = error_calc(desired_angleX, measured_angleX);

  int x = old_angleX + gain(errorX,old_error_angleX) + integral(errorX) + derivative(gain(errorX,old_error_angleX),errorX,old_error_angleX, old_error_angleX2);
  
 old_error_angleX = errorX;
 old_error_angleX2 = old_error_angleX;
 old_angleX = x;    
 
 return x;
}

int pid_Y(void)
{
int desired_angleY = old_y_desired;
int errorY = error_calc(desired_angleY, measured_angleY);

 int y = old_angleY + gain(errorY,old_error_angleY) + integral(errorY) + derivative(gain(errorY,old_error_angleY),errorY,old_error_angleY, old_error_angleY2);

 old_error_angleY = errorY;
 old_error_angleY2 = old_error_angleY;
 old_angleY = y;    

 return y;
}

int pid_Z(void)
{
 int desired_angleZ = old_y_desired;
 int errorZ = error_calc(desired_angleZ, measured_angleZ);

 int z = old_angleZ + gain(errorZ,old_error_angleZ) + integral(errorZ) + derivative(gain(errorZ,old_error_angleZ),errorZ,old_error_angleZ, old_error_angleZ2);

 old_error_angleZ = errorZ;
 old_error_angleZ2 = old_error_angleZ;
 old_angleZ = z;    
 return z;
}


