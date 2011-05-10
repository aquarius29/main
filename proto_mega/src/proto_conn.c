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

#ifdef PC
	#include<stdio.h> 
	#include<stdlib.h>  
#endif
 
 	#include"proto_lib.h"
/***************************************************************************** 
    Definitions 
*****************************************************************************/ 
 
unsigned char proto_navi_to_connectivity_msg; 
//unsigned char nav_msg; 
 
unsigned char proto_read_navi_to_connectivity(void); 
 
void proto_send_navi_to_connectivity(unsigned char msg); 
 
/***************************************************************************** 
    Implementations 
*****************************************************************************/ 
 
 
unsigned char proto_read_navi_to_connectivity(void){ 
#ifdef PC
	storeForTint(READ, CONNECTIVITY, UNKNOWN, proto_navi_to_connectivity_msg);
	#ifdef DEBUG
		printf("navigation msg value set to: %c\n", proto_navi_to_connectivity_msg );
	#endif
#endif
    return proto_navi_to_connectivity_msg; 
    
} 
 
void proto_send_navi_to_connectivity(unsigned char msg){ 
    proto_navi_to_connectivity_msg = msg; 
#ifdef PC
	storeForTint(WRITE, NAV, UNKNOWN, proto_navi_to_connectivity_msg);
	#ifdef DEBUG
		printf("navigation msg value set to: %c\n", proto_navi_to_connectivity_msg );
	#endif
#endif
} 
