/*****************************************************************************
  * Product: mov_stab.c
  * Version: 0.1
  * Created: April 19, 2011
  * History:
  * Author:  Maryam Sepasi,Sepideh Fazlmashhadi       
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

// to stabilize the roll angle, motor 2 & 4 should change
int stab_roll(void)
{
	
  diff_roll = abs(data.roll - sensor.roll);
  if (diff_roll == 0){
	return 0;
  }else if( 0 < diff_roll){
	while (diff_roll >0){	
	write_motor(0,-1,0,1);// it should be changed to 8 bits and put it in one character then pass that character to motor via protocol
	float new_diff_roll = abs(data.roll - sensor.roll);
	diff_roll = new_diff_roll;
  }
  return 0;
}


int Stab_pitch(void)
{
  diff_pitch = abs(data.pitch - sensor.pitch);
  if (diff_pitch == 0){
	return 0;
  }else {
	while (diff_pitch >0){	
	write_motor(1,0,-1,0);
	float new_diff_pitch = abs(data.pitch - sensor.pitch);
	diff_pitch = new_diff_pitch;
  }
  return 0;
}


int stab_yaw(void)
{
  diff_yaw = abs(data.yaw - sensor.yaw);
  if(diff_yaw == 0){
	return 0;
  }else if (diff_yaw < 180){
	while (diff_yaw > 0){
		write_motor(-1,1,-1,1);
		float new_diff_yaw = abs(data.yaw - sensor.yaw);
		diff_raw = new_diff_yaw;}
	} else {
		while (diff_yaw > 0){
		write_motor(1,-1,1,-1);
		float new_diff_yaw = abs(data.yaw - sensor.yaw);
		diff_raw = new_diff_yaw;
		}
	}
  return 0;
}

int stab_qc(void)
{
  if( sensor.roll == 0 && sensor.pitch == 0 && sensor.yaw == 0){
      printf("\n correct angel when flatting \n");
  return 0;
  }else {
	printf("\n not in a correct angle \n");	
	stab_roll();
	stab_pitch();
	stab_yaw();
	printf("\n All of the angles are in a right position \n");	
  return 0;	
}







