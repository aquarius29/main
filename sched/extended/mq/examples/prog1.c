#include <stdio.h>
#include <unistd.h>
#include "mq.h"

#define KEY 123

int main(void){
  int id= mq_init(KEY);
  size_t len;
  if ((len=mq_send(id, 1, "dude1")) < 0){
    perror("msgsnd");
    _exit(1);
  }
}
