#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


#define PORT 9600
#define BUFFER_SIZE 10


int main(){

int server_socket;
  int size;
  int receive_data;
  char buffer[BUFFER_SIZE];
struct hostent *host;
struct sockaddr_in server;
 struct sockaddr_in client;

host= (struct hostent *) gethostbyname((char *)"127.0.0.1");

  if ((server_socket = socket(AF_INET,SOCK_DGRAM,0))<0){
    perror("socket()");
  }
  else{
    printf("Socket ok\n");
  }
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr = *((struct in_addr *)host->h_addr);



  size = sizeof(struct sockaddr);

 printf("Before while \n");
 


while (1)
	{


	  printf("In while \n");
        receive_data = recvfrom(server_socket, buffer, BUFFER_SIZE, 0 , (struct sockaddr *)&client, &size);
 printf("%i", receive_data);
	printf("after reciv\n");

    buffer[receive_data] = '\0';
	  
	  sleep(1);
	  printf("incomming\n");
	  printf("%i", receive_data);
          printf("%s\n", buffer);
	}
 printf("after while");
 close(server_socket);
  return 0;

}
