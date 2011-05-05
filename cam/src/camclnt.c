
/*TCP client codes */

/* Author Abdirashid Jama, Henry Ikuh */
#include <stdio.h>      
#include <sys/socket.h>
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>    
#include "../include/cv.h"
#include "../include/highgui.h"
#define DEFPORT       3434            /* default port number */

  IplImage* image_bytes;
  void Exit_Error_func(char *errorMessage);  /* Error handling function */


  int main(int argc, char *argv[])
  {

  int getting_data = 0;
  int sock;                        /* Socket descriptor */
  struct sockaddr_in Server_Address; /*  server address */
  unsigned short Server_Port;     /* server port */
  char *server_IP;                 /* Server IP address  */
  char    *server;           /* pointer to server name  */
  char    localhost[] =   "localhost";    /* default server name            */
  //int connect_toserver;
  int width=640;
  int height=480;
  int key;
  int i;
  int j;
  int k;
  unsigned short *connect_toserver;
  void compress_and_show();
  void Exit_Error_func(char *errorMessage)
  
  {
     perror(errorMessage);
     exit(1);
  }


  
  /* Constructing the server address structure */
  memset(&Server_Address, 0, sizeof(Server_Address));     /* Zero out the structure */
  Server_Address.sin_family      = AF_INET;             /* adress of the Internet family */
    
  if (argc > 2) {                 /* if the protocol port specified   */
  Server_Port = atoi(argv[2]);   /* convert the port to binary*/
  } 
  else {
  Server_Port = DEFPORT;       /* use default port number */
       }
  if (Server_Port > 0)                   /* check if the value is allowed */
  Server_Address.sin_port = htons((u_short)Server_Port);
  else {                          /* print error message and exit */
		        Exit_Error_func("valid port number needed");

  }

  /* if the server name isn't specified use localhost's adress or name */

  if (argc < 2) 
  {
  server = argv[1];         /* if server argument specified   */
  } 
  else 
  {
  server = localhost;
  }


  /* creating the image */ 

  image_bytes = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

  cvZero(image_bytes);

    /* Creating a stream socket using TCP */

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        Exit_Error_func("socket() failed");
	}
    
        printf("socket created successfully\n");

    /* Connect the socket to the specified server. */

 


  /* connect to the video server */

  //connect_toserver = connect(mysocket,(struct sockaddr *)&serveaddr,sizeof(struct sockaddr));
  if(connect(sock, (struct sockaddr*)&Server_Address, sizeof(Server_Address))==-1)
  
  {

  Exit_Error_func("connect() failed");
  }

  else
  {
  printf("connection successfull\n");
  }
  //int image_size = image_bytes->imageSize;

  char received_data[image_bytes->imageSize];

  /* start receiving images */

  while(image_bytes->imageSize>0) // instead of while (1) loop

  {

  /* Here we get the raw images from the server */
  int data;

  for(i = 0; i < image_bytes->imageSize; i += data) {
  
  if ((data = recv(sock, received_data + i, image_bytes ->imageSize - i, 0)) == -1) {

  Exit_Error_func("recv failed");

  }

  }
  getting_data = 1;
  printf("images received");

  /* converting the received data to OpenCV's IplImage format so that it can be shown on the client side */


  for (i = 0, k = 0; i < image_bytes->height; i++) {

  for (j = 0; j < image_bytes->width; j++) {

  ((uchar*)(image_bytes->imageData + i * image_bytes->widthStep))[j] = received_data[k++];

  }
  }
  printf("images converted");

  
  
  
  cvShowImage("client video stream", image_bytes);

  //cvShowImage("client video stream", image_bytes);


  key = cvWaitKey(10);


  }

  fprintf(stdout, "To stop the video stream use crtl + C \n");

  cvNamedWindow("client video stream ", CV_WINDOW_AUTOSIZE);

 

  


  /* free the memory */

  cvDestroyWindow("client video stream ");//??
  getting_data = 0;


/* Closing the socket. */

  close(sock);

  exit(0);

  }
 

  

        
        

   
  


