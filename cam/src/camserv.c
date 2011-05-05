/*
*
*
*
*created by Abdirashid Jama
*
*
*
*/

#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>    
#include <unistd.h>   

#define QUE 5    /* Maximum  connection requests to handle */

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
  /****************************************************************************************************************************************************/
  /*Video Capturing and compression codes here*/
  /****************************************************************************************************************************************************/
    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
{
        Exit_Error_func("socket failed");
}

      
    /* Construct local address structure */
    memset(&Server_Address, 0, sizeof(Server_Address));   /* makes the structure zero*/
    Server_Address.sin_family = AF_INET;                /* Internet address family */
    Server_Address.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    Server_Address.sin_port = htons(server_port);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &Server_Address, sizeof(Server_Address)) < 0)
{
        Exit_Error_func("binding failed");
}
 printf("binding successful\n");
printf("socket successful \n");
    /* Mark the socket to listen for incoming connections */
    if (listen(servSock, QUE) < 0)
        Exit_Error_func("listening failed");

    
/* Main server loop - accept and handle requests */
printf("listening \n");

/* For now this server is handling strinf messages it will handle video stream in the future. Video captured will be put up*/
        while (1) {
                 clntLen = sizeof(Client_adress);
                if ( (clntSock = accept(servSock, (struct sockaddr *)&Client_adress, &clntLen)) < 0) {
                        
                        Exit_Error_func("Accepting failed");
                }
                printf("accepting \n");
		printf("waiting for msg to handle \n");

                n = recv(clntSock, msg_buf, sizeof(msg_buf), 0);
                while (n > 0)
                {   if(strcmp (msg_buf, "set_camera_available")){

                    send(clntSock, "true\n",n, 0);
                    n = recv(clntSock, msg_buf, sizeof(msg_buf), 0);
		}
		else{
                printf("wrong message \n");
		}
                }
                close(clntSock);    /* Close client socket */
        	}

        
    }



