/*!
 *  @file conn_tcpclient_main.c 
 *
 *  @brief Main function for client socket
 *
 *  @author Michal Musialik,Ali Issa
 *  
 *  @date 2011-04-10
 *  @history  2011-05-07 - uppdating conn_tcpclient_main.c - Michal,Ali
*/

#include "conn_tcpclient_main.h"
#include "conn_tcpclient.h"

 
void init(void){
     socket_create();
     socket_binding();
     socket_connection();
}
