<<<<<<< HEAD
/*!
* @file proto_cam_conn.c
* @brief Messages between Camera and Connectivity
* @author Nena
* @history 
*			- 2011-05-10 updated by Elnaz
* 			- 2011-05-12 updated by Mihail
*/

#ifdef PC
   #include <stdio.h>
#endif

#include <stdlib.h>
#include "proto_lib.h"

uint16_t  camera_message;
uint16_t  connect_message;

void proto_write_camera(uint16_t  message){
	camera_message=message;
#ifdef PC
	storeForTint(PROTO_WRITE, PROTO_CAMERA, PROTO_UNKNOWN, camera_message);
	#ifdef DEBUG
        printf("camera_message: %c\n", camera_message);
	#endif
#endif
}

uint16_t  proto_read_camera(void){
	uint16_t  temp=camera_message;
	camera_message=0;
#ifdef PC
	storeForTint(PROTO_READ, PROTO_CAMERA, PROTO_UNKNOWN, camera_message);
	#ifdef DEBUG
		printf("camera_message: %c\n", camera_message);
	#endif
#endif
	return temp;
}

void proto_write_connect(uint16_t  message){
	connect_message=message;
#ifdef PC
	storeForTint(PROTO_WRITE, PROTO_CONNECTIVITY, PROTO_UNKNOWN, connect_message);
	#ifdef DEBUG
		printf("connect_message: %c\n", connect_message);
	#endif
#endif
}

uint16_t  proto_read_connect(void){
	uint16_t  temp=connect_message;
	connect_message=0;
#ifdef PC
	storeForTint(PROTO_READ, PROTO_CONNECTIVITY, PROTO_UNKNOWN, connect_message);
	#ifdef DEBUG
		printf("connect_message: %c\n", connect_message);
	#endif
#endif
	return temp;
}
=======
/*****************************************************************************
* Product: 
* Version: 
* Released: April 20 2011
* Updated: 
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

#ifdef PC
   #include <stdio.h>
#endif

   #include "proto_lib.h"
unsigned int camera_message;
unsigned int connect_message;

void proto_write_camera(unsigned int message){
	camera_message=message;
#ifdef PC
	storeForTint(WRITE, CAMERA, UNKNOWN, camera_message);
	#ifdef DEBUG
	printf("camera_message: %c\n", camera_message);
	#endif
#endif
}

unsigned int proto_read_camera(void){
	unsigned int temp=camera_message;
	camera_message=0;
#ifdef PC
	storeForTint(READ, CAMERA, UNKNOWN, camera_message);
	#ifdef DEBUG
	printf("camera_message: %c\n", camera_message);
	#endif
#endif
	return temp;
}

void proto_write_connect(unsigned int message){
	connect_message=message;
#ifdef PC
	storeForTint(WRITE, CONNECTIVITY, UNKNOWN, connect_message);
	#ifdef DEBUG
	printf("connect_message: %c\n", connect_message);
	#endif
#endif
}

unsigned int proto_read_connect(void){
	unsigned int temp=connect_message;
	connect_message=0;
#ifdef PC
	storeForTint(READ, CONNECTIVITY, UNKNOWN, connect_message);
	#ifdef DEBUG
	printf("connect_message: %c\n", connect_message);
	#endif
#endif
	return temp;
}
>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
