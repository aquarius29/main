<<<<<<< HEAD
/*!
* @file proto_conn.c
* @brief Connectivity messages
* @author Navid Amiriarshad, Pooyan Mobtahej
* @history 
*			- 2011-05-09 updated by Elnaz
* 			- 2011-05-12 updated by Mihail
*/

#ifdef PC
	#include<stdio.h> 
#endif

#include <stdlib.h>
#include"proto_lib.h"
/**************************************************************************** 
    Definitions 
****************************************************************************/ 
 
uint8_t proto_navi_to_connectivity_msg; 
 
uint8_t proto_read_navi_to_connectivity(void); 
 
void proto_send_navi_to_connectivity(uint8_t  msg); 
 
/**************************************************************************** 
    Implementations 
****************************************************************************/ 
 
uint8_t  proto_read_navi_to_connectivity(void){ 
#ifdef PC
	storeForTint(PROTO_READ, PROTO_CONNECTIVITY, PROTO_UNKNOWN, proto_navi_to_connectivity_msg);
	#ifdef DEBUG
		printf("navigation msg value set to: %c\n", proto_navi_to_connectivity_msg );
	#endif
#endif
    return proto_navi_to_connectivity_msg; 
    
} 
 
void proto_send_navi_to_connectivity(uint8_t  msg){ 
    proto_navi_to_connectivity_msg = msg; 
#ifdef PC
	storeForTint(PROTO_WRITE, PROTO_NAV, PROTO_UNKNOWN, proto_navi_to_connectivity_msg);
	#ifdef DEBUG
		printf("navigation msg value set to: %c\n", proto_navi_to_connectivity_msg );
	#endif
#endif
} 
=======
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
>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
