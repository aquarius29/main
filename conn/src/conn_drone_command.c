#include <stdio.h>

/*
 * @ author: mgbah iheanacho
 * @ file: drone_command.c
 */

int drone_command(int command){
  if(command == 1){
    printf("starting up drone...\n");
    return 1;
  }else if(command == 2){
    printf("lifting up...\n");
    return 2;
  }else if(command == 0){
    printf("shut down..\n"); 
    return 3;
  }else{
    printf("unknown command..\n");
  }
}
