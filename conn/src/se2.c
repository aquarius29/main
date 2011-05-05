/****************************************************************************
* Product: TCP server
* Version: 1.0.0
* Released: Mar 29 2011
* Updated: Apr 05 2011
*
* Copyright 2011. 
*
* @ Ehsan
*
* <Connectivity>
*
*
* Refrences:
* http://shoe.bocks.com/net/
* http://www.pythonprasanna.com/Papers%20and%20Articles/Sockets/udpserver.c
* Application Note C/C++ Coding Standard Quantum Leaps, LLC
* 
*Run with./se
*
****************************************************************************/

/* Includes ...............................................................*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>    /* For create socket */
#include <sys/socket.h>   /* For create socket and binding and connection */
#include <netinet/in.h>   /* For binding */
#include <netdb.h>        /*For converting a hostname into a network address*/
#include <unistd.h>       /* For closing connections */
#include <fcntl.h>        /* For handling more than one connection */
/* Defines ................................................................*/
#define PORT 5000
/* Main ...................................................................*/
int main ()
            {
/* Variable definitions ...................................................*/
   int sk_chk; /*socket creator and check*/
   int bi_chk; /*socket binder and check*/
   int li_chk; /*socket listener and check*/
   int ac_chk_new_sk; /*New socket and connetion acceptor and check */
   int add_len;
   int buf_size=1024 ; // a 1k buffer
   struct sockaddr_in serv_ad;
   struct sockaddr_in clnt_ad;
/* Creating a socket ......................................................*/
             sk_chk= socket(AF_INET,SOCK_STREAM,0);
/* Chech if the socket created ............................................*/
             if (sk_chk<0 ) 
                           {
                            perror("Error creating socket");
                           }
             printf (" Socket created \n");
/* Binding port Defined to the created socket .............................*/
             /* Type of created socket */
             serv_ad.sin_family = AF_INET;
             serv_ad.sin_addr.s_addr = INADDR_ANY;
             /* Set the PORT */
             serv_ad.sin_port = htons(PORT);
             /* Bind the PORT */
             bi_chk= bind(sk_chk,(struct sockaddr *)
                         &serv_ad,sizeof(serv_ad));
/* Check if the binding were done successfully ............................*/
             if (bi_chk<0 )
                           {
                            perror("Error binding socket");
                            exit(EXIT_FAILURE);
                           }
             printf (" %s %d %s", "Port", 
                     PORT, "is Bound to the socket  \n");
/* Start Listening ........................................................*/            
            li_chk=listen (sk_chk,1);	   
/* Check if the listening is OK ...........................................*/
            if (li_chk<0 )
                          {
                            perror("Error listening socket");
		            exit(EXIT_FAILURE);
                          }
             printf (" Listening started \n");
/* Accept connection ............................*/    
             add_len=sizeof(struct sockaddr_in);
             ac_chk_new_sk= accept(sk_chk,(struct sockaddr *)
                                   &clnt_ad,&add_len);       
/* Check if connection is accepted ........................................*/
             if (ac_chk_new_sk<0 )
		                  {
		                   perror("Error accepting socket");
		                  }
              printf (" Access Garanted \n");
/* Receiving data  ............... ........................................*/

              //Start connection
              
             // add_len=sizeof(struct sockaddr_in);

             //Receiving data 
             while(1){
                      char *buffer=(char *)charmalloc(buf_size);
                      struct sockaddr_in clnt_ad;
                      recv(ac_chk_new_sk,buffer,buf_size,0);
 //recvfrom(sk_chk,buffer,buf_size,0,(struct sockaddr *)
                    //           &clnt_ad,&add_len); //Receive
                      printf("\n(%s , %d) sent : ",inet_ntoa(clnt_ad.sin_addr),
                             ntohs(clnt_ad.sin_port)); //print received data
                      printf("%s", buffer);
	              fflush(stdout);
                      }
/* Closing socket .......................................................*/
             
             close (sk_chk);
            }
