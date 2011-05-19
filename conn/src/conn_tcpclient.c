/*!
 *  @file conn_tcpclient.c
 *
 *  @brief tcpclient file
 *
 *  @author Michal Musialik
 *  @date 2011-05-07
 *  @history    2011-04-15 - first outcast of conn_tcpclient.c file
 *  @history    2011-04-16 - rebuilding file architecture
 *  @history    2011-04-20 - testing of modules
 *  @history    2011-04-25 - rebuilding file acording to coding standarts
 *  @history    2011-04-28 - integrating GUI functionality
 *  @history    2011-05-02 - restructuring GUI implementation
 *  @history    2011-05-12 - implementation latest message passing
 *  @history    2011-05-13 - adding debug functions  
 *  @histroy    2011-05-16 - adding receive GPS function
 *  
 *  Description:
 *  Client part of the wireless connection that is used to send command 
 *  messages to the drone wirelessly. Command mesags are invoked by GUI
 *  that controll the drone. 
 *
 */
#include <signal.h> 
#include <fcntl.h>
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
/*#include "conn_frame.h"*/

#define SERVER_ADDRESS "129.16.166.190" 

int socket_tcp;
int receive;
char receive_data[10];

struct hostent * host; 
struct sockaddr_in connecting; 

/*Creating client socket*/
int socket_create(void){
    if((socket_tcp = socket(AF_INET, SOCK_STREAM,0)) < 0){
        DEBUG("failed to create a socket\n")
        return -1;
    }
    else {
        DEBUG("socket is succesfully created\n")
        return 0;
    }
}


/*!
    @brief Binding socket function
*/
int socket_binding(void) {
  /*Drone adress need to be hadcodded*/
  host = (struct hostent *)gethostbyname((char *)SERVER_ADDRESS);
  connecting.sin_family = AF_INET;
  connecting.sin_port = htons(PORT);
  connecting.sin_addr= *((struct in_addr *)host->h_addr);
  memset(&(connecting.sin_zero),'\0',8);/*zeroing rest of struct*/
  return 0;
}

/*Connecting function*/
int socket_connection(void) {
    if(connect(socket_tcp,(struct sockaddr *)&connecting,sizeof(struct sockaddr)) < 0) {
        DEBUG("connect()")
	return -1;
    }
    else {
        DEBUG("Client is connected\n")
        return 0; 
    }
}


/*Function for sending data over to the server*/
void send_forward (void){
  DEBUG("Sending foward\n")
    send(socket_tcp,FORWARD,BUFFER_SIZE,0);
}

void send_back (void){
  DEBUG("Sending back\n") 
    send(socket_tcp,BACK,BUFFER_SIZE,0);
}

void send_left (void){
  DEBUG("Sending left\n")
    send(socket_tcp,LEFT,BUFFER_SIZE,0);
}

void send_right (void){
  DEBUG("Sending right\n")
    send(socket_tcp,RIGHT,BUFFER_SIZE,0);
}

void send_exit(void){
  DEBUG("Shutting\n")
    send(socket_tcp,QUIT,BUFFER_SIZE,0);
  CLOSE_SOCKET_TCP;
}


void send_hover(void){
  DEBUG("Hover mode\n")
    send(socket_tcp,TAKE_OFF,BUFFER_SIZE,0);
}

void send_landing(void){
  DEBUG("landing\n")
    send(socket_tcp,LAND,BUFFER_SIZE,0);
}

void send_alt_up(void){
  DEBUG("Alt up\n")
    send(socket_tcp,UP,BUFFER_SIZE,0);
}

void send_alt_down(void){
  DEBUG("Alt down\n")
    send(socket_tcp,DOWN,BUFFER_SIZE,0);
}

void send_camera(void){
  DEBUG("Camera\n")
 
    send(socket_tcp,START_CAMERA,BUFFER_SIZE,0);

}

void send_gps_outdoor(void){
  DEBUG("gps outdoor\n")
  send(socket_tcp,START_OUTDOOR_PATH,BUFFER_SIZE,0);
}

void send_kill_outdoor(void){
  DEBUG("kill outdoor\n")
    send(socket_tcp,KILL_GPS,BUFFER_SIZE,0);
}

void send_indoor(void){
  DEBUG("indoor\n")
    send(socket_tcp,START_INDOOR_PATH,BUFFER_SIZE,0);
}

void send_kill_indoor(void){
  DEBUG("kill indoor\n")
    send(socket_tcp,KILL_INDOOR,BUFFER_SIZE,0);
}

void send_kill_server(void){
  DEBUG("kill server\n")
    send(socket_tcp,SERVER_SHUT,BUFFER_SIZE,0);
}

void send_indoor_position(void){
  DEBUG("indoor position\n")
    send(socket_tcp,INDOOR_POSITION,BUFFER_SIZE,0);
}


void send_outdoor_position(void){
  DEBUG("outdoor position\n")
    send(socket_tcp,OUTDOOR_POSITION,BUFFER_SIZE,0);
}

void receiving(void){
  
  while(1){
    receive = recv(socket_tcp,receive_data,sizeof(receive_data),0);
    receive_data[GPS_BUFFER]= '\0';
    printf("%s\n",receive_data);
      
  }
}
