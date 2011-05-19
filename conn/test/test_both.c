#include <stdlib.h>

int main(void) {
  int pid = fork();
  if (pid == 0) {
    system("./clienttest.a");
  }
  else {
    system("./servertest.a");
    sleep(3);
  }
  //sleep(1);
  //system("./clienttest.a");
}
