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
	int serversock;
	int clientsock;

/*	data variables */
	int imgsize;
	int bytes;
	int new_data;
	IplImage *gray_frame; // to hold the processed images

	pthread_mutex_t	 m = PTHREAD_MUTEX_INITIALIZER;

/*	the video server function*/
void video_server(void)
{

	//pthread_t 	thread_new;

	struct sockaddr_in server;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	pthread_setcancelstate(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

/*	OPEN SERVERSOCK*/
	if ((serversock = socket (PF_INET,SOCK_STREAM,0)) == -1){
	terminate("error: socket() could not open",1);
	}

/*	SET UP THE IP AND PORT NUMBER OF THE SERVER*/
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT_NUMBER);
	server.sin_addr.s_addr = INADDR_ANY;


/*	BIND THE SOCKET*/
	if(bind(serversock, (const void*) &server, sizeof(server)) == -1){
	terminate("error: bind() failed ",1);
	}

/*	listen for client connection*/
	if (listen(serversock, 10) == -1){
	terminate("Listening failed",1);
	}
	else{
	printf("Listening ...\n");
	}

/* accept request for connection from a client*/
	if ((clientsock = accept(serversock, NULL, NULL)) == -1){
	terminate("accept failed", 1);
	}
	else {
	printf("connection accepted ...\nNow sending frames to client...\n");
	}

/*	get the frame size to be sent out, we will be sending the gray_frame from the
	camera_capture*/
	imgsize = gray_frame -> imageSize;

/*	send frames to client using pthread, we first need to lock then unlock thread*/
	while(new_data != 0){
	pthread_mutex_lock(&m);
		if(new_data){
		bytes = send (clientsock, gray_frame -> imageData, imgsize, 0);

		}
	pthread_mutex_unlock(&m);
	
	if (bytes != imgsize){	
	fprintf(stderr, "Connection was closed at the client side.\n");
	close(clientsock);

		if ((clientsock = accept(serversock, NULL, NULL)) == -1){
		terminate("Accept failed",1);
		}
	}

/*	cancel the pthread*/
	pthread_testcancel();
	
	usleep(1000);
	}


}

/*	A function to quit a process safely */
void terminate(char*msg, int retval)
{
	
	if (retval == 0){
		if (msg){ fprintf(stdout,"%s\n", msg);}
	}
	else{
		if(msg) {fprintf(stderr, "%s\n", msg);}
	}

	close(clientsock);
	close(serversock);
	pthread_mutex_destroy(&m);
	exit(retval);

}//End of file

