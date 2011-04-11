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
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <libarduino.h>
#include "protolib.h"

#define ledPin 13
#define ON 1
#define OFF 0

int main (void){
/*	sei(); */
	pinMode(ledPin, OUTPUT);
	char a = 1;
	while(1){
		write_motor_ctrl(a);
		a = a + 51;
		digitalWrite(ledPin, ON);
		_delay_ms(200);
		digitalWrite(ledPin, OFF);
		_delay_ms((long)read_motor_ctrl() * 50);
	}
	return 1;
}
