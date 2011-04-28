/* This file is written by @Shuang Wu and @Yuhan Qiu. */
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>

#include "v4l-test.h"
#include "network.h"

void tcp_send(struct buffer* bs, int sockfd)
{
  //printf("%s", bs[0].start); /* data is in bs[0].start */
  // TODO: Send the image over the network.
  // TODO: Receive compressed video instead.
  
  int new_fd;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  int sin_size;

  while(1){
    read_frame();
    //trying until connected
    sin_size=sizeof(struct sockaddr_in);
    if(-1==(new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))){
      fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
      exit(1);
    }
  
    printf("Accept!\n");
     
    if(-1==send(new_fd,bs[0].start,strlen(bs[0].start),0)){
      fprintf(stderr,"Write Error:%s\n",strerror(errno));

      exit(1);
    }

    close(new_fd);
  }

  close(sockfd);
  exit(0);
}
