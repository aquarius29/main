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
