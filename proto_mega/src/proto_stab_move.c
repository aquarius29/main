/*****************************************************************************
* Product: 
* Version: 
* Released: April 8 2011
* Updated: May 10 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

 
 #ifdef PC
   #include <stdio.h>
   
   #include <string.h>
#endif
	#include <stdlib.h>
 #include "proto_lib.h"

/***************************************************************************** 
    Definitions 
*****************************************************************************/ 
struct stab_gyroscope * gyroPtr;
struct stab_accelerometer * accPtr;
struct stab_magnetometer * magPtr;
 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 
struct stab_gyroscope * proto_stabReadAttitude(void){ 
/* if the pointer is null*/
/*	then should not attempt to read the values because the code will crash*/
/*	so i should initialize the struct*/
/* else*/
/*	everything is okay, just return the struct*/

  if (gyroPtr == NULL){
	createDefaultstabgyro();
}
	
#ifdef PC
 storeForTint(READ, MOVEMENT, UNKNOWN, gyroPtr->roll);
 storeForTint(READ, MOVEMENT, UNKNOWN, gyroPtr->pitch);
 storeForTint(READ, MOVEMENT, UNKNOWN, gyroPtr->yaw);
	#ifdef DEBUG
	printf("Movement value set to: %d , %d\n", gyroPtr.roll , gyroPtr.pitch,gyroPtr.yaw);
  #endif
#endif
  return (struct stab_gyroscope *) gyroPtr;
}

struct stab_accelerometer * proto_stabReadAcc(void){ 
  if (accPtr == NULL){
	createDefaultstabacc();
}	
#ifdef PC
 storeForTint(READ, MOVEMENT, UNKNOWN, accPtr->acc_x);
 storeForTint(READ, MOVEMENT, UNKNOWN, accPtr->acc_y);
 storeForTint(READ, MOVEMENT, UNKNOWN, accPtr->acc_z);
	#ifdef DEBUG
	printf("Movement value set to: %d , %d\n", accPtr.acc_x , accPtr.acc_y,accPtr.acc_z);
  #endif
#endif
  return (struct stab_accelerometer *) accPtr;
}
 

struct stab_magnetometer * proto_stabReadHeading(void){ 
  if (magPtr == NULL){
	createDefaultstabmag();
}
	
#ifdef PC
 storeForTint(READ, MOVEMENT, UNKNOWN, magPtr->heading);
	#ifdef DEBUG
	printf("Movement value set to: %d , %d\n", magPtr.heading );
  #endif
#endif

  return (struct stab_magnetometer *) magPtr;
}


struct stab_magnetometer * proto_stabReadHeight(void){ 
  if (magPtr == NULL){
	createDefaultstabmag();
}
	
#ifdef PC
 storeForTint(READ, MOVEMENT, UNKNOWN, magPtr->height);
	#ifdef DEBUG
	printf("Movement value set to: %d , %d\n", magPtr.height );
  #endif
#endif

  return (struct stab_magnetometer *) magPtr;

}


struct stab_magnetometer * magnetometerPtr;
void proto_stabWriteHeading(int heading){ 
	
	if (magPtr == NULL)
		magPtr = (struct stab_magnetometer *) malloc(sizeof(struct stab_magnetometer));
	magPtr->heading = heading;
   
#ifdef PC
 storeForTint(WRITE, STAB, UNKNOWN, magPtr->heading);

	#ifdef DEBUG
	printf("Stab value set to: %d , %d\n", magPtr.heading);
  #endif
#endif
} 

void proto_stabWriteAcc(float acc_x,float acc_y,float acc_z){ 
	if (accPtr == NULL)
	accPtr = (struct stab_accelerometer *) malloc(sizeof(struct stab_accelerometer));
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

void proto_stabWriteAttitude(float roll,float pitch,float yaw){ 
       if (gyroPtr == NULL)
	gyroPtr = (struct stab_gyroscope *) malloc(sizeof(struct stab_gyroscope));
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



void proto_stabWriteHeight(float height){
	if (magPtr == NULL)
		magPtr = (struct stab_magnetometer *) malloc(sizeof(struct stab_magnetometer));
	magPtr->height = height;
#ifdef PC
 storeForTint(WRITE, STAB, UNKNOWN, magPtr->height);
	#ifdef DEBUG
	printf("Stab value set to: %d , %d\n",magPtr.height);
  #endif
#endif
} 


void createDefaultstabacc(){
accPtr = (struct stab_accelerometer *) malloc(sizeof(struct stab_accelerometer));

	 accPtr->acc_x = 3;
        accPtr->acc_y = 4;
        accPtr->acc_z = 5;
}

void createDefaultstabmag(){
magPtr = (struct stab_magnetometer *) malloc(sizeof(struct stab_magnetometer));
      
      magPtr->heading = 0;
	magPtr->height = 0;
}

void createDefaultstabgyro(){
	gyroPtr = (struct stab_gyroscope *)malloc(sizeof(struct stab_gyroscope));
       gyroPtr->roll = 0; 
 	gyroPtr->pitch = 0; 
 	gyroPtr->yaw = 0; 
}
