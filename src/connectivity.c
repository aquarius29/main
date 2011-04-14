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
#include"connectivity.h" 
 
 
/***************************************************************************** 
    Definitions 
*****************************************************************************/ 
 
unsigned char navi_to_connectivity_msg; 
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
