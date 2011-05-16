#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
<<<<<<< HEAD
#include "sched_types.h"
=======

>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
#define SLEEPT 500*1000


int16_t init1();
int16_t run1();

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
