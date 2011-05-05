/*! 
    @file tcpserver.c
    @author Michal Musialik 
*/
/*
We crating a master socket that allow being connected by slave sockets and 
allow to send messages as strings through wifi.
*/

#define IP_BUFFER_LENGTH 200 /*Buffer for IP adress*/
#define PORT 9600 /*IP port adress*/
#define BUFFER_SIZE 32 /*Buffer size of messages*/
#define BACKLOG 3 //Number of connection pending

int socket_tcp; /*tcp socket name*/
int new_socket;/*Name of the oncomming socket connection*/
int byte; /*Byte of message*/
int addrlen; /*Length of an adress*/
int on = 1;/*setcokopt option_value argument*/
char ip_buffer[IP_BUFFER_LENGTH];/*Host ip */
char reciv_data[BUFFER_SIZE]; /*Recived data*/

struct sockaddr_in client;/*Struct for socket adress*/
struct sockaddr_in server;/*Struct for socket adress*/


/*Function to get hosts IP information*/
void conn_host_setup(void){

  struct hostent * Host ;
  gethostname(ip_buffer , IP_BUFFER_LENGTH);
  Host = ( struct hostent * )gethostbyname(ip_buffer);
#ifdef DEBUG
  printf("Host name : %s\n", Host->h_name) ;
  printf("Host IP Address : %s\n", inet_ntoa(*((struct in_addr *)Host->h_addr)));
#endif
}


/*Creating socket*/

int conn_socket_create(void){

 if(( socket_tcp = socket(AF_INET,SOCK_STREAM,0))==-1){
#ifdef DEBUG
    perror("create()");
#elif defined TEST
        return 1; /* error */
#endif
    exit(EXIT_FAILURE);
  }
  else{
#ifdef TEST
        return 0; /* success */
#elif defined DEBUG
    printf("Created tcp socket\n");
#endif
  }

 return 0;

}

/*Reusing ceated socket*/
int conn_socket_reusing(void){

 if (setsockopt(socket_tcp, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0){
#ifdef DEBUG     
   perror("setsockopt()");
#endif
      exit(EXIT_FAILURE);
    }
  else{
#ifdef DEBUG
    printf("Reusing socket\n");
#endif
  }
 
 return 0;

}

/*Binding socket to an adress*/
int conn_socket_bind(void){

  server.sin_family = AF_INET; 
  server.sin_port = htons(PORT); 
  server.sin_addr.s_addr = INADDR_ANY;
    
if((bind(socket_tcp, (struct sockaddr *)&server, sizeof(struct sockaddr)))==-1){
#ifdef DEBUG 
   perror("bind()");
#elif defined TEST
        return 1; /* error */
    #endif
    exit(EXIT_FAILURE);
  }
  else{
  	#ifdef TEST
        return 0; /* success */
    #elif defined DEBUG
    printf("Binding server socket\n");
#endif 
 }

 return 0;
}

/*Listening for incomming connections*/
int conn_socket_listening(void){

 if((listen(socket_tcp, BACKLOG))<0){
#ifdef DEBUG
    perror("listen()");
    #elif defined TEST
        return 1; /* error */
    #endif
    exit(EXIT_FAILURE);
  }
  else{
	#ifdef TEST
        return 0; /* success */
    #elif defined DEBUG

    printf("Listening for connections\n");
#endif 
 }

  return 0;
}


/*Creating now socket*/
int conn_new_socket_creation(void){

 if(( new_socket = accept(socket_tcp, (struct sockaddr *)&client, &addrlen))==-1){
#ifdef DEBUG  
 perror("accept()");
    #elif defined TEST
        return 1; /* error */
    #endif
    exit(EXIT_FAILURE);
  }
  else{ 
  	#ifdef TEST
        return 0; /* success */
    #elif defined DEBUG
    printf("Client IP is %s and port is : %d \n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
#endif 
 }


  return 0;
}


/*Data exchage betwen other socket*/
void conn_data_passing(void){
 
 
  while(1){
    
    byte = recv(new_socket,reciv_data,BUFFER_SIZE,0);
    reciv_data[byte]= '\0';
    
    /*Closing master socket on quit command*/
    if (strcmp(reciv_data,"quit")==0){
      close(new_socket);
#ifdef DEBUG    
  printf("Closing server\n");
#endif
      break;	   
    } 
    else{
      /*Sending data back to the slave socket*/
     printf("%s\n", reciv_data); 
      send(new_socket,reciv_data,strlen(reciv_data),0);


    }
  }
      close(socket_tcp);
   
}

   
