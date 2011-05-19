/*
Author Michal Musialik
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "conn_udpclient.c"

int init(void){

  socket_host();
  socket_create();
  socket_address_bind();
  socket_server_check();
  return 0;
}

int main(void){

  init();

}
