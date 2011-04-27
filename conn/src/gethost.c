#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 200
/*this is software for getting information about mine ip*/

int main (void){

  /*initializing variable*/
  char ip_buffer [BUFFER_SIZE] ;
  struct hostent * Host;

  /*binding variable and buffer size to gethostname */
  gethostname ( ip_buffer , BUFFER_SIZE );
  Host = ( struct hostent * ) gethostbyname ( ip_buffer );//struct for various ip parts
  printf ( "Host name : %s\n" , Host->h_name );//printing host
  printf("Host IP Address : %s\n", inet_ntoa(*((struct in_addr *)Host->h_addr)));//printing ip address
  printf("Host Adress type : %i\n",Host->h_addrtype);//printing addresstype
  printf("Host IP length : %i\n", Host->h_length);//printing ip address length
  return 0;
} 
