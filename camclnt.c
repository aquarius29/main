/* Author Abdirashid Jama */
#include <stdio.h>      
#include <sys/socket.h>
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>    
#define DEFPORT       5200            /* default protocol port number */
#define RCVBUFSIZE 1000   /* Size of receive buffer */

void Exit_Error_func(char *errorMessage);  /* Error handling function */

int main(int argc, char *argv[])
{
     int sock;                        /* Socket descriptor */
     struct sockaddr_in Server_Address; /*  server address */
     unsigned short Server_Port;     /* server port */
     char *server_IP;                 /* Server IP address  */
     char *msg_string;                /* pointer to String to send to  server */
     int     n;               /* number of characters read           */
     char    msg_buf[RCVBUFSIZE];       /* buffer for data from the server     */
     unsigned char camera = 0;
     //char    *text;           /* pointer to user's line of text      */
     char    *server;           /* pointer to server name  */
     char    localhost[] =   "localhost";    /* default server name            */
void Exit_Error_func(char *errorMessage)
{
     perror(errorMessage);
     exit(1);
}


  
/* Construct the server address structure */
    memset(&Server_Address, 0, sizeof(Server_Address));     /* Zero out the structure */
    Server_Address.sin_family      = AF_INET;             /* adress of the Internet family */
    
        if (argc > 2) {                 /* if the protocol port specified   */
                Server_Port = atoi(argv[2]);   /* convert the port to binary*/
        } else {
                Server_Port = DEFPORT;       /* use default port number */
        }
        if (Server_Port > 0)                   /* check if the value is allowed */
                Server_Address.sin_port = htons((u_short)Server_Port);
        else {                          /* print error message and exit */
		        Exit_Error_func("valid port number needed");

        }

        /* if the server name isn't specified use localhost's adress or name */

        if (argc > 1) {
                server = argv[1];         /* if server argument specified   */
        } else {
                server = localhost;
        }

    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        Exit_Error_func("socket() failed");
	}
    
        printf("socket created successfully\n");

    /* Connect the socket to the specified server. */

        if (connect(sock, (struct sockaddr *)&Server_Address, sizeof(Server_Address)) < 0) {
               
	Exit_Error_func("connect() failed");
        }

        /* Repeatedly read data from user and send it to server. */

        msg_string = fgets(msg_buf, sizeof(msg_buf), stdin);
        
                send(sock, msg_buf, strlen(msg_buf), 0);
                n = recv(sock, msg_buf, sizeof(msg_buf), 0);
                write(1, msg_buf, 0);
                msg_string = fgets(msg_buf, sizeof(msg_buf), stdin);
        

        /* Close the socket. */

        close(sock);

        /* Terminate the client program . */

        exit(0);
}


