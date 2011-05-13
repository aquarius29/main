#include <stdio.h>
#include <stdlib.h>
#include "sched_types.h"
#define SLEEPT 500*1000


int16_t init2();
int16_t run2();

//int main(void){
//  init();
//  run();
//}

int16_t init2(){
  printf("initialized module 2...\n");
  return SUCCESS;
}

int16_t run2(){
  while(1){
    printf("ready to rumble with module 2...\n");
    usleep(SLEEPT);
  }
  return SUCCESS;
}
