#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include "sched_types.h"
=======

>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
#define SLEEPT 500*1000


int16_t init2();
int16_t run2();

int16_t init2(){
  printf("initialized module 2...\n");
  return 1;
}

int16_t run2(){
  while(1){
    printf("ready to rumble with module 2...\n");
    usleep(SLEEPT);
  }
  return 1;
}
