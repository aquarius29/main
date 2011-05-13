/* ONLY TO BE USED FOR THE GROUPP TO RUN PROGRAM TEST*/


#include "cv.h"
#include "highgui.h"
#include "cam_interface.h"
#include "cam_cam.h"
#include <stdio.h>

#include "cam_server.c"
#include "cam_video_capture.c"


int main(void)
{
  
    initialize();
    grab_frame();
    convert_and_send_video();
    video_server();

return 0;
  
 
}
