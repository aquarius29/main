/*****************************************************************************
* Product: 
* Version:  
* Released: April 5 2011
* Updated: April 5 2011
* 
* Copyright (C) 2011 Navid amiriarshad,pooyan mobtahej
*
* providing message handling for stab, filter and Motor Control groups
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

/*****************************************************************************
	Definitions
*****************************************************************************/

unsigned char stab_to_motor_msg;
unsigned char motor_msg;


// read msg from motor inbox
unsigned char read_stab_to_motor(void);// proto API

// pass msg to motor control
void send_stab_to_motor(unsigned char msg);// proto API

// read msg from filter inbox
unsigned char read_motor_msg_(void);// proto API

// pass msg to filter
void send_motor_msg(unsigned char msg);// proto API

/*****************************************************************************
	Implementations
*****************************************************************************/

unsigned char read_stab_to_motor(void){
#ifdef PC
	printf("stab to motor value set to: %c\n", stab_to_motor_msg);
#endif
	return stab_to_motor_msg;
	
}

void send_stab_to_motor(unsigned char msg){
	motor_msg = msg;
#ifdef PC
	printf("stab to motor value set to: %c\n", motor_msg );
#endif
}

unsigned char read_motor_msg_(void){
#ifdef PC
	printf("motor msg value set to: %c\n", motor_msg );
#endif
	return motor_msg;
}

void send_motor_msg(unsigned char msg){
#ifdef PC
	printf("motor msg value set to: %c\n", stab_to_motor_msg );
#endif
	stab_to_motor_msg = msg;
}

