#include <stdio.h>
#include <unistd.h>
#include "mq.h"

#define KEY 123

int main(void){
  int id= mq_init(KEY);
  size_t len;
  char msg[MSGSIZE];
  if ((len=mq_recv(id, 1, msg)) < 0){
    perror("msgsnd");
    _exit(1);
  }

  printf("message received (%ld bytes): %s\n", len, msg);
}
