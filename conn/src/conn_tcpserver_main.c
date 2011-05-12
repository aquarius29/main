/*!
 *  @file conn_tcpserver_main.c 
 *
 *  @brief Main function for drone socket
 *
 *  @author Michal Musialik
 *  
 *  @date 2011-04-10
 *  @history    2011-04-15 - structuring file layout
 *              2011-04-20 - adding host_setup() function
 *              2011-05-07 - uppdating  conn_tcpserver_main.c to new standard
 *              2011-05-11 - updating for keepalive
 */

#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <stddef.h>
#include <resolv.h>
#include <fcntl.h>

#include "conn_ui_mask.c"
#include "conn_tcpserver.h"
#include "conn_tcpserver.c"
#include "conn_tcpserver_main.h"

/*Initiazion function*/
int16_t init(void){

  host_setup();
  socket_create();
  socket_reusing();
  socket_keep_alive();
  socket_binding();
  socket_listening();
  return 0;

 }

int16_t run(void){

  data_passing();

  return 0;
}

