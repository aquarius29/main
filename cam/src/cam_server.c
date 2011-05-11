/**
  * Module: cam_server.c
  *
  * Author (s): Ikuh Henry, Abdirashid Jama
  * Created: 2011-04-24
  * Version: 0.01
  * history: 2011-04-24 - created the initial file
			 2011-04-28 - connect, send video over TCP network to client
			 2011-05-06 - re structure source code.

  * Description: a testing tcp server for video streaming.
*/

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "cam_interface.h"
#include "cam_cam.h"

/*	define a default port number of ther server */
#define PORT_NUMBER 5457

/*	sockets variables */
    int server_socket;
    int client_socket;

/*	data variables */
    int bytes;
    int new_data;
    IplImage *gray_frame; /*to hold the processed images*/

    pthread_mutex_t	 m = PTHREAD_MUTEX_INITIALIZER;

/*	the video server function*/
void video_server(void)
{

 
    struct sockaddr_in cam_server;

/*	OPEN SERVER SOCKET*/
    if ((server_socket = socket (PF_INET,SOCK_STREAM,0)) == -1){
    terminate("error: socket() could not open",1);
    }

/*	SET UP THE IP AND PORT NUMBER OF THE SERVER*/
    memset(&cam_server, 0, sizeof(cam_server));
    cam_server.sin_family = AF_INET;
    cam_server.sin_port = htons(PORT_NUMBER);
    cam_server.sin_addr.s_addr = INADDR_ANY;


/*	BIND THE SOCKET*/
    if(bind(server_socket, (const void*) &cam_server, sizeof(cam_server)) == -1){
    terminate("error: bind failed ",1);
    }

/*	listen for  a client connection*/
    if (listen(server_socket, 10) == -1){
    terminate("Listening  failed",1);
    }
    else{
    printf("Listening ...\n");
    }

/* accept request for connection from a client*/
    if ((client_socket = accept(server_socket, NULL, NULL)) == -1){
    terminate("accept failed", 1);
    }
    else {
    printf("connection accepted ...\nNow sending frames to client...\n");
    }

/*	send frames to client using pthread, we first need to lock then unlock thread*/
    while(new_data != 0){
    pthread_mutex_lock(&m);
        if(new_data){
        bytes = send (client_socket, gray_frame -> imageData, gray_frame ->imageSize, 0);

        }
    pthread_mutex_unlock(&m);
	
    if (bytes != gray_frame ->imageSize){	
    fprintf(stderr, "Connection was closed at the client side.\n");
    close(client_socket);

        if ((client_socket = accept(server_socket, NULL, NULL)) == -1){
        terminate("Accept failed",1);
        }
    }
	
    usleep(100);
    }

}

/*	A function to quit a process safely */
void terminate(char*msg, int ret_value)
{
	
    if(ret_value == 0){
    if(msg){fprintf(stdout,"%s\n", msg);}
    }
    else{
        if(msg) {fprintf(stderr, "%s\n", msg);}
    }

    close(client_socket);
    close(server_socket);
    pthread_mutex_destroy(&m);
    exit(ret_value);

}//End of file

