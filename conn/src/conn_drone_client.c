#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>

/* @authors: mgbah iheanacho & nelson sekitoleko
 * @function: the main method. only for testing, will be removed before final integration.
 *
 */

int main(void){
  getMyInfo();
  int s = socket_file_descriptor();
  requestConnection(s);
  send_data(s);
  return 0;
}

/* get client info
 * @info: taken from michal's code.
 *
 */
getMyInfo(){
  int s = socket_file_descriptor();
  char ip_buffer[200];
  struct hostent *Host;
  gethostname ( ip_buffer , 200);
  Host = ( struct hostent * ) gethostbyname ( ip_buffer );//struct for various ip parts	
  printf ( "Host name : %s\n" , Host->h_name );//printing host		
  printf("Host IP Address : %d\n", inet_ntoa(*((struct in_addr *)Host->h_addr)));//printing ip address		
  printf("Host Adress type : %i\n",Host->h_addrtype);//printing addresstype
  printf("Host IP length : %i\n", Host->h_length);//printing ip address length
}

/* @requestConnection: requests a connection to a server using the socket as a parameter.
 * @mysocket: takes a socket as a parameter.
 * @struct serveaddr: a struct containing the server information
 * @struct host: a struct containing the information of the host
 */
requestConnection(int mysocket){
  struct sockaddr_in serveaddr;
  struct hostent *host;
  int serverStat, socketStat;
  host = gethostbyname("127.0.0.1");//hard coded data, change to your ip address for connection.

  serveaddr.sin_family = AF_INET;
  serveaddr.sin_port = htons(9600);
  serveaddr.sin_addr = *((struct in_addr *)host->h_addr);
  bzero(&(serveaddr.sin_zero),8);

  socketStat = checkSocket(mysocket);
  if(socketStat == -1){
    perror("error...\n");
    exit(1);
  }else{
    printf("socket created\n");
  }
  serverStat = connect(mysocket,(struct sockaddr *)&serveaddr,sizeof(struct sockaddr));
  if(serverStat == -1){
    perror("connection error\n");
    exit(1);
  }else{
    printf("connected...\n");
  }
}

/*@send_data: sends data between connected server.
 *@sock_in_use: a socket used to connect the server
 *
 */
send_data(int sock_in_use){
  int byte;
  char data_send[200], recv_data[200];
  while(1){
  printf("enter messages to be sent..\n");
  scanf("%s",data_send);
  if(strcmp(data_send,"exit") != 0){
    send(sock_in_use,data_send,strlen(data_send),0);
  }else{
     send(sock_in_use,data_send,strlen(data_send),0);
     printf("Closing client\n");
     close(sock_in_use);
     break;
  }
  byte = recv(sock_in_use,recv_data,200,0);
  recv_data[byte] = '\0';
  printf("recieved %s\n",recv_data);
  }
}
  
