#include <stdio.h>
#include <stdlib.h>
#define SLEEPT 500*1000

int init1();
int run1();

int init1(){
  printf("initialized...\n");
  return 1;
}

int run1(){
  int i = 4;
  char buff[SHM_PROC_SIZE];
  size_t recvlen = 0;
  int res;

  while(1){
    printf("module 1: running...\n");
    usleep(SLEEPT*5);
    //recvlen = proc_recv(1, buff);
    
    res= proc_read_state(PROC_UI, buff);

    if (res == 1){
      printf(" * State for UI says: %s\n", buff);
    }


    res= proc_read_state(PROC_NAV, buff);

    if (res == 1){
      printf(" * State for NAV says: %s\n", buff);
    }


    
    i--;
  }
  return 1;
}
