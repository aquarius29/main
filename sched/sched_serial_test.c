/*The purpose of this is to test the message handler(sched_serial.c) and is not meant to be compiled as part of the program to be used on the Mega*/




#include <stdio.h>
#include "sched_serial.h"



main(){
  char msg[32];
  int inChar;

  printf("Enter a message to pass:");
  gets(&msg);

  if(msg[0] != NULL){
    int i = 0;
    while(msg[i] != '\0'){  //Write to sched_serial
      put_char(rxtx, msg[i]);
      i++;
    }
    while ((inChar = getc(rxtx)) != EOF)       /* Reads first */
      { putchar(inChar); } 

  }
  
  return 0;


}
