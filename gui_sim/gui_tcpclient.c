
/*Author Michal Musialik*/

#define PORT 9600 // port macro
#define BUFFER_SIZE 32 // message buffer size

int socket_tcp; // tcp_socket name
char send_data[BUFFER_SIZE];

struct sockaddr_in connecting; 
struct hostent * host; //Host adress




int socket_create(){

 if((socket_tcp = socket(AF_INET, SOCK_STREAM,0))==-1){
     printf("failed to create a socket\n");
     exit(EXIT_FAILURE);
   }
 else{
     printf("socket is succesfully created\n");
   
   }
 return 0;
}



int socket_binding(){

  host = (struct hostent *)gethostbyname((char *)"127.0.0.1");
  connecting.sin_family = AF_INET;
  connecting.sin_port = htons(PORT); //my port here
  connecting.sin_addr= *((struct in_addr *)host->h_addr);
  memset(&(connecting.sin_zero),'\0',8);

 return 0;
}

int socket_connection(){


 if(connect(socket_tcp,(struct sockaddr *)&connecting,sizeof(struct sockaddr))==-1)
  {
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
  send(socket_tcp,"3",1,0);
  
}

void send_back (void){
 printf("Sending back\n"); 
 send(socket_tcp,"5",1,0);
  
}

void send_left (void){
 printf("Sending left\n");
  send(socket_tcp,"7",1,0);
  
}

void send_right (void){
 printf("Sending right\n");
  send(socket_tcp,"9",1,0);
  
}

void send_exit(void){
 printf("Shutting\n");
  send(socket_tcp,"quit",4,0);
  close(socket_tcp);
}


void send_auto(void){

  printf("Auto mode\n");
  send(socket_tcp,"17",2,0);
}

void send_hover(void){

  printf("Hover mode\n");
  send(socket_tcp,"15",2,0);
}

void send_landing(){

  printf("landing\n");
  send(socket_tcp,"16",2,0);
}

void send_alt_up(void){

  printf("Alt up\n");
  send(socket_tcp,"11",2,0);
}

void send_alt_down(void){

  printf("Alt down\n");
  send(socket_tcp,"13",2,0);
}

void send_camera(void){
  
  printf("Camera\n");
  send(socket_tcp,"18",2,0);
}

void send_gps(void){

  printf("Gps\n");
  send(socket_tcp,"19",2,0);
}

void send_server(void){
  
  printf("Server\n");
  send(socket_tcp,"shut_server",20,0);
  
}
