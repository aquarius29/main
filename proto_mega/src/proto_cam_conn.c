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
