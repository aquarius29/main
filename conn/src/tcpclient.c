
/*Author Michal Musialik*/

#define PORT 9600 // port macro
#define BUFFER_SIZE 32 // message buffer size

int socket_tcp; // tcp_socket name
char send_data[BUFFER_SIZE];

struct sockaddr_in connecting; 
struct hostent * Host; //Host adress




int socket_host(char *argv[]){

if((Host = gethostbyname(argv[1]))==NULL)
  {
  perror("Cant get host name\n");
  exit(EXIT_FAILURE); 
 }

  else{
  printf("client-the remote host is %s\n",argv[1]);
 }

return 0; 

}

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

 connecting.sin_family = AF_INET;
 connecting.sin_port = htons(PORT); //my port here
 connecting.sin_addr= *((struct in_addr *)Host->h_addr);
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


 int data_passing(){

 while(1){

   printf("Message input: ");
   scanf("%s", send_data);
   
   if(strcmp(send_data,"quit")!=0){
       send(socket_tcp,send_data,strlen(send_data),0);
   }
   else{
     send(socket_tcp,send_data,strlen(send_data),0);
     printf("Closing client \n");
     close(socket_tcp);    
     break;
   }

 }
 return 0;
}
