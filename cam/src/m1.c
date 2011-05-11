/* ONLY TO BE USED FOR THE GROUPE TO RUN PROGRAM TEST*/


#include "cv.h"
#include "highgui.h"
#include "cam_interface.h"
#include "cam_cam.h"
#include <stdio.h>


int main(void)
{
  
 	initialize();
	grab_frame();
	save_and_convert_video();
	video_server();
 return 0;
  
 
}
