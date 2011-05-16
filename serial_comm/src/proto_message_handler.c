
/*
 *  initial code for the linked list handler of raw data and processing messages from the
 *  USART port
 *
 *
 *  author: Justin
 */

#include "WProgram.h"

struct node{
  int head;
  char data[40];
  int tail;
}

  struct list{
    struct node n1;
    int head;
    int tail;
  }

    uint8_t push(struct node n1){
      
