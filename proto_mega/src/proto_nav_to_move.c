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
      
char type;
char order;
int distance;
int yaw;
int height;

        }navigation;
       
struct navigation read();


void write(struct navigation msg);

/*****************************************************************************
	Implementations
*****************************************************************************/
struct navigation read(){
#ifdef PC
    printf("Navigation value set to: %d , %d , %d , %d , %d\n", navigation.type, navigation.order, navigation.distance, navigation.yaw, navigation.height);
#endif
       return navigation;

       }


void write(struct navigation msg){
     
     navigation = msg;
#ifdef PC
    printf("Navigation value set to: %d , %d , %d , %d , %d\n", navigation.type, navigation.order, navigation.distance, navigation.yaw, navigation.height);
#endif
     }



















