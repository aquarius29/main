/*!
 *  @file conn_tcpclient.h
 *
 *  @brief Header file for conn_tcpclient.c
 *
 *  @author Michal Musialik
 *  @date 2011-05-07
 *  @history    2011-05-07 - first outcast of conn_tcpclient.h file
 *  @history    2011-05-13 - restructuring
 */

#define GPS_BUFFER 50
#define PORT 9600 
#define BUFFER_SIZE 20 
#define CLOSE_SOCKET_TCP close(socket_tcp)

#define FORWARD "3"
#define BACK "4" 
#define LEFT "5" 
#define RIGHT "6" 
#define UP "7" 
#define DOWN "8" 
#define LAND "9" 
#define TAKE_OFF "10" 
#define KILL_INDOOR "11" 
#define KILL_GPS "12"
#define KILL_SERVER "13" 
#define START_CAMERA "14"
#define START_INDOOR_PATH "30"
#define START_OUTDOOR_PATH "31"
#define INDOOR_POSITION "20"
#define OUTDOOR_POSITION "21"
#define QUIT "quit"
#define SERVER_SHUT "shut_server"
#define DEBUG(x) printf("%s",x);

int socket_create(void);
int socket_binding(void);
int socket_connection(void);
void send_forward (void);
void send_back (void);
void send_left (void);
void send_right (void);
void send_exit(void);
void send_hover(void);
void send_landing(void);
void send_alt_up(void);
void send_alt_down(void);
void send_camera(void);
void send_kill_server(void);
void send_gps_outdoor(void);
void send_kill_outdoor(void);
void send_indoor(void);
void send_kill_indoor(void);
void send_indoor_position(void);
void send_outdoor_position(void);
void recieving(void);
