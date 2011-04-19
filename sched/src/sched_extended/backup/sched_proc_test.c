#include <stdio.h>
#include <stdlib.h>
#include "sched_types.h"
#define SLEEPT 500*1000


int init();
int run();

//int main(void){
//  init();
//  run();
//}

int init(){
  printf("initialized...\n");
  return SUCCESS;
}

int run(){
  while(1){
    printf("ready to rumble...\n");
    usleep(SLEEPT);
  }
  return SUCCESS;
}
