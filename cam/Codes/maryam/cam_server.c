/*-------------------------------------------------------------------------------------------------------
**	cam_server.c
**	Authurs: Maryam Aghaee

* The program captures frames from webcam using opencv computer vision library in c.
* file name: video_server.c
 
**	Prerequisite:
**	Install: ffmpeg
**	OpenCV
**	v4l2 (comes with your linux distribution)

**	References: http://pubs.opengroup.org/onlinepubs/007908799/xsh/pthread_create.html
				http://www.ffmpeg.org/
				http://opencv.willowgarage.com/documentation/reading_and_writing_images_and_video.html
				nashrudding.com
				http://pubs.opengroup.org/onlinepubs/007908799/xsh/pthread.h.html
*--------------------------------------------------------------------------------------------------------*/

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//#include <time.h>
//#include "../include/cv.h"
#include "../include/highgui.h"

/*	define a default port number of ther server */
#define PORT_NUMBER 5457

/*	sockets variables */
int serversock;
int clientsock;
int new_data;
IplImage* gray_frame;
int imgsize;
int bytes;

/*	*/
void video_server(void* arg)
{
	pthread_mutex_t	 mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_t 	thread_new;

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
	while(1){
	pthread_mutex_lock(&mutex);
		if(new_data){
		bytes = send (clientsock, gray_frame -> imageData, imgsize, 0);
		//new_data = 0;
		}
	
	pthread_mutex_unlock(&mutex);
	
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
	close(clientsock);
}//End of file
