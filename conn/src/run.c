#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <netdb.h>

/* author: mgbah iheanacho */

int socket_file_descriptor(){
  return socket(AF_INET,SOCK_STREAM,0);
}

checkSocket(int sockFd){
  if(sockFd == -1){
    return 0;
  }else{
    return 1;
  }
}
