#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sched_types.h"
#define SLEEPT 500*1000


int16_t init1();
int16_t run1();

//int main(void){
//  init();
//  run();
//}

int16_t init1(void){
  printf("initialized...\n");
  return 1;
}

int16_t run1(void){
  int i = 4;
  while(i > 0){
    printf("ready to rumble...\n");
    usleep(SLEEPT);
    i--;
  }
  return 1;
}
