#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 200

/*! 
    @file conn_gethost.c
    @author Michal Musialik 
*/
/*
This software gather various information about hosts IP
 */
int main (void){

  /*initializing variable*/
  char ip_buffer [BUFFER_SIZE] ;
  struct hostent * Host;
  
  /*Setting variable and getting information about host through
   hostent struct*/
  gethostname ( ip_buffer , BUFFER_SIZE );
  Host = ( struct hostent * ) gethostbyname ( ip_buffer );
  printf("Host Name : %s\n", Host->h_name );
  printf("Host IP Address : %s\n", inet_ntoa(*((struct in_addr *)Host->h_addr)));
  printf("Host Adress type : %i\n",Host->h_addrtype);
  printf("Host IP length : %i\n", Host->h_length);
  
  return 0;
} 
