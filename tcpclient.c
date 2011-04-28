<<<<<<< HEAD
=======
/*tcpclient is by @Yuhan Qiu and @Shuang Wu*/
>>>>>>> 446597c5f201dd66ff2e0a4a79c2462fcca8e6d0
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
int main(int argc,char *argv[])
{
  int sockfd;
  char buffer[1024];
  struct sockaddr_in server_addr;
  struct hostent *host;
  int portnumber,nbytes;
while(1){
  if(3!=argc){
    fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
    exit(1);
  }

  if(NULL==(host=gethostbyname(argv[1]))){
    fprintf(stderr,"Hostname error:%s\a\n",strerror(errno));
    exit(1);
  }

  if((portnumber=atoi(argv[2]))<0){
    fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
    exit(1);
  }

  if(1==(sockfd=socket(AF_INET,SOCK_STREAM,0))){
    fprintf(stderr,"Socket error:%s\a\n",strerror(errno));
    exit(1);
  }
  printf("Socket id is %d\n",sockfd);

  bzero(&server_addr,sizeof(struct sockaddr_in));

  server_addr.sin_family=AF_INET;
  server_addr.sin_port=portnumber;
  server_addr.sin_addr=*((struct in_addr *)host->h_addr);
  server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

  if(-1==connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))){
    fprintf(stderr,"Connect Error:%s\n\a",strerror(errno));
    exit(1);
  }
  printf("Connect\n");

  if(-1==(nbytes=recv(sockfd,buffer,1024,0))){
    fprintf(stderr,"Read Error:%s\n\a",strerror(errno));
    exit(1);
  }
  buffer[nbytes]='\0';
  printf("I have received:%s\n",buffer);
  close(sockfd);
}
  exit(0);
}
