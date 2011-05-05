/**
 * Module:       conn_tcpserver.h
 * Author(s):    Michal Musialik
 *
 * Description:  Prototype functions used in 
 *               conn_tcpserver.c
 *
 */

void host_setup(void);
int socket_create(void);
int socket_reusing(void);
int socket_bind(void);
int socket_listening(void);
int new_socket_creation(void);
void data_passing(void);
