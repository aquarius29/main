#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#define PORT 9000

int main(){

  int sock;
  int bind;

  struct sockaddr_in server;
  
  if((sock=socket(AF_INET,SOCK_DGRAM,0))<0){
    perror("socket()");
  }
  else{
    printf("socket ok\n");
  }
  
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind (sock,&server,sizeof(server))<0){
    perror("bind()");
  }
  else{
    printf("bind ok");
  }

  
  return 0;
}
