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
//#include "navigation.h" 
#ifdef PC
#endif
 
/***************************************************************************** 
    Definitions 
*****************************************************************************/ 
 
unsigned char navi_to_connectivity_msg = 0x12; 
//unsigned char nav_msg; 
 
 
unsigned char read_navi_to_connectivity(void); 
 
void send_navi_to_connectivity(unsigned char msg); 
 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 
 
 
unsigned char read_navi_to_connectivity(void){ 
#ifdef PC
	printf("navigation msg value set to: %c\n", navi_to_connectivity_msg );
#endif
    return navi_to_connectivity_msg; 
    
} 
 
void send_navi_to_connectivity(unsigned char msg){ 
    navi_to_connectivity_msg = msg; 
#ifdef PC
	printf("navigation msg value set to: %c\n", navi_to_connectivity_msg );
#endif
} 
