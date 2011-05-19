/*!
 *  @file conn_frame.h
 *
 *  @brief This is a header file that contain prtotype used frame.c
 *  @author Michal Musialik
 *
 *  @date 2011-05-07
 *  @history    2011-05-11 - adding final prototypes\n
 *              2011-05-16 - linking
 *
 *  @ref http://www.gtk.org 
 */



#include <gtk/gtk.h>
#define TEXT_SIZE 50
#define DEBUG(x) printf("%s",x);
#define MENU_X_CORD 330

void window_creation(void);
void destroy_command(void);
void info_frame(void);
void button_exit(void);
void button_back_controll(void);
void button_left_controll(void);
void button_right_controll(void);
void button_forward_controll(void);
void button_altitide_up(void);
void button_altitide_down(void);
void button_camera_controll(void);
void button_landing_command(void);
void button_hover_command(void);
void button_gps_outdoor_command(void);
void button_kill_gps_outdoor(void);
void button_gps_indoor_command(void); 
void button_kill_gps_indoor(void);
void button_server_command(void);
void button_connect_to_server(void);
void  button_indoor_position(void);
void  button_outdoor_position(void);
void back_controll(void);
void left_controll(void);
void left_controll(void);
void right_controll(void);
void forward_controll(void);
void alt_up(void);
void alt_down(void);
void camera_connect(void);
void hover(void);
void gps_outdoor(void);
void gps_kill_outdoor(void);
void gps_indoor(void);
void gps_kill_indoor(void);
void kill_server(void);
void command_quit(void);
void indoor_position(char* text);
void outdoor_position(char* text);
void landing(void);
void drone_connect(void);
void enter_callback(GtkWidget *widget, GtkWidget *entry );
void frame_text_label(void);
