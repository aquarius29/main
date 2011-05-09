/*!
 *  @file conn_tcpclient.h
 *
 *  @brief Header file for conn_tcpclient.c
 *
 *  @author Michal Musialik
 *  @date 2011-05-07
 *  @history    2011-05-07 - first outcast of conn_tcpclient.h file
 */
#define PORT 9600 
#define BUFFER_SIZE 20 
#define GO_FORWARD "3"
#define STOP_FORWARD "4"
#define GO_BACK "5"
#define STOP_BACK "6"
#define GO_LEFT "7"
#define STOP_LEFT "8"
#define GO_RIGHT "9"
#define STOP_RIGHT "10"
#define GO_UP "11"
#define STOP_UP "12"
#define GO_DOWN "13"
#define STOP_DOWN "14"
#define HOVER "15"
#define LAND "16"
#define AUTO "17"
#define QUIT "quit"
#define GPS "19"
#define SERVER_SHUT "shut_server"

struct sockaddr_in connecting; 
struct hostent * host; 

int socket_create(void);
int socket_binding(void);
int socket_connection(void);
void send_foward (void);
void send_back (void);
void send_left (void);
void send_right (void);
void send_exit(void);
void send_auto(void);
void send_hover(void);
void send_landing(void);
void send_alt_up(void);
void send_alt_down(void);
void send_camera(void);
void send_gps(void);
void send_server(void);
