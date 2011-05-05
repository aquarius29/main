#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include "gui_tcpserver.c"
#include "gui_tcpserver.h"
/*Author Michal Musialik*/


int main(void){

  host_setup();
  socket_create();
  socket_reusing();
  socket_keep_alive();
  socket_binding();
  socket_listening();
  data_passing();
  
  return 0;

}
