
/*Author Abdirashid Jama and Henry
i integrated my camserver codes and the codes for capturing videos writen by Henry and its working now but not final*/
#include <stdio.h>     
#include <sys/socket.h>
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     
#include <netinet/in.h>
#include <pthread.h>
#include "cv.h"
#include "highgui.h"
#define MAXPENDING 5    /* Maximum outstanding connection requests */
#define RCVBUFSIZE 1000
// Define a port number for the server machine
#define PORT_NUM 3434

CvCapture*    capture;
IplImage*    cam_video;
IplImage*    file_video;
 unsigned int clntLen;            /* Length of client address data structure */
int            is_data_ready = 0;
int            server_socket, clntSock;
struct sockaddr_in Server_Address; /* Local address */
struct sockaddr_in Client_adress; /* Client address */
int servSock;                    /* Socket descriptor for server */
int clntSock;                    /* Socket descriptor for client */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// Function Prototypes for our video server and "peaceful" exit_now
void* videoServer(void* arg);
void  exit_now(char* msg, int retval);
//void Exit_error_func(char *errorMessage);  /* Error handling function */

struct sockaddr_in Server_Address; /* Local address */
struct sockaddr_in Client_adress; /* Client address */

    

int main(int argc, char **argv)
{
   
    
    pthread_t     thread_s;
   int            key;
/*void Exit_error_func(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}*/


if (argc == 2) {

       capture = cvCaptureFromFile(argv[1]);

   } else {

       capture = cvCaptureFromCAM(0);

   }



   if (!capture) {

      exit_now("cvCapture failed",1);

   }



   cam_video = cvQueryFrame(capture);

   file_video = cvCreateImage(cvGetSize(cam_video), IPL_DEPTH_8U, 1);



   cvZero(file_video);

   cvNamedWindow("Jama's player", CV_WINDOW_AUTOSIZE);



   /* print the width and height of the frame, needed by the client */

   fprintf(stdout, "width:  %d\nheight: %d\n\n", cam_video->width, cam_video->height);

   fprintf(stdout, "Press 'q' to exit_now.\n\n");



   /* run the streaming server as a separate thread */

   if (pthread_create(&thread_s, NULL, videoServer, NULL)) {

       exit_now("pthread_create failed.",1);

   }



   while(key != 'q') {

       /* get a frame from camera */

       cam_video = cvQueryFrame(capture);

       if (!cam_video) break;



       cam_video->origin = 0;

       //cvFlip(cam_video, cam_video, -1); //i dont need it to flip if its file video.



       /**

        * convert to grayscale

         */

       pthread_mutex_lock(&mutex);

       cvCvtColor(cam_video, file_video, CV_BGR2GRAY);

       is_data_ready = 1;

       pthread_mutex_unlock(&mutex);



       /* also display the video here on server */

       cvShowImage("Rashid's Player", cam_video);

       key = cvWaitKey(20);

   }



   /* user has pressed 'q', terminate the streaming server */

   if (pthread_cancel(thread_s)) {

       exit_now("pthread_cancel failed.",1);

   }



   /* free memory */

   cvDestroyWindow("stream_server");

   exit_now(NULL,0);

}



/**

* This is the streaming server, run as a separate thread

* This function waits for a client to connect, and send the grayscaled images

*/

void* videoServer(void* arg)

{

   struct sockaddr_in server;



   /* make this thread cancellable using pthread_cancel() */

   pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

   pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);


    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
{
        exit_now("socket() failed",1);
}

      
    /* Construct local address structure */
    memset(&Server_Address, 0, sizeof(Server_Address));   /* Zero out structure */
    Server_Address.sin_family = AF_INET;                /* Internet address family */
    Server_Address.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    Server_Address.sin_port = htons(PORT_NUM);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &Server_Address, sizeof(Server_Address)) < 0)
{
        exit_now("bind() failed",1);
}
 printf("binding successful\n");
    /* Mark the socket to listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        exit_now("listen() failed",1);
        printf("socket successful \n");
    
/* Main server loop - accept and handle requests */
    printf("listening \n");
       
                 clntLen = sizeof(Client_adress);
                if ( (clntSock = accept(servSock, (struct sockaddr *)&Client_adress, &clntLen)) < 0) {
                        
                        exit_now("Accept() failed",1);
                }
		else{
                printf("accepting \n");
		printf("waiting for msg to handle \n");
		}
               
                /* the size of the data to be sent */

   int imgsize = file_video->imageSize;

   int bytes, i;



   /* start sending images */

   while(1)

   {

       /* send the grayscaled frame, thread safe */

       pthread_mutex_lock(&mutex);

       if (is_data_ready) {

           bytes = send(clntSock, file_video->imageData, imgsize, 0);

           is_data_ready = 0;

       }

       pthread_mutex_unlock(&mutex);



       /* if something went wrong, restart the connection */

       if (bytes != imgsize) {

           fprintf(stderr, "Connection closed.\n");

           close(clntSock);



           if ( (clntSock = accept(servSock, (struct sockaddr *)&Client_adress, &clntLen)) < 0) {
                        
                        exit_now("Accept() failed",0);
                }

       }
                close(clntSock);    /* Close client socket */
        	}
 /* have we terminated yet? */

       pthread_testcancel();



       /* no, take a rest for a while */

       usleep(1000);

   }





/**

* this function provides a way to exit_now nicely from the system

*/

void exit_now(char* msg, int retval)

{

     if (retval == 0) {

    if (msg) {

     fprintf(stdout, "%s\n", msg);

     fprintf(stdout, "\n");

    }

 }

 else {

    if (msg) {

     fprintf(stderr, "%s\n", msg);

     fprintf(stderr, "\n");

    }

 }





   if (clntSock) close(clntSock);

   if (server_socket) close(server_socket);

   if (capture) cvReleaseCapture(&capture);

   if (file_video) cvReleaseImage(&file_video);



   pthread_mutex_destroy(&mutex);



   exit(retval);

}

        
    
   


