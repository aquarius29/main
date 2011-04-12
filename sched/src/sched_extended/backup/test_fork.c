#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define N 600 * 1000

void do1(){
  while (1){
  printf("do1\n");
  usleep(N);
  }
}

void do2(){
  while (1) {
    printf("do2\n");
    usleep(N);
  }
}

void do_stuff(){
  int n = 5;
  pid_t pid;

  while ( n>0 ){
    pid = fork();
    if (pid == 0) do1();
    else do2();

    printf("n is %d\n", n);
    n--;
  }
}

int main(void){
  do_stuff();
}
