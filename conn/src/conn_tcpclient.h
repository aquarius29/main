/**
 * Module:       conn_tcpclient.h
 * Author(s):    Michal Musialik
 *
 * Description:  Prototype function used conn_tcpclient.c. 
 *
 */


int socket_host(char *argv[]);
int socket_create(void);
int socket_binding(void);
int socket_connection(char *argv[]);
int data_passing(void);
