#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include "conn_tcpserver.c"
#include "conn_tcpserver.h"
/*! 
    @file tcpclient.c
    @author Michal Musialik 
*/
int main(void){

  conn_host_setup();
  conn_socket_create();
  conn_socket_reusing();
  conn_socket_bind();
  conn_socket_listening();
  conn_new_socket_creation();
  conn_data_passing();
  

}
