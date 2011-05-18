/*!
 *  @file conn_udpclient.c
 *
 *  @brief tcpclien file
 *
 *  @author Michal Musialik
 *  @date 2011-05-17 - initiazing udpserver
 *
 *  Description:
 *  This is a udpclient that start camra remotely.
 *
 */

#define PORT 9000
#define BUFFER_SIZE 10
#define BUFFER_CHECK_SIZE 5


struct sockaddr_in server;
struct sockaddr_in client;
struct hostent *host;

int sock;
int len = sizeof(struct sockaddr_in);
int byte;
char data [BUFFER_SIZE];
char check[BUFFER_CHECK_SIZE] = "check";

void socket_host(void){
 host= (struct hostent *) gethostbyname((char *)"127.0.0.1");
}

void socket_create(void){
if((sock = socket(AF_INET, SOCK_DGRAM, 0))<0){
    perror("socket()");
  }
  else{
    printf("socket ok\n");
  }
}

void socket_address_bind(void){
 client.sin_family = AF_INET;
  client.sin_port = htons(PORT);
 client.sin_addr = *((struct in_addr *)host->h_addr);
}

void socket_server_check(void){
   sendto(sock,check,sizeof(check),0,(struct sockaddr *)&client,sizeof(struct sockaddr_in));
   close(sock);
}
