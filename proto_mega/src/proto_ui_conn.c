/*****************************************************************************
* Product: 
* Version: 
* Released: April 20 2011
* Updated:  May 03 2011
*
* Copyright (C) by joshua akhigbemen
*
* Update by Elnaz Shahmehr
*
* <IT University of Goteborg>
*****************************************************************************/
#include <stdio.h>
#include "proto_lib.h"

/*test code for message interpretation. as code is recieved as a binary, it tranforms the message
and decodes it based on the pre-defined inputs expected.*/



//current position
int instruct = -1;

proto_readMsg(int instruction){ 
  if(instruction ==  GO_FORWARD){
	  instruct = 1;
#ifdef PC
storeForTint(READ, UI, UNKNOWN, instruct);
	#ifdef DEBUG
   printf("go forward\n", instruct);
	#endif
#endif
	  return 1;
  }
  else if (instruction == GO_BACKWARD){
       instruct = 0;
#ifdef PC
storeForTint(READ, UI, UNKNOWN, instruct);
	#ifdef DEBUG
   printf("go backward\n", instruct);
	#endif
#endif
	  return 0;
  }
  else if (instruction == GO_RIGHT){
        instruct = 2;
#ifdef PC
storeForTint(READ, UI, UNKNOWN, instruct);
	#ifdef DEBUG
      printf ("go right", instruct);
	#endif
#endif
        return 2;
       }
       else if (instruction == GO_LEFT ){
               instruct = 3;
#ifdef PC
storeForTint(READ, UI, UNKNOWN, instruct);
	#ifdef DEBUG
       printf(" go left",instruct);
	#endif
#endif
               return 3;
            }
            else if (instruction == SET_TO_GPS)
            {
                 instruct = 4;
#ifdef PC
storeForTint(READ, UI, UNKNOWN, instruct);
	#ifdef DEBUG
	printf (" set to gps ",instruct);
	#endif
#endif
                 return 4;
             }
}

proto_sendMsg(){
	char instructions [200];

	if(instruct == 1){
	  //	instructions = "go forward";
	#ifdef PC
storeForTint(WRITE,CONNECTIVITY, UNKNOWN, instruct);
	#ifdef DEBUG   
		printf("go forward\n",instruct);
	 	#endif
#endif
	}
	else if( instruct == 0)
    { 
         // instruction = "go backward ";
   	#ifdef PC
storeForTint(WRITE,CONNECTIVITY, UNKNOWN, instruct);
	#ifdef DEBUG       
         printf("go backward\n",instruct);
         	 	#endif
#endif
         }
         else if ( instruct == 2 )
         {  
              // instruction = " go right ";
               	#ifdef PC
storeForTint(WRITE,CONNECTIVITY, UNKNOWN, instruct);
	#ifdef DEBUG  
              printf ("go right",instruct);
               	 	#endif
#endif         
              }
              else if (instruct == 3)
              { 
                   // instruction = "go left";
                    	#ifdef PC
storeForTint(WRITE,CONNECTIVITY, UNKNOWN, instruct);
	#ifdef DEBUG               
                 printf(" go left",instruct);
                 	 	#endif
#endif               
                 }
                 else if (instruct == 4 )
                 {
                      // instruction = " set to gps ";
                                          	#ifdef PC
storeForTint(WRITE,CONNECTIVITY, UNKNOWN, instruct);
	#ifdef DEBUG 
                      printf (" set to gps ",instruct);
                              	 	#endif
#endif         
                      }
    else
    {
	  //	instructions = "stay on current position";
	  
			printf("stay on current position\n");
			 
	}
}

/*int main(){*/
/*	int protocol = readMsg(0);*/
/*	sendMsg();*/
/*	getchar();*/



