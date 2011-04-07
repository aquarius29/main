#include "gui_ui_mask.c"
/*Author michal musialik*/

#define IP_BUFFER_LENGTH 200
#define PORT 9600 // port macro
#define BUFFER_SIZE 32 // message buffer size
#define BACKLOG 5 //Number of socket connection aviable in listen

#define CLOSE_SOCKET_IF_NULL(s) if (s!=NULL)close(s);s=NULL;

int socket_tcp; // tcp_socket name
int new_socket;//name of incomming socket
int receive; // receive value
int sending; //sending value
int addrlen; // length of an adress
int on = 1;//setcokopt option_value argument
char ip_buffer[IP_BUFFER_LENGTH];//buffer for ip
char reciv_data[BUFFER_SIZE]; // buffer for message length
int pid;/*process id*/
double parrent_pid;

int optval;
socklen_t optlen = sizeof(optval);


struct sockaddr_in client; 
struct sockaddr_in server;

int temp;//variable for parsing from string to int 


/*Function to get hosts IP information*/
int host_setup(){

  struct hostent * Host ;
  gethostname(ip_buffer , IP_BUFFER_LENGTH);
  printf("%s\n", ip_buffer);
  Host = ( struct hostent * )gethostbyname(ip_buffer);
  printf("Host name : %s\n", Host->h_name) ;
  printf("Host IP Address : %s\n", inet_ntoa(*((struct in_addr *)Host->h_addr)));

  return 0; 

}

int socket_create(){

 if(( socket_tcp = socket(AF_INET,SOCK_STREAM,0))==-1){
    perror("create()");
    exit(EXIT_FAILURE);
  }
  else{
    printf("Created tcp socket\n");
  }

 return 0;

}

int socket_reusing(){

 if (setsockopt(socket_tcp, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0){
      perror("setsockopt()");
      exit(EXIT_FAILURE);
    }
  else{
    printf("Reusing socket\n");
  }
 
 return 0;

}

int socket_keep_alive(){

  if(getsockopt(socket_tcp, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
      perror("getsockopt()");
      close(socket_tcp);
      exit(EXIT_FAILURE);
   }
  else{
   printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));
  }


  return 0;

}

int socket_binding(){

  server.sin_family = AF_INET; //allways afinet if its tcp
  server.sin_port = htons(PORT); //host to network short 
  server.sin_addr.s_addr = INADDR_ANY; //assigning mine ip adess

 if((bind(socket_tcp, (struct sockaddr *)&server, sizeof(struct sockaddr)))==-1){  
    perror("bind()");
    exit(EXIT_FAILURE);
  }
  else{
    printf("Binding server socket\n");
  }

 return 0;
}

int socket_listening(){

 if((listen(socket_tcp, BACKLOG))<0){
    perror("listen()");
    exit(EXIT_FAILURE);
  }
  else{
    printf("Listening for connections\n");
  }

  return 0;
}



int data_passing(){
  
  while(1){
    
        if(( new_socket = accept(socket_tcp, (struct sockaddr *)&client, &addrlen))<0){
      perror("accept()");
      exit(EXIT_FAILURE);
    }
    else{ 
      printf("Client IP is %s and port is : %d \n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    }
    
  
    pid = fork();

    
    if (pid < 0){
      
      perror("pid()");
      exit(1);
    }


    printf("Parent ..... %d\n",getpid());
   
    
    if(pid==0){
      printf("child---------%d\n",getpid());
      close(socket_tcp);
      message(new_socket,parrent_pid);
     

      close(new_socket);
      exit(0);   
    }
    else{
      close(new_socket);
    }
    }

  close(socket_tcp);
  return 0;
  
}



void message(int new_socket,double parrent_pid){
  
  while(1){
   receive = recv(new_socket,reciv_data,BUFFER_SIZE,0);
    
    reciv_data[receive]= '\0';
    
    if (strcmp(reciv_data,"quit")==0){
       CLOSE_SOCKET_IF_NULL(new_socket);
      printf("Closing client\n");
      break;	   
    }
    else if (strcmp(reciv_data,"shut_server")==0){
      printf("%d\n",parrent_pid);
      printf("Shutting server\n");
      kill(parrent_pid,SIGTERM);
      
    }
    
    else{
      printf("%s\n", reciv_data); 
      temp = atoi(reciv_data);
      controll_movement(temp);
    }
 }
 
 
}
