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
//#include<errno.h>
//#include<sys/types.h>
//#include<unistd.h>
//#include <avr/io.h>
//#include <util/delay.h>
//#include <avr/interrupt.h>
//#include <libarduino.h>
#include "protolib.h"
#include "navigation.h"


/*****************************************************************************
	Definitions
*****************************************************************************/

struct navigation {
      
unsigned char nav_to_mov_ca_msg;
unsigned char mov_ca_msg;
unsigned char connect_msg;
unsigned char connect_to_nav_msg;
unsigned char current_loc;
unsigned char destination_msg;
       
       }navigation;
       
struct navigation read();


void write(struct navigation msg);

/*****************************************************************************
	Implementations
*****************************************************************************/

struct navigation  read(){
#ifdef PC
    printf("Navigation value set to: %d , %d , %d\n", msg.destination_msg, msg.current_loc, msg.connect_to_nav_msg, msg.connect_msg, msg.mov_ca_msg, msg.nav_to_mov_ca_msg  );
#endif
       return navigation;

       }


void write(struct navigation msg){
     
     navigation = msg;
#ifdef PC
    printf("Navigation value set to: %d , %d , %d\n", msg.destination_msg, msg.current_loc, msg.connect_to_nav_msg, msg.connect_msg, msg.mov_ca_msg, msg.nav_to_mov_ca_msg  );
#endif
     }



















