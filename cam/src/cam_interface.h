/**
  * Module: cam_interface.h
  *
  * Author (s): Ikuh Henry
  * Created: 2011-05-08
  * Version: 0.01
  * Description: main interface for scheduler to run the program
*/




//#include "cv.h"
#include "highgui.h"
#include <pthread.h>
#include <stdint.h>

/*	program header files */

int16_t cam_init(void);

int16_t cam_run(void);

