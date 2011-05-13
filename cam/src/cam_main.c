/**
  * Module: cam_main.c
  *
  * Author (s): Ikuh Henry
  * Created: 2011-04-27
  * Version: 0.01
  * history: 2011-04-27 - created the initial file
			 2011-05-08 - re structure source code

  * Description: Contains the init and run functions of the camera
*/



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "cv.h"
#include "highgui.h"
#include <stdint.h>
#include "cam_interface.h"
#include "cam_cam.h"

int16_t cam_init(void)
{
    initialize(void);// init cam
    return 0;

}

int16_t cam_run(void)
{
    grab_frame();	
    convert_and_send_video();
    video_server();

    return 0;
}
