/*****************************************************************************
* Product: 
* Version: 
* Released: April 1 2011
* Updated: April 1 2011
*
* Copyright (C) 2011 Peter Mihail Anton 
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <libarduino.h>
#include "protolib.h"

#define ledPin 13
#define ON 1
#define OFF 0

int motor(void){
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, ON);
	_delay_ms(300);
	digitalWrite(ledPin, OFF);
	_delay_ms((long)read_motor_ctrl() * 100);
	return 1;
}

