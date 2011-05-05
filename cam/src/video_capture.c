
/*---------------------------------------------------------------------------------------------------------------------------------------------
* VIDEO CAPTURE
* Henry Ikuh - Colaborator ( Abdirashid Jama)

* The program captures both video file and webcam using opencv computer vision library in c.
* file name: video_capture.c
 
* Prerequisite:
**	Install: ffmpeg
**	OpenCV
**	v4l2 (comes with your linux distribution)
 
* To compile: gcc `pkg-config --cflags opencv` `pkg-config --libs opencv` -lpthread video_capture.c -o video_capture
* To run: ./video_capture 
* To capture a saved video file: ./video_capture filename.extention
 
*---------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Opencv library API
#include "cv.h"
#include "highgui.h"


// Variable declaration
IplImage*	cam_video;
IplImage*	file_video;
CvCapture*	capture;
//CvCapture*	capture_compress;
int	is_data_ready = 0;


// Function Prototypes
void  exit_now(char* msg, int retval);


// main function
int main(int argc, char** argv)
{
	pthread_t 	thread_s;
	int	key;
	

	if (argc == 2) {
		capture = cvCaptureFromFile(argv[1]);
	} else {
		capture = cvCaptureFromCAM(0);
	}

	if (!capture) {
		exit_now("\nNo Webcam connected or no video file. Check and complete the arguments", 1);
	}
/*---------------------------------------------------------------------------------------------------------------------------------------------
 video compression here???????????
 I plan to have a compression function called here or be in a loop, so that when a stream of video is captured by the opencv
 its compressed from its original webcam video format (Motion JPEG) to another codec like x.264, H.264, Vp8 or others.
 then the cvQueryFrame funtion takes the compressed video stream as argument say "capture_compressed" instead of "capture"
 which will then stream the video to the gui, this way the current problem of : session timeout, Corrupt JPEG data: . as a result of the video
 stream from the usb webcamera. At least this is what i understand for now.
 
 If we can do a video compression supported in opencv or ffmpeg, then good. or we can use the ffmpeg server to do this.
*---------------------------------------------------------------------------------------------------------------------------------------------*/
	cam_video = cvQueryFrame(capture);
	file_video = cvCreateImage(cvGetSize(cam_video), IPL_DEPTH_8U, 3);
	cvZero(file_video);
	cvNamedWindow("VIDEO SERVER", CV_WINDOW_AUTOSIZE);


/* print to the stdout the frame size for client to use as run parameter */
	fprintf(stdout, "Video Frame Width:  %d\nVideo Frame Height: %d\n\n", cam_video->width, cam_video->height);
	fprintf(stdout, "Press 'Ctrl+C' to quit streaming.\n\n");

	
/*---------------------------------------------------------------------------------------------------------------------------------------------
 Here is a loop to continuesly display the video to highgui interface as long as we 
 don't exit the streaming and while the lenght of the file_video is not == 0 (end of lenght) 
*---------------------------------------------------------------------------------------------------------------------------------------------*/
	while(key!='c') {
		/* get video stream from camera */
		cam_video = cvQueryFrame(capture);
		if (!cam_video) break;
		
		cam_video->origin = 0;
	
		/* display the video here on HIGHGUI */
		cvShowImage("VIDEO SERVER", cam_video);
		key = cvWaitKey(8); 
		/* cvWaitKey value determine how long it waits between each frame to be stiched to the other. so higher value makes it slower. */
		//cvReleaseImage(&file_video);
		//cvReleaseImage(&cam_video);

	}
/*---------------------------------------------------------------------------------------------------------------------------------------------
 ? while video playing : save convert and save video as byte stream (grid of numbers) to an array, emm will this work? 
 The video stream is made up of grid of numbers
*---------------------------------------------------------------------------------------------------------------------------------------------*/

	/* free memory */
	cvDestroyWindow("VIDEO SERVER");
	exit_now(NULL, 0);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------
 this function provides a way to exit_now safely from the system
*---------------------------------------------------------------------------------------------------------------------------------------------*/
void exit_now(char* msg, int retval)
{
 	if (retval == 0) {
    if (msg) {
      fprintf(stdout, "%s\n", msg);
      fprintf(stdout, "\n");
    }
  } 
  else {
    if (msg) {
      fprintf(stderr, "%s\n", msg);
      fprintf(stderr, "\n");
    }
  }
  
	exit(retval);
}

