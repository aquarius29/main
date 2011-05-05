/*-------------------------------------------------------------------------------------------------------
**	terminate.c
**	Authors: Henry Ikuh, Abdirashid Jama

* This function terminates any operation that does not satisfy the request and also close sockets and 
* other running threads

* file name: terminate.c
 
*--------------------------------------------------------------------------------------------------------*/

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "../include/cv.h"
#include "../include/highgui.h"

int serversock;
	int clientsock;
	CvCapture* video_capture;
	IplImage* gray_frame;
void terminate(char*msg, int retval)
{
	
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	if (retval == 0){
		if (msg){ fprintf(stdout,"%s\n", msg);}
	}
	else{
		if(msg) {fprintf(stderr, "%s\n", msg);}
	}

/* close all opened sockets and release capture, destroy active thread*/
	if (serversock)
		close(serversock);
	if (clientsock)
		close (clientsock);
	if (gray_frame)
		cvReleaseImage(&gray_frame);
	if (video_capture)
		cvReleaseCapture(&video_capture);

	pthread_mutex_destroy(&mutex);
/*	exit return */
	exit(retval);

}
