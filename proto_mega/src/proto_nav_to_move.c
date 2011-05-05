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



/*****************************************************************************
	Definitions
*****************************************************************************/

struct navigation {
      
char type_msg;
char order_msg;
int distance_msg;
int yaw_msg;
int height_msg;

        }navigation;
       
struct navigation read();


void write(struct navigation msg);

/*****************************************************************************
	Implementations
*****************************************************************************/
struct navigation read(){
#ifdef PC
    printf("Navigation value set to: %d , %d , %d , %d , %d\n", navigation.type_msg, navigation.order_msg, navigation.distance_msg, navigation.yaw_msg, navigation.height_msg);
#endif
       return navigation;

       }


void write(struct navigation msg){
     
     navigation = msg;
#ifdef PC
    printf("Navigation value set to: %d , %d , %d , %d , %d\n", navigation.type_msg, navigation.order_msg, navigation.distance_msg, navigation.yaw_msg, navigation.height_msg);
#endif
     }



















