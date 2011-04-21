#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

/*Author Ali issa*/
/* the port users will be connecting to */
#define PORT 9600
/* how many pending connections queue will hold */
#define BACKLOG 10
#define MAXLEN 300

/*variables*/
int soc, recbytes, integer;
char buf[MAXLEN];
struct hostent *he;
struct sockaddr_in their_addr; // will point to the results

int createSocket(void) {
    /*creating socket*/
    if ((soc = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("failed to create a socket\n");
        return -1;
        exit(1);
    } else {
        he = gethostbyname("192.168.1.2");
        printf("socket is succesfully created\n");
        their_addr.sin_family = AF_INET;
        their_addr.sin_port = htons(PORT); //my port here
        their_addr.sin_addr = *((struct in_addr *) he->h_addr);
        memset(&(their_addr.sin_zero), '\0', 8);
        return 2;
    }
}

int connectSocket() {
    /*connection and check*/
    if (connect(soc, (struct sockaddr *) &their_addr, sizeof (struct sockaddr)) == -1) {
        perror("connect()");
        return -1;
        exit(1);
    } else
        printf("Client is connected to server\n");
    return 2;
}

int sendMessage() {
    if (send(soc, "Some message from UI group\n", 22, 0) == -1) {
        printf("unable to send message\n");
        return -1;
    } else {
        printf("message was succesfully sent\n");
        return 2;
    }
}

int receive() {
    if ((recbytes = recv(soc, buf, MAXLEN - 1, 0)) == -1) {
        perror("rescv()");
        return -1;
        exit(1);
    } else
        printf("client has recieved from host\n");
    buf[recbytes] = '\0';
    /*receiving message from the server*/
    printf("client- recieved: %s", buf);
    return 2;
    close(soc);
}

