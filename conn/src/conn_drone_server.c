#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#define MYPORT 9600


/* @authors: mgbah iheanacho & nelson sekitoleko
 * 
 *
 */
struct sockaddr_in my_addr;
struct sockaddr_in clientaddr;

/* @bindStatus: binds the socket
 * @socketfd: the socket used to bind.
 * @return: returns an integer(1) if binding is succesful or 0 if unsuccesful
 */
int bindStatus(int socketfd){
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(MYPORT);
  my_addr.sin_addr.s_addr= INADDR_ANY;
  if(bind(socketfd,(struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
    return 0;
  }else{
    return 1;
  }
}

/* 
 * @listenStat: listens to the socket 
 * @sockfd: socket used to listen for incoming communication
 * @capacity_conn: number of connnections which can be handled by the server
 * @return: returns an integer(1) if listening is succesful or 0 if unsuccesful
 */
int listenStat(int sockfd,int capacity_conn){
  if(listen(sockfd,capacity_conn) ==-1){
    return 0;
  }else{
    return 1;
  }
}

/*
 * @newSock: creates a new socket for accepting a connection 
 * @oldSocket: the old socket requiered to make create the new socket
 */
int newSock(int oldSocket){
  int sin_size;
  sin_size = sizeof(struct sockaddr_in);
  return accept(oldSocket,(struct sockaddr *)&clientaddr,&sin_size);
}


/* acccept an incoming communication */
void acceptStat(int sFD){
  int newFileDesc;
  newFileDesc = newSock(sFD);
  if(newFileDesc == -1){
    printf("error..\n");
  }else{
    printf("connection accepted\n");
  }
}

/* @mk_Connct: make connection by giving the socket file descriptor and the number of connections the connection can hold in a queue
 * @sfd: socket used to make a connection
 * @cap_conn: number of connections the server can hold
 * @thier_addr: a struct containing the 
 */

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
   acceptStat(sfd);
}



send_data(int sock_in_use){
  int byte, newSocket;
  newSocket = newSock(sock_in_use);
  char dataRecvd[200];
  while(1){
    byte = recv(sock_in_use,dataRecvd,200,0);
    dataRecvd[byte] = '\0';
    if(strcmp(dataRecvd,"exit")== 0){
      close(newSocket);			
      printf("server closing...\n");
      close(newSocket);
      break;
    }else{
      printf("%s\n", dataRecvd);
       send(newSocket,dataRecvd,strlen(dataRecvd),0);
    }
  }
}


int main(void){  
  int sD = socket_file_descriptor() ;
  struct sockaddr_in their_addr;
  their_addr.sin_family = AF_INET;
  their_addr.sin_port = htons(3490);
  their_addr.sin_addr.s_addr= INADDR_ANY;
   mk_Connct(sD,10,their_addr);
   send_data(sD);
}
