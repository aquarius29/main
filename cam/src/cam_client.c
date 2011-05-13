/**
  * Module: cam_client.c
  *
  * Author (s): Abdirashid Jama, Ikuh Henry
  * Created: 2011-05-01
  * Version: 0.01
  * history: 2011-05-02 - accept localhost
			 2011-05-10 - succesful, get frames from server on another machine
			 

  * Description: a tcp client for video streaming.
*****************************************************************************************************
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "highgui.h"

/*	define a default port number of the server as also define in the server */
#define PORT 5457


/* variable declaration for data to be received */
	//int getting_data;
	int width = 640;
	int height = 480;
	int key;
	int frame;
	int total_covt;// to change soon
	int converted;
	int data;


/*	socket variables and server port */
	in_port_t server_port = PORT;
	int cln_sock;
	struct sockaddr_in server_address; 


/*	declare variable to hold to frames that will be be from the server, its ipl image */
	IplImage* sent_frames;

/*  function prototypes  */
	void initialize_client (int argc, char *argv[]);
	void create_socket(void);
	void establish_connection(void);
	void receive_and_convert(void);
	void display(void);
	void close_and_free(void);


/*	client initializer function  */
void initialize_client (int argc, char *argv[])
{
/*	CONTROL NUMBER OF ARGUMENTS FOR THE CLIENT / USER */
	if (argc < 1|| argc > 2)
	perror(" Wrong Parameters: Enter Only <SERVER-IP-ADDRESS>");
  
/*create a channel for the sent_frames, which is same as expected channel from the server */
	sent_frames = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1); 
	cvZero(sent_frames);
  
/*Setup the server address structure in the client */
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
 
/* Convert the server IPv4 or IPv6 address to binary */
	char *server_IP = argv[1];
	int bin_ip_num = inet_pton(AF_INET, server_IP, &server_address.sin_addr.s_addr);

/* bin_ip_num : is the Binary IP address number of the converted server IP address */
	if (bin_ip_num == 0)
	perror("Ip adress should be dotted");
		else if (bin_ip_num < 0)
		perror("inet_pton() failed");
	server_address.sin_port = htons(server_port);

}

/*	function to create the client socket, using TCP protocol */
void create_socket(void)
{
	cln_sock= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (cln_sock < 0)
	perror("Socket creation failed");

}

/*	Establish connection between the client and the listening server */
void establish_connection(void) 
{

	if (connect(cln_sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
	perror("Could not Connect to the Server");

	else{
	printf("connection successfull\n");
	}

}


/* This function receives the frames from the server after connection*/
void receive_and_convert(void)
{
	char received_data[sent_frames->imageSize]; /*to store received bytes*/
	while(sent_frames-> imageSize > 0){

	/* we get 1-channel raw (gray) images from the server */
	for(frame = 0; frame < sent_frames->imageSize; frame += data) {
	/*retrieve frames from the client socket*/
		if ((data = recv(cln_sock, received_data + frame, sent_frames ->imageSize - frame, 0)) == -1) {
		perror("recv() failed");
		}
	}
	//getting_data = 1;
	printf("images-received...");

/* converting the received raw data for display*/
	for (frame = 0, converted = 0; frame < sent_frames-> height; frame++) {
		for (total_covt = 0; total_covt < sent_frames->width; total_covt++) {
		((uchar*)(sent_frames->imageData + frame * sent_frames->widthStep))[total_covt] = received_data[converted++];
		}
	}

	printf("images-converted...");
	display();

}//end of loop

	if(sent_frames-> imageSize < 0){
	close_and_free();
	}
}


/*	Display the frames as video */
void display(void)
{
	cvNamedWindow("QUADROTOR-CLIENT",0); 
	cvResizeWindow("QUADROTOR-SERVER",320,240);
	cvShowImage("QUADROTOR-CLIENT", sent_frames);
	key = cvWaitKey(25);
}


/* close socket and destroy window*/
void close_and_free(void)
{
	cvDestroyWindow("client video stream ");
	//getting_data = 0;
	close(cln_sock);
	exit(0);
}

