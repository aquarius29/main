#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "conn_udpserver.c"

int init(void){

  create_socket();
  socket_address_bind();
  socket_server_cam();
 
  return 0;
}


int main(void){

  init();

}
