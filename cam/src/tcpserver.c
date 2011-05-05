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

  int sockfd,new_fd;

  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  int sin_size,portnumber;

  const char hello[]="Hello\n";

  if(2!=argc){
  
    fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);

    exit(1);
  }

  if((portnumber=atoi(argv[1]))<0){

    fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
    exit(1);
  }

  //creating the server
  if(1==(sockfd=socket(AF_INET,SOCK_STREAM,0))){

    fprintf(stderr,"Socket error:%s portnumber\a\n",strerror(errno));

    exit(1);
  }

  printf("Socket id is %d\n",sockfd);

  bzero(&server_addr,sizeof(struct sockaddr_in));

  server_addr.sin_family=AF_INET;
  server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  server_addr.sin_port=portnumber;
  
  //binding sockfd

  if(-1==bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))){
    fprintf(stderr,"Bind error:%s\n\a",strerror(errno));

    exit(1);

  }

  printf("Bind\n");


  //listening sockfd
  if(-1==(listen(sockfd,5))){
    fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
    exit(1);
  }
  printf("Listen\n");

  while(1){

    //trying until connected
    sin_size=sizeof(struct sockaddr_in);
    if(-1==(new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))){
      fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
      exit(1);
    }
  
    printf("Accept!\n");
     
    if(-1==send(new_fd,hello,strlen(hello),0)){
      fprintf(stderr,"Write Error:%s\n",strerror(errno));

      exit(1);
    }

    close(new_fd);
  }

  close(sockfd);
  exit(0);
}
