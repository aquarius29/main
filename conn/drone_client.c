#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>

/* authors: mgbah iheanacho & nelson */

int main(void){
  getMyInfo();
  int s = socket_file_descriptor();
  requestConnection(s);
  return 0;
}

/* taken  extracted from michal's code */
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

requestConnection(int mysocket){
  struct sockaddr_in serveaddr;
  struct hostent *host;
  int serverStat, socketStat;
  host = gethostbyname("129.16.164.243");

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
