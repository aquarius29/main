
/**
  * Module: cam_cam.h
  *
  * Author (s): Ikuh Henry
  * Created: 2011-05-08
  * Version: 0.01
  * Description: header file
*/


#include <stdio.h>

/*	header file - all other function prototypes that will be use in the group 
	for file to files.
*/


void initialize();

void grab_frame(void);

void convert_and_send_video(void);

void video_server(void);

void terminate(char*msg, int ret_value);


