/*! 
    @file conn_tcpclient.c
    @author Michal Musialik 
*/
/*
This file is a slave socket that allows the user to create a remote 
connection to a master socket and allow to transfer varions command 
through wifi.
*/


#define PORT 9600 /*IP port adress*/
#define BUFFER_SIZE 32 /*Buffer size of messages*/

int socket_tcp; /*Tcp socket name*/
char send_data[BUFFER_SIZE];/*Send data*/
char data_receive[BUFFER_SIZE];/*Recived data*/

int byte;/*Byte of message*/

struct sockaddr_in connecting; /*Struct for socket adress*/
struct hostent * Host; /*Struct for Ip adress*/



/*Master sockets adress*/
int conn_socket_host(char *argv[]){

  /*Checking Master sockets IP */
  if((Host = gethostbyname(argv[1]))==NULL)
    {
      perror("gethostbyname()");
      exit(EXIT_FAILURE); 
    }
  
  else{
    printf("Remote host is %s\n",argv[1]);
  }
  
  return 0; 
  
}

/*Creating socket*/
int conn_socket_create(void){

 if((socket_tcp = socket(AF_INET, SOCK_STREAM,0))==-1){
     printf("socket()");
     exit(EXIT_FAILURE);
   }
 else{
     printf("Socket is succesfully created\n");
   
   }
 return 0;
}

/*Binding socket*/
int conn_socket_binding(void){

 connecting.sin_family = AF_INET;
 connecting.sin_port = htons(PORT);
 connecting.sin_addr= *((struct in_addr *)Host->h_addr);
 memset(&(connecting.sin_zero),'\0',8);/*Zerong the rest of the structure*/

 return 0;
}

/*Connection to a host*/
int conn_socket_connection(char *argv[]){


 if(connect(socket_tcp,(struct sockaddr *)&connecting,sizeof(struct sockaddr))==-1)
  {
    perror("connect()");
    exit(1);
  }
 else{
   printf("Client is connected to%s\n",argv[1]);
 }

 return 0;
}


/*Data transfer*/
 int conn_data_passing(void){

 while(1){

   printf("Message input: ");
   scanf("%s", send_data);
   /*Sending packeges of data as strings*/
   if(strcmp(send_data,"quit")!=0){
       send(socket_tcp,send_data,strlen(send_data),0);
   }
   else{
   /*Quiting both client and server with quit*/
     send(socket_tcp,send_data,strlen(send_data),0);
     printf("Closing client \n");
     close(socket_tcp);    
     break;
   }
   /*Receiving a response from master socket*/
   byte = recv(socket_tcp,data_receive,BUFFER_SIZE,0);
   data_receive[byte]= '\0';
   printf("Received %s\n", data_receive);

 }
 return 0;
}
