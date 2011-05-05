
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



// Read msg from navigation to Movement and C/A

unsigned char read_nav_to_mov_ca(void);// proto API

// send msg between navigation and Movement and C/A

void send_nav_to_mov_ca(unsigned char msg);// proto API

// Read msg between connectivity and Navigation

unsigned char read_connect_to_nav(void);// proto API

// Send msg between connectivity and Navigation

void send_connect_to_nav(unsigned char msg); //proto API

// read current location from 

unsigned char get_current_location(void);// proto API

//send current location via connecivity

void send_current_location(unsigned char msg);// proto API

//read destination from navigation via connectivity

unsigned char read_destination_msg_(void);// proto API


// pass msg of destination to navigation

void send_destination_msg(unsigned char msg);



