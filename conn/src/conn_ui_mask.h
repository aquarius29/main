/*!
 *  @file conn_mask_ui.h
 *
 *  @brief tcpclient file
 *
 *  @author Michal Musialik
 *  @date 2011-05-07
 *  @history    2011-05-07 - adding new values for macros
 *  @history    2011-04-13 - uppdating to new standard
 *  
 */
#define FORWARD 3
#define BACK 4 
#define LEFT 5 
#define RIGHT 6 
#define UP 7 
#define DOWN 8 
#define LAND 9 
#define TAKE_OFF 10 
#define KILL_INDOOR 11 
#define KILL_GPS 12
#define KILL_SERVER 13 
#define START_CAMERA 14
#define START_INDOOR_PATH 30
#define START_OUTDOOR_PATH 31
#define INDOOR_POSITION 20
#define OUTDOOR_POSITION 21
#define DEBUG(x) printf("%s",x);

void controll_movement(int status);
