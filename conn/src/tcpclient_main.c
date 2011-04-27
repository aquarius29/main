#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "tcpclient.c"

int main(int argc,char *argv[]){
  
  socket_host(argv);
  socket_create();
  socket_binding();
  socket_connection();
  data_passing();  

  return 0;
}
