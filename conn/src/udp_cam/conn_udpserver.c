/*!
 *  @file conn_udpserver.c
 *
 *  @brief tcpclien file
 *
 *  @author Michal Musialik
 *  @date 2011-05-17 - initiazing udpserver
 *
 *  Description:
 *  This is a udp server that start camra ffserver and ffmpeg.
 *
 */

#define BUFFER_SIZE 5
#define PORT 9000

struct sockaddr_in server;
struct sockaddr_in client;

int sock;
int len = sizeof(struct sockaddr_in);
int byte;
char check[BUFFER_SIZE];

/*Creating UDP socket*/
void create_socket(void){ 
  if((sock=socket(AF_INET,SOCK_DGRAM,0))<0){
    perror("socket()");
  }
  else{
    printf("socket ok\n");
  }
  
}

/*Binding UDP socket*/
void socket_address_bind(void){
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr =INADDR_ANY;
  if (bind (sock,(struct sockaddr *)&server,sizeof(server))<0){
    perror("bind()\n");
  }
  else{
    printf("bind ok\n");
  }

}

/*Receiving start ffserver & ffmpeg command from client*/
void socket_server_cam(void){
  byte = recvfrom(sock,check,sizeof(check),0,(struct sockaddr *)&client, &len);
  check[byte] = '\0';
  printf("%s\n",check);
  if((strcmp(check,"check"))==0){
    printf("cam\n");
    system("ffserver & ffmpeg -r 15 -s 352x288 -f video4linux2 -i /dev/video1 http://localhost:8090/feed1.ffm > /dev/null 2>/dev/null &");
  }
  close(sock);
}
