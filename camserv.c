/* Author Abdirashid Jama */
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define MAXPENDING 5    /* Maximum outstanding connection requests */
#define RCVBUFSIZE 1000
void Exit_Error_func(char *errorMessage);  /* Error handling function */
void client_handler(int client_socket);   /* TCP client handling function */

int main(int argc, char *argv[])
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in Server_Address; /* Local address */
    struct sockaddr_in Client_adress; /* Client address */
    unsigned short server_port;     /* Server port */
    unsigned int clntLen;            /* Length of client address data structure */
    char    msg_buf[RCVBUFSIZE];       /* buffer for string the server sends  */
    int     n;               /* number of characters received       */
	
    int status; 
void Exit_Error_func(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}


    if (argc != 2)     /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage:  %s <Server Port>\n", argv[0]);
        exit(1);
    }

    server_port = atoi(argv[1]);  /* First arg:  local port */

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
{
        Exit_Error_func("socket() failed");
}
printf("socket successful \n");
      
    /* Construct local address structure */
    memset(&Server_Address, 0, sizeof(Server_Address));   /* Zero out structure */
    Server_Address.sin_family = AF_INET;                /* Internet address family */
    Server_Address.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    Server_Address.sin_port = htons(server_port);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &Server_Address, sizeof(Server_Address)) < 0)
{
        Exit_Error_func("bind() failed");
}
 printf("binding successful\n");
    /* Mark the socket to listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        Exit_Error_func("listen() failed");

    
/* Main server loop - accept and handle requests */
printf("listening \n");
        while (1) {
                 clntLen = sizeof(Client_adress);
                if ( (clntSock = accept(servSock, (struct sockaddr *)&Client_adress, &clntLen)) < 0) {
                        
                        Exit_Error_func("Accept() failed");
                }
                printf("accepting \n");
		printf("waiting for msg to handle \n");

                n = recv(clntSock, msg_buf, sizeof(msg_buf), 0);
                
		 printf("responding to client");

		while(n>0){
                if(strcmp (msg_buf,"set_camera_available")==0){
                printf("if.................................");
		status=1;
                send(clntSock, status,strlen(status, 0);
                n = recv(clntSock, msg_buf, sizeof(msg_buf), 0);
		  
		}
		else{
		status=0;
                send(clntSock, status,strlen(status), 0);
                printf("wrong message \n");
		close(clntSock); 

		exit(0);
		}
                
                close(clntSock);    /* Close client socket */
        	}
	}	
        
    }
    /* NOT REACHED */


