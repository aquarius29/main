/*!
* @file proto_read.c
* @brief Transfer data between Arduino and Panda
* @author Navid amiriarshad,Pooyan Mobtahej
* @history 
* 			- 2011-04-26 first release
*			
* 			
*/

/*****************************************************************************
    Definitions
*****************************************************************************/
#include "proto_lib_panda.h"

typedef struct{
  unsigned char data [255];
  
  unsigned char type;

  } MSGpack;


# define     MOTOR_MSG_TYPE 1 
# define     CONNECTIVITY_MSG_TYPE 2 
# define     SCADULER_MSG_TYPE 3  
# define     UI_MSG_TYPE 4

# define     MOTOR_MSG_SIZE 1
# define     CONNECTIVITY_MSG_SIZE 1
# define     SCADULER_MSG_SIZE 1
# define     UI_MSG_SIZE 1 





/*****************************************************************************
    Implement
*****************************************************************************/
void sendto_MOTOR(unsigned char data){
}

void sendto_UI(unsigned char data){
}

void sendto_CONNECTIVITY(unsigned char data){
}

#ifdef  PC

 void rec ( MSGpack  m  ){
  // Switch cases for each modules which have interact with the Boards 
  switch(m.type) {
   case  MOTOR_MSG_TYPE:
  
   sendto_MOTOR(*((unsigned char*)m.data));
    break;


   case  CONNECTIVITY_MSG_TYPE:
  
   sendto_CONNECTIVITY(*((unsigned char*)m.data));
   
    break;
     
  
   case  SCADULER_MSG_TYPE:
  
   sendto_SCADULER(*((unsigned char*)m.data));
    break;

   
   case  UI_MSG_TYPE:
  
   sendto_UI(*((unsigned char*)m.data));
    break;

    }
}

#else

void rec(){
 	 #ifdef PC
         storeForTint(READ, MOTOR, UNKNOWN, data);
	#ifdef DEBUG
	printf("motor msg value set to: %c\n", data );
     #endif
#endif
 //read from serial  m      
}

#endif


