/*!
 *  @file conn_tcpserver.c
 *
 *  @brief Header file for tcpserver
 *
 *  @author Michal Musialik
 *  @date 2011-03-20
 *  @history    2011-03-23 - first outcast of conn_tcpserver.c file
 *  @history    2011-04-04 - adding data transfer functions
 *  @history    2011-04-06 - restructuring conn_tcpserver.c 
 *  @history    2011-04-13 - midyfing data transfering  
 *  @history    2011-04-21 - implying data handling function
 *  @history    2011-04-22 - adding socket options
 *  @history    2011-04-30 - adding keepalive option
 */



int socket_tcp; 
int new_socket;
int receive; 
int sending; 
int address_length; 
int reusing_value = 1;
char ip_buffer[IP_BUFFER_LENGTH];
char receive_data[BUFFER_SIZE]; 
int pid;
int parrent_pid;

int keepalive_value;
socklen_t keepalive_length = sizeof(keepalive_value);


int atio_temp;/*variable for parsing from string to int*/ 


/*Function to get hosts IP information*/
void host_setup(void){
  gethostname(ip_buffer , IP_BUFFER_LENGTH);
  printf("%s\n", ip_buffer);
  host = ( struct hostent * )gethostbyname(ip_buffer);
  printf("Host name : %s\n", host->h_name) ;
  printf("Host IP Address : %s\n", inet_ntoa(*((struct in_addr *)host->h_addr)));
}

/*Function for socket creation*/
int socket_create(void){
 if(( socket_tcp = socket(AF_INET,SOCK_STREAM,0))==-1){
    perror("create()");
    exit(EXIT_FAILURE);
  }
  else{
    printf("Created tcp socket\n");
  }
 return 0;
}

/*Function for socket reusage*/
int socket_reusing(void){
 if (setsockopt(socket_tcp, SOL_SOCKET, SO_REUSEADDR, &reusing_value, sizeof(reusing_value)) < 0){
      perror("setsockopt()");
      exit(EXIT_FAILURE);
    }
  else{
    printf("Reusing socket\n");
  }
 return 0;
}

/*Function for keeping socket alive*/
int socket_keep_alive(void){

  if(getsockopt(socket_tcp, SOL_SOCKET, SO_KEEPALIVE, &keepalive_value, &keepalive_length) < 0) {
      perror("getsockopt()");
      close(socket_tcp);
      exit(EXIT_FAILURE);
   }
  else{
   printf("Socket is keept %s\n", (keepalive_value ? "alive." : "dead."));
  }
  return 0;
}

/*Function for binding socket*/
int socket_binding(void){
  server.sin_family = AF_INET; 
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;
 if((bind(socket_tcp, (struct sockaddr *)&server, sizeof(struct sockaddr)))==-1){  
    perror("bind()");
    exit(EXIT_FAILURE);
  }
  else{
    printf("Binding server socket\n");
  }
 return 0;
}

/*Function for listening*/
int socket_listening(void){
 if((listen(socket_tcp, MAX_NR_OF_CONNECTIONS))<0){
    perror("listen()");
    exit(EXIT_FAILURE);
  }
  else{
    printf("Listening for connections\n");
  }
  return 0;
}

/*Function for accepting incomming sockets*/
int socket_accept(void){
  if(( new_socket = accept(socket_tcp, (struct sockaddr *)&client, &address_length))<0){
    perror("accept()");
    exit(EXIT_FAILURE);
  }
  else{ 
    printf("Client IP is %s and port is : %d \n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
  }
     return 0;
}


/*Function that handles data passing*/
int data_passing(void){
  /*Main while loop*/ 
  while(1){
    socket_accept();
  
    /*forking*/
    pid = fork();

    if (pid < 0){      
      perror("pid()");
      exit(1);
    }
    printf("Parent ..... %d\n",getpid());
    if(pid==0){
      printf("child---------%d\n",getpid());
      CLOSE_SOCKET_TCP;
      message_handling(new_socket,parrent_pid);
      CLOSE_NEW_SOCKET;
      exit(0);   
    }
    else{
      CLOSE_NEW_SOCKET;
    }
  }
  CLOSE_SOCKET_TCP;
  return 0;
}


/*Function for handling all data trafic*/
void message_handling(int new_socket,int parrent_pid){
  while(1){
   receive = recv(new_socket,receive_data,BUFFER_SIZE,0);
   receive_data[receive]= '\0';
   /*closing client socket*/
   if (strcmp(receive_data,"quit")==0){
     CLOSE_NEW_SOCKET;
     printf("Closing client\n");
     break;	   
   }
   /*closing server socket*/
   else if (strcmp(receive_data,"shut_server")==0){
     printf("%i\n",parrent_pid);
     printf("Shutting server\n");
     kill(parrent_pid,SIGTERM);
   }
   else{
     /*reading incomming data and sending to controll_movement*/
     printf("%s\n", receive_data); 
     atio_temp = atoi(receive_data);
     controll_movement(atio_temp);
   }
 }
}
