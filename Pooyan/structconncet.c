/*****************************************************************************
* Product: 
* Version:  
* Released: April 5 2011
* Updated: April 13 2011
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
#include "connectivity.h"
#ifdef PC
#endif


/*****************************************************************************
	Definitions
*****************************************************************************/

struct connectivity {
       unsigned char navi_to_connectivity_msg;
       unsigned char nav_msg;
       
       }connectivity;
       
struct connectivity read();


void write(struct connectivity msg);

/*****************************************************************************
	Implementations
*****************************************************************************/

struct connectivity  read(){
#ifdef PC
    printf("Connectivity value set to: %d , %d , %d\n", msg.navi_to_connectivity_msg , msg.nav_msg);
#endif
       return connectivity;
       }


void write(struct connectivity msg){
     connectivity = msg;
#ifdef PC
    printf("Connectivity value set to: %d , %d , %d\n", msg.navi_to_connectivity_msg , msg.nav_msg);
#endif
     }







