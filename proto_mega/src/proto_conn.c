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
