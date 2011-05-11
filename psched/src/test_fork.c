#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define N 600 * 1000

void do1(){
  while (1){
    printf("do1 - pid: %d\n", getpid());
  usleep(N);
  }
}

void do2(){
  while (1) {
    printf("do2 - pid: %d\n", getpid());
    usleep(N);
  }
}

void do3(){
  while (1) {
    printf("do3 - pid: %d\n", getpid());
    usleep(N);
  }
}

void do_stuff(void(*func)()){
  pid_t pid = fork();
  if (pid == 0) (*func)();
}

int main(void){
  do_stuff(&do1);
  do_stuff(&do2);
  do_stuff(&do3);
}
