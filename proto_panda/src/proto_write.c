/*!
* @file proto_write.c
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

#define      MOTOR_MSG_SIZE 1
#define      CONNECTIVITY_MSG_SIZE 1
#define      SCADULER_MSG_SIZE 1
#define      UI_MSG_SIZE 1







/*****************************************************************************
    Implement
*****************************************************************************/
void send(void * m,int size,int type){

   MSGpack   msg;
  
  // mem copy (msg.data, m, size);
   
   msg.type = type;
  
#ifdef PC
      
       rec( msg );
#else 

   //serial out m

  #endif

}     
 














