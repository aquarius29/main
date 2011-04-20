/*****************************************************************************
  * Product: mov_stab.c
  * Version: 0.1
  * Created: April 19, 2011
  * History:
  * Author:         
  *
  *
  * Movement/CA
  *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "mov_header.h"

float diff_roll;
float diff_pitch;
float diff_yaw;

/*Calculate the differences on the roll pitch yaw.. the current with the desired*/

int Stab_roll(void)
{
  diff_roll = data.roll - sensor.roll;
  return roll;
}


int Stab_pitch(void)
{
  diff_pitch = data.pitch - sensor.pitch;
  return pitch;
}


int Stab_yaw(void)
{
  diff_yaw = data.yaw - sensor.yaw;
  return yaw;
}

int Stab_qc(void)
{
  if( diff_roll == 0 && diff_pitch == 0 && diff_yaw == 0){
      printf("\n correct angel when flatting \n");
  return 0;
  }
  else
  return 1;	
}







