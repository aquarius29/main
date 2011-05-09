/*!
 *  @file conn_tcpclient.c
 *
 *  @brief tcpclient file
 *
 *  @author Michal Musialik
 *  @date 2011-05-07
 *  @history    2011-05-07 - first outcast of conn_tcpclient.c file
 */

int socket_tcp;


/*Creating client socket*/
int socket_create(void){
  if((socket_tcp = socket(AF_INET, SOCK_STREAM,0))==-1){
     printf("failed to create a socket\n");
     exit(EXIT_FAILURE);
   }
 else{
     printf("socket is succesfully created\n");
 }
 return 0;
}


/*Binding socket*/
int socket_binding(void){
  /*Drone adress need to be hadcodded*/
  host = (struct hostent *)gethostbyname((char *)"127.0.0.1");
  connecting.sin_family = AF_INET;
  connecting.sin_port = htons(PORT);
  connecting.sin_addr= *((struct in_addr *)host->h_addr);
  memset(&(connecting.sin_zero),'\0',8);
  return 0;
}

/*Connecting to server address*/
int socket_connection(void){
  if(connect(socket_tcp,(struct sockaddr *)&connecting,sizeof(struct sockaddr))==-1){
    perror("connect()");
    exit(1);
  }
  else{
    printf("Client is connected\n");
  }
  return 0;
}

void send_foward (void){
  printf("Sending foward\n");
  send(socket_tcp,GO_FORWARD,BUFFER_SIZE,0);
}

void send_back (void){
  printf("Sending back\n"); 
  send(socket_tcp,GO_BACK,BUFFER_SIZE,0);
}

void send_left (void){
 printf("Sending left\n");
 send(socket_tcp,GO_LEFT,BUFFER_SIZE,0);
}

void send_right (void){
 printf("Sending right\n");
 send(socket_tcp,GO_RIGHT,BUFFER_SIZE,0);
}

void send_exit(void){
 printf("Shutting\n");
 send(socket_tcp,QUIT,BUFFER_SIZE,0);
  close(socket_tcp);
}


void send_auto(void){
  printf("Auto mode\n");
  send(socket_tcp,AUTO,BUFFER_SIZE,0);
}

void send_hover(void){
  printf("Hover mode\n");
  send(socket_tcp,HOVER,BUFFER_SIZE,0);
}

void send_landing(void){
  printf("landing\n");
  send(socket_tcp,LAND,BUFFER_SIZE,0);
}

void send_alt_up(void){
  printf("Alt up\n");
  send(socket_tcp,GO_UP,BUFFER_SIZE,0);
}

void send_alt_down(void){
  printf("Alt down\n");
  send(socket_tcp,GO_DOWN,BUFFER_SIZE,0);
}

void send_camera(void){
  printf("Camera\n");
  send(socket_tcp,"18",BUFFER_SIZE,0);
}

void send_gps(void){
  printf("Gps\n");
  send(socket_tcp,GPS,BUFFER_SIZE,0);
}

void send_server(void){
  printf("Server\n");
  send(socket_tcp,SERVER_SHUT,BUFFER_SIZE,0);
}
