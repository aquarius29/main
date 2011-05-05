#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <netdb.h>

#define MYPORT 9600

/* author: mgbah iheanacho
   version: 0.001
 */
/* this creates a socket */



/* binds the socket */
int bindStatus(int socketfd){
  struct sockaddr_in my_addr;
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(MYPORT);
  my_addr.sin_addr.s_addr= INADDR_ANY;
  if(bind(socketfd,(struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
    return 0;
  }else{
    return 1;
  }
}

/* listens to the socket */
int listenStat(int sockfd,int capacity_conn){
  if(listen(sockfd,capacity_conn) ==-1){
    return 0;
  }else{
    return 1;
  }
}

/* acccept an incoming communication */
void acceptStat(int sFD, struct sockaddr_in clientaddr){
  int sin_size, newFileDesc;
  sin_size = sizeof(struct sockaddr_in);
  newFileDesc = accept(sFD,(struct sockaddr *)&clientaddr,&sin_size);
  if(newFileDesc == -1){
    printf("error..\n");
  }else{
    printf("connection accepted\n");
  }
}

/* make connection by giving the socket file descriptor and the number of connections the connection can hold in a queue */

void mk_Connct(int sfd,int cap_conn, struct sockaddr_in their_addr){
  int sockStat = checkSocket(sfd);
  int bindStat = bindStatus(sfd);
  int LstStat = listenStat(sfd,cap_conn);

  if(sockStat == 1 && bindStat == 1 && LstStat == 1 ){
    printf("socket created\n..binding succesful\n..listening for incoming connections\n..");
  }else{
    printf("error:");
    if(sockStat == 0){
      printf("socket not created...\n");
	}else if(bindStat == 0){
      printf("binding failed...\n");
    }else if(LstStat == 0){
      printf("Listen failed...\n");
    }
    else{
      printf("information missing");
    }
  }
   acceptStat(sfd,their_addr);
   close(sfd);
}


int main(void){  
  int sD = socket_file_descriptor() ;
  struct sockaddr_in their_addr;
  their_addr.sin_family = AF_INET;
  their_addr.sin_port = htons(9600);
  their_addr.sin_addr.s_addr= INADDR_ANY;
   mk_Connct(sD,10,their_addr);
}

