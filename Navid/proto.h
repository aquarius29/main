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


// read msg from motor inbox
unsigned char read_stab_to_motor(void);// proto API

// pass msg to motor control
void send_stab_to_motor(unsigned char msg);// proto API

// read msg from filter inbox
unsigned char read_motor_msg_(void);// proto API

// pass msg to filter
void send_motor_msg(unsigned char msg);// proto API
