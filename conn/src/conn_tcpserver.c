/*!
 *  @file conn_tcpserver.c
 *
 *  @brief Header file for tcpserver
 *
 *  @author Michal Musialik,Ali Issa
 *  @date 2011-03-20
 *  @history    2011-03-23 - first outcast of conn_tcpserver.c - Michal,Ali\n
 *              2011-04-04 - adding data transfer functions - Michal,Ali\n
 *              2011-04-06 - restructuring conn_tcpserver.c - Michal\n
 *              2011-04-13 - midyfing data transfering - Michal,Ali\n
 *              2011-04-21 - implying data handling function - Michal\n
 *              2011-04-25 - Adding fork for reconnection - Michal,Ali\n
 *              2011-04-28 - adding socket options - Michal\n
 *              2011-05-02 - adding keepalive option - Ali\n
 *  
 *  @details The drone server with receiving command from the user.\n
 *  Forking is used so that socket_tcp so that the master socket is\n 
 *  allways running so that the user can reconnect.\n
 */


#include "conn_ui_mask.h"
#include "conn_tcpserver.h"
#include "conn_tcpserver_main.h"
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



int socket_tcp; 
int new_socket;
int receive; 
int sending; 
int address_length; 
int reusing_value = 1;
char ip_buffer[IP_BUFFER_LENGTH];
char receive_data[BUFFER_SIZE]; 
int pid;
int parrent_pid;

int keepalive_value;
socklen_t keepalive_length = sizeof(keepalive_value);
int atio_temp;/*variable for parsing from string to int*/ 

struct sockaddr_in server;
struct sockaddr_in client;
struct hostent * host ;

/*!
    @brief Function to get hosts IP information
*/
void host_setup(void){
    gethostname(ip_buffer , IP_BUFFER_LENGTH);
    printf("%s\n", ip_buffer);
    host = ( struct hostent * )gethostbyname(ip_buffer);
#ifdef DEBUG_NR2
    printf("Host name : %s\n", host->h_name) ;
    printf("Host IP Address : %s\n", inet_ntoa(*((struct in_addr *)host->h_addr))); 
#endif
}

/*! 
    @brief Function for socket creation
*/
int socket_create(void){
     if(( socket_tcp = socket(AF_INET,SOCK_STREAM,0))==-1){
     DEBUG("create()")
     return 1;   
}
     else{
     DEBUG("Created tcp socket\n")
     return 0;
     }
 }

/*!
   @brief Function for socket reusage
*/
int socket_reusing(void){
     if (setsockopt(socket_tcp, SOL_SOCKET, SO_REUSEADDR, &reusing_value,
         sizeof(reusing_value)) < 0){
     DEBUG("setsockopt()")
     return 1;          
}
     else{
     DEBUG("Reusing socket\n")
     return 0;
     }
}

/*!
   @brief Function for keeping socket alive
*/
int socket_keep_alive(void){
    if(getsockopt(socket_tcp, SOL_SOCKET, SO_KEEPALIVE, &keepalive_value,
    &keepalive_length) < 0) {
    DEBUG("getsockopt()")
    return 1;      
}
   else{
   #ifdef DEBUG_NR2
   printf("Socket is keept %s\n", (keepalive_value ? "alive." : "dead."));
   #endif
   return 0;
   }
}

/*!
   @brief Function for binding socket
*/
int socket_binding(void){
    server.sin_family = AF_INET; 
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    if((bind(socket_tcp, (struct sockaddr *)&server, sizeof(struct sockaddr)))==-1){  
    DEBUG("bind()")
    return 1;
}
    else{
    DEBUG("Binding server socket\n");
    return 0; 
    }
}

/*!
   @brief Function for listening
*/
int socket_listening(void){
    if((listen(socket_tcp, MAX_NR_OF_CONNECTIONS))<0){
    DEBUG("listen()")
    return 1;
}
   else{
   DEBUG("Listening for connections\n")
   return 0; 
   }
}

/*!
   @brief Function for accepting incomming sockets
*/
int socket_accept(void){
    if(( new_socket = accept(socket_tcp, (struct sockaddr *)&client,
    &address_length))<0){
    DEBUG("accept()")
    return 1;
}
    else{ 
    #ifdef DEBUG_NR2
    printf("Client IP is %s and port is : %d \n", inet_ntoa(client.sin_addr),
    ntohs(client.sin_port));
    #endif
    return 0;  
    } 
}


/*!
   @brief Function that handles data passing. 
   @details In here we fork the process for different purosses, one of the\n
   fork is to keep drone socket running when the client is dissconnected\n
   so that reconnection can be established.
 */
int data_passing(void){
 /*
   @brief Main while loop 
 */  
    while(1){
    socket_accept();
    pid = fork();
        if (pid < 0){      
        DEBUG("pid()")
        exit(1);
        }
    if(pid==0){
#ifdef DEBUG_NR2
    printf("child---------%d\n",getpid());
#endif
    CLOSE_SOCKET_TCP;
    message_handling(new_socket,parrent_pid);
    CLOSE_NEW_SOCKET;
    exit(0);   
    }
    else{
        CLOSE_NEW_SOCKET;
    }
#ifdef DEBUG_NR2
    printf("Parent ..... %d\n",getpid());
#endif
    }
    CLOSE_SOCKET_TCP;
    return 0;
}


/*!
   @brief Function for handling all data trafic
*/
void message_handling(int new_socket,int parrent_pid){
    while(1){
    receive = recv(new_socket,receive_data,BUFFER_SIZE,0);
    receive_data[receive]= '\0';
/*!
   @brief Closing client socket
*/
    if (strcmp(receive_data,"quit")==0){
    CLOSE_NEW_SOCKET;
    DEBUG("Closing client\n")
    break;	   
}
/*!
   @brief Closing server socket
*/
    else if (strcmp(receive_data,"shut_server")==0){
    DEBUG("Shutting server\n")
    kill(parrent_pid,SIGTERM);
}   
   else{
/*!
  @brief Reading incomming data and sending to controll_movement
*/
#ifdef DEBUG_NR2
     printf("%s\n", receive_data); 
#endif
     atio_temp = atoi(receive_data);
     controll_movement(atio_temp);
   }
}
}
