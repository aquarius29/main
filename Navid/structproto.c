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
#ifdef PC
#endif

/*****************************************************************************
	Definitions
*****************************************************************************/

struct proto {
       
unsigned char stab_to_motor_msg;
unsigned char motor_msg;
       
       }proto;
       
struct proto read();


void write(struct proto msg);

/*****************************************************************************
	Implementations
*****************************************************************************/

struct proto  read(){
#ifdef PC
    printf("proto value set to: %d , %d , %d\n", msg.stab_to_motor_msg , msg.motor_msg);
#endif
       return proto;
       }


void write(struct proto msg){
     proto = msg;
#ifdef PC
    printf("proto value set to: %d , %d , %d\n", msg.stab_to_motor_msg , msg.motor_msg);
#endif
     }
