#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

/*Ali & Kuhan & Michal*/

#define IP_BUFFER_LENGTH 200
#define PORT 9600 // port macro
#define BUFFER_SIZE 1024 // message buffer size
#define BACKLOG 5 //Number of socket connection aviable in listen

struct sockaddr_in sin2;



int socket_bind; //bound socket value
int sending; //sending value
int receive; // receive value
int addrlen; // length of an adress
int new_socket; //number of ip adress
int socket_tcp; // tcp_socket name
char ip_buffer[200]; //buffer for ip

int gatherInfo() {
    struct hostent * Host;
    gethostname(ip_buffer, IP_BUFFER_LENGTH);
    printf("%s\n", ip_buffer);
    Host = (struct hostent *) gethostbyname(ip_buffer);
    printf("Host name : %s\n", Host->h_name);
    printf("Host IP Address : %s\n", inet_ntoa(*((struct in_addr
            *) Host->h_addr)));
}

int createSocket() {
    socket_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_tcp == -1) {
        perror("Create socket \n");
    } else {
        printf("Created tcp socket\n");
    }
    sin2.sin_family = AF_INET; //allways afinet if its tcp
    sin2.sin_port = htons(PORT); //host to network short
    sin2.sin_addr.s_addr = INADDR_ANY; //assigning mine ip adess
}

int socketBind() {
    socket_bind = bind(socket_tcp, (struct sockaddr *) &sin2, sizeof (struct
            sockaddr));
    if (socket_bind < 0) {
        return 1;
        perror("Cannot bind socket\n");
        exit(EXIT_FAILURE);
    } else {
        return 2;
        printf("binding server socket\n");
    }
}

int listenSocket(){
    listen(socket_tcp, BACKLOG);
}

int newSocket() {
    addrlen = sizeof (struct sockaddr);
    new_socket = accept(socket_tcp, (struct sockaddr *) &sin2, &addrlen);
    if (new_socket < 0) {
        perror("accepting socket error");
        exit(EXIT_FAILURE);
    } else {
        printf("Welcome to ser mrs ALI\n");
        printf("new socket with adress %d\n", new_socket);
    }
}

int acceptSocket() {
    char *buffer = malloc(BUFFER_SIZE);
    receive = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
    if (receive < 0) {
        printf("Cannot receive massage");
        exit(EXIT_FAILURE);
    } else {
        buffer[BUFFER_SIZE] = '\0';
        printf("%s\n", buffer);
        free(buffer);
    }
}

int write() {
    char welcome_message [BUFFER_SIZE] = "Welcome to the jungle!!!";
    sending = send(new_socket, welcome_message, sizeof (welcome_message), 0);
    if (sending < 0) {
        perror("Cant send Welcome message\n");
        exit(EXIT_FAILURE);
    } else {
        printf("data send %s\n", welcome_message);
        printf("buffer size send %i\n", sizeof (welcome_message));
    }
}

int closeSocket() {
    close(new_socket);
    close(socket_tcp);
    exit(EXIT_SUCCESS);
}

