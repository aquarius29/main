/* ONLY TO BE USED FOR THE GROUPP TO RUN PROGRAM TEST*/


#include "cv.h"
#include "highgui.h"
#include "cam_interface.h"
#include "cam.h"
#include <stdio.h>


int main(void)
{
  
 	initialize();
	grab_frame();
	save_and_convert_video();
	video_server();
 return 0;
  
 
}
