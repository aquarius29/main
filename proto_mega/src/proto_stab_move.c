/*!
* @file proto_stab_move.c
* @brief Movement messages
* @author Elnaz Shahmehr
* @history 
*           - 2011-04-08
* 			- 2011-05-10 updated by Elnaz
* 			- 2011-05-12 updated by Mihail
*			- 2011-05-13 updated by Elnaz
*/
 
#ifdef PC
   #include <stdio.h>
   #include <string.h>
#endif

#include <stdlib.h>
#include "proto_lib.h"

/**************************************************************************** 
    Definitions 
****************************************************************************/ 
int heading;
float height;

struct stab_attitude * attPtr;
struct stab_gyroscope * gyroPtr;

 
/**************************************************************************** 
    Implementations 
****************************************************************************/ 
struct stab_attitude * proto_stabReadAttitude(void){ 
#ifdef PC
    storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, attPtr->roll);
    storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, attPtr->pitch);
    storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, attPtr->yaw);
	#ifdef DEBUG
	printf("Movement value set to: %f , %f, %f\n", attPtr->roll, attPtr->pitch,
	    attPtr->yaw);
    #endif
#endif
    return (struct stab_attitude *) attPtr;
}

struct stab_gyroscope * proto_stabReadGyro(void){ 
#ifdef PC
    storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, gyroPtr->gyro_x);
    storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, gyroPtr->gyro_y);
    storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, gyroPtr->gyro_z);
	#ifdef DEBUG
	printf("Movement value set to: %f , %f, %f\n", gyroPtr->gyro_x, gyroPtr->gyro_y,
	        gyroPtr->gyro_z);
    #endif
#endif
    return (struct stab_gyroscope *) gyroPtr;
}
 

void proto_stabWriteGyro(float gyro_x,float gyro_y,float gyro_z){ 
    gyroPtr->gyro_x = gyro_x;
    gyroPtr->gyro_y = gyro_y;
    gyroPtr->gyro_z = gyro_z;	
#ifdef PC
    storeForTint(PROTO_WRITE, PROTO_STAB, PROTO_UNKNOWN, gyroPtr->gyro_x);
    storeForTint(PROTO_WRITE, PROTO_STAB, PROTO_UNKNOWN, gyroPtr->gyro_y);
    storeForTint(PROTO_WRITE, PROTO_STAB, PROTO_UNKNOWN, gyroPtr->gyro_z);
	#ifdef DEBUG
	printf("Stab value set to: %f, %f, %f\n", gyroPtr->gyro_x,
	    gyroPtr->gyro_y,gyroPtr->gyro_z);
    #endif
#endif
} 

void proto_stabWriteAttitude(float roll,float pitch,float yaw){ 
	attPtr->roll = roll; 
 	attPtr->pitch = pitch; 
 	attPtr->yaw = yaw; 
#ifdef PC
    storeForTint(PROTO_WRITE, PROTO_STAB, PROTO_UNKNOWN, attPtr->roll);
    storeForTint(PROTO_WRITE, PROTO_STAB, PROTO_UNKNOWN, attPtr->pitch);
    storeForTint(PROTO_WRITE, PROTO_STAB, PROTO_UNKNOWN, attPtr->yaw);
	#ifdef DEBUG
	printf("Stab value set to: %f , %f, %f\n", attPtr->roll, attPtr->pitch,
	        attPtr->yaw);
    #endif
#endif
} 

/////////////////////////

void proto_stabWriteHeading(int messageHeading){
	heading=messageHeading;
#ifdef PC
    storeForTint(PROTO_WRITE, PROTO_MOTOR, PROTO_UNKNOWN, heading);
	#ifdef DEBUG
	   printf("Stab value set to: %d\n", heading);
    #endif 
#endif
} 
   
int proto_stabReadHeading(void){
	int tempHeading=heading;
	heading=0;
#ifdef PC
    storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, tempHeading);
	#ifdef DEBUG
	printf("Stab value set to: %d\n", tempHeading);
    #endif
#endif
	return tempHeading;
}

////////////////////////

void proto_stabWriteHeight(float messageHeight){
	height=messageHeight;
#ifdef PC
    storeForTint(PROTO_WRITE, PROTO_MOTOR, PROTO_UNKNOWN, height);
	#ifdef DEBUG
	   printf("Stab value set to: %f\n", height);
    #endif 
#endif
} 
   
float proto_stabReadHeight(void){
	float tempheight=height;
	 height=0;
#ifdef PC
    storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, tempheight);
	#ifdef DEBUG
	printf("Stab value set to: %f\n", tempheight);
    #endif
#endif
	return tempheight;
}

//////////////

void createDefaultstabgyro(){
    if(gyroPtr == NULL){
        gyroPtr = (struct stab_gyroscope *) malloc(sizeof(struct stab_gyroscope));
    }
    gyroPtr->gyro_x = 3;
    gyroPtr->gyro_y = 4;
    gyroPtr->gyro_z = 5;
}

void createDefaultstabatt(){
	if(attPtr == NULL){
	    attPtr = (struct stab_attitude * ) malloc(sizeof(struct stab_attitude));
    }
    attPtr->roll = 0; 
 	attPtr->pitch = 0; 
 	attPtr->yaw = 0; 
}
