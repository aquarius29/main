/*****************************************************************************
* Product: 
* Version: 
* Released: April 8 2011
* Updated: May 3 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

 
 #ifdef PC
   #include <stdio.h>
   #include <stdlib.h>
   #include "proto_lib.h"
   #include <stdio.h>
   #include <string.h>
#endif

 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 

void proto_stabWriteAttitude(float roll,float pitch,float yaw){ 
       if (gyroPtr == NULL)
	gyroPtr = malloc(sizeof(struct stab_gyroscope));
 	gyroPtr->roll = roll; 
 	gyroPtr->pitch = pitch; 
 	gyroPtr->yaw = yaw; 
       
	

#ifdef PC
 storeForTint(WRITE, STAB, UNKNOWN, gyroPtr->roll);
 storeForTint(WRITE, STAB, UNKNOWN, gyroPtr->pitch);
 storeForTint(WRITE, STAB, UNKNOWN, gyroPtr->yaw);
	#ifdef DEBUG
	printf("Stab value set to: %d , %d\n", gyroPtr.roll , gyroPtr.pitch,gyroPtr.yaw);
  #endif
#endif
} 
 
 
void proto_stabWriteAcc(float acc_x,float acc_y,float acc_z){ 
	if (accPtr == NULL)
	accPtr = malloc(sizeof(struct stab_accelerometer));
        accPtr->acc_x = acc_x;
        accPtr->acc_y = acc_y;
        accPtr->acc_z = acc_z;
       
	
#ifdef PC
 storeForTint(WRITE, STAB, UNKNOWN, accPtr->acc_x);
 storeForTint(WRITE, STAB, UNKNOWN, accPtr->acc_y);
 storeForTint(WRITE, STAB, UNKNOWN, accPtr->acc_z);
	#ifdef DEBUG
	printf("Stab value set to: %d , %d\n", accPtr.acc_x , accPtr.acc_y,accPtr.acc_z);
  #endif
#endif
} 
struct stab_magnetometer * magnetometerPtr;

void proto_stabWriteHeading(int heading){ 
	
	if (magPtr == NULL)
		magPtr = malloc(sizeof(struct stab_magnetometer));
	magPtr->heading = heading;
   
#ifdef PC
 storeForTint(WRITE, STAB, UNKNOWN, magPtr->heading);

	#ifdef DEBUG
	printf("Stab value set to: %d , %d\n", magPtr.heading);
  #endif
#endif
} 

void proto_stabWriteHeight(float height){
	if (magPtr == NULL)
		magPtr = malloc(sizeof(struct stab_magnetometer));
	magPtr->height = height;
#ifdef PC
 storeForTint(WRITE, STAB, UNKNOWN, magPtr->height);

	#ifdef DEBUG
	printf("Stab value set to: %d , %d\n",magPtr.height);
  #endif
#endif
} 

struct stab_accelerometer * retrieve_acc(void)
{
	return accPtr;
}

struct stab_gyroscope * retrieve_gyro(void)
{
	return gyroPtr;
}

struct stab_magscope * retrieve_mag(void)
{
	return magPtr;
}

