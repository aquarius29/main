/*!
 *  @file conn_tcpclient_main.c 
 *
 *  @brief Main function for client socket
 *
 *  @author Michal Musialik
 *  
 *  @date 2011-04-10
 *              2011-05-07 - uppdating  conn_tcpclient_main.c to new standard
 *  @histroy  2011-05-11 - adding signal handler - Ali Issa
*/

#include "conn_tcpclient_main.h"
#include "conn_tcpclient.h"

 
 void init(void){
   socket_create();
  socket_binding();
  socket_connection();
 
 
}
