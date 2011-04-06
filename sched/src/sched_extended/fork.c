#include <stdio.h>
#include <unistd.h>

int main(void){
  int cid ;
  char a[0];

  printf("Pid : %d, parentid: %d\n", getpid(), getppid());
  
  //cid= fork();
  
  printf("Pid : %d, parentid: %d - cid: %d\n", getpid(), getppid(), cid);
  execv("ls", a);
}
