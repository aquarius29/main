/*!
 *  @file conn_tcpserver_main.c 
 *
 *  @brief Main function for drone socket
 *
 *  @author Michal Musialik,Ali Issa
 *  
 *  @date 2011-04-10
 *  @history    2011-04-15 - structuring file layout Michal, Ali
 *              2011-04-20 - adding host_setup() function - Michal
 *              2011-05-07 - uppdating  conn_tcpserver_main.c - Ali
 *              2011-05-11 - updating for keepalive - Ali
 *
 */



#include <stdio.h>


#include "conn_tcpserver.h"
#include "conn_tcpserver_main.h"

/*Initiazion function*/
int conn_init(void){
    host_setup();
    socket_create();
    socket_reusing();
    socket_keep_alive();
    socket_binding();
    socket_listening(); 
    return 0;
 }

/*Run function*/
int conn_run(void){
    data_passing();
    return 0;
}

