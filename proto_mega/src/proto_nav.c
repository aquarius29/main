/*****************************************************************************
* Product: 
* Version:  
* Released: April 5 2011
* Updated: April 5 2011
* 
* Copyright (C) 2011 Navid amiriarshad,Pooyan Mobtahej
*
* Providing message handling Between Navigation and Connectivity
*
* <IT University of Goteborg>
*****************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"proto_nav.h"
#ifdef PC
#endif


/*****************************************************************************
	Definitions
*****************************************************************************/

unsigned char nav_to_mov_ca_msg;
unsigned char mov_ca_msg;
unsigned char connect_msg;
unsigned char connect_to_nav_msg;
unsigned char current_loc;
unsigned char destination_msg;


// Read msg from navigation to Movement and C/A

unsigned char read_nav_to_mov_ca(void);// proto API

// send msg between navigation and Movement and C/A

void proto_send_nav_to_mov_ca(unsigned char msg);// proto API

// Read msg between connectivity and Navigation

unsigned char proto_read_connect_to_nav(void);// proto API

// Send msg between connectivity and Navigation

void proto_send_connect_to_nav(unsigned char msg); //proto API

// read current location from 

unsigned char proto_get_current_location(void);// proto API

//send current location via connecivity

void proto_send_current_location(unsigned char msg);// proto API

//read destination from navigation via connectivity

unsigned char proto_read_destination_msg_(void);// proto API


// pass msg of destination to navigation

void proto_send_destination_msg(unsigned char msg);


/*****************************************************************************
	Implementations
*****************************************************************************/

unsigned char proto_read_nav_to_mov_ca(void){
#ifdef PC
	printf("navigation to movement msg value set to: %c\n", mov_ca_msg);
#endif
	return mov_ca_msg;
}

void proto_send_nav_to_mov_ca(unsigned char msg){
	mov_ca_msg = msg;
#ifdef PC
	printf("navigation to movement msg value set to: %c\n", mov_ca_msg);
#endif
	
}

unsigned char proto_read_connect_to_nav(void){
#ifdef PC
	printf("Connection to Navigation msg value set to: %c\n", connect_msg);
#endif
         
	return connect_msg;
}

void proto_send_connect_to_nav(unsigned char msg){
	connect_msg = msg;
#ifdef PC
	printf("Connection to Navigation msg value set to: %c\n", connect_msg);
#endif
}

unsigned char proto_get_current_location(void){
#ifdef PC
	printf("Current location msg value set to: %c\n", current_loc);
#endif

	return current_loc;

}

void proto_send_current_location(unsigned char msg){

	current_loc = msg;
#ifdef PC
	printf("Current location msg value set to: %c\n", current_loc);
#endif
}

unsigned char proto_read_destination_msg_(void){
#ifdef PC
	printf("Destination msg value set to: %c\n", destination_msg);
#endif
	return destination_msg;
}

void proto_send_destination_msg(unsigned char msg){

	destination_msg = msg;
#ifdef PC
	printf("Destination msg value set to: %c\n", destination_msg);
#endif

}


