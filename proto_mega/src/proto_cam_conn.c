/*
 *  camera_conn_protocol.c
 *  
 *
 *  Created by Nena Stojova on 4/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>


unsigned int camera_message;
unsigned int connect_message;

void proto_write_camera(unsigned int message){
	camera_message=message;
}

unsigned int proto_read_camera(void){
	unsigned int temp=camera_message;
	camera_message=0;
	return temp;
}

void proto_write_connect(unsigned int message){
	connect_message=message;
}

unsigned int proto_read_connect(void){
	unsigned int temp=connect_message;
	connect_message=0;
	return temp;
}
