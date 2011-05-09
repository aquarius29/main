/*!
 *  @file conn_tcpclient_main.c 
 *
 *  @brief Main function for client socket
 *
 *  @author Michal Musialik
 *  
 *  @date 2011-04-10
 *              2011-05-07 - uppdating  conn_tcpclient_main.c to new standard
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "conn_tcpclient.h"
#include "conn_tcpclient.c"


  void init(void){

  socket_create();
  socket_binding();
  socket_connection();
 
 
}
