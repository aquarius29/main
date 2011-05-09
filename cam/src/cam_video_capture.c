/***********************************************************************************************
 * Library: OpenCV
 * Version: 2.1.0
 * = What is OpenCV?
 *
 * OpenCV is "Open Source Computer Vision Library".
 * OpenCV is developed by Intel and many opensource developers.
 * The library include many useful function for computer vision, such as object-detection.
 *
 * OpenCV is developed at
 * sourceforge.net[http://sourceforge.net/projects/opencvlibrary]
 * 
 ** =How to install
***********************************************************************************************/

/**
  * Module: cam_video_capture.c
  *
  * Author (s): Ikuh Henry, Abdirashid Jama
  * Created: 2011-04-20
  * Version: 0.02
  * history: 2011-04-10 - created the initial file
			 2011-04-20 - grabing frames
			 2011-04-28 - compress, convert and send
			 2011-05-06 - re structure source code

  * Description: Contains the functions that captures video from the web cam 
  				 and convert video frames for streaming 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "cv.h"
#include "highgui.h"

#include "cam_interface.h"
#include "cam.h"

/*
	video capture structure for opencv and the IplImage structure
*/
	CvCapture* video_capture;
	IplImage* video_frame; // uncompressed array of BGR images
	IplImage *gray_frame; // to hold the processed images
	

/*
	Function Prototypes
*/
	void initialize(void);
	void grab_frame(void);
	void save_and_convert_video(void);



/*
	Variables
*/
	int new_data;
	int key;
	//int cam_index = 1;
	pthread_mutex_t	 mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_t 	thread_new;

/*
	Function that initializes the camera
*/
	
void initialize(void)
{
	//if(cam_index){
	video_capture = cvCaptureFromCAM(1);
	//}
		if(!video_capture){
		perror("could not capture from device");
		}
	printf("Initializing ...\n");

}

/*
	Function that grabs the captured frames 
*/
void grab_frame(void)
{

	video_frame = cvQueryFrame(video_capture);

	fprintf(stdout, "Frame Width: %d\n", video_frame -> width);
	fprintf(stdout, "Frame Height: %d\n\n", video_frame -> height);
	printf("******************************\n");
	fprintf(stdout, "Press Ctrl+C to stop streaming\n");

	//return 0;
}

/*
	Function that saves a compressed mpeg4 video stream to file
*/
void save_and_convert_video(void)
{
	CvSize size = cvSize((int)cvGetCaptureProperty(video_capture,CV_CAP_PROP_FRAME_WIDTH),
						(int)cvGetCaptureProperty(video_capture,CV_CAP_PROP_FRAME_WIDTH));
	CvVideoWriter *writer = cvCreateVideoWriter("out.avi", CV_FOURCC('D','I','V','X'), 25,size, 1);

/*	create a variable to hold processed frames*/
	gray_frame = cvCreateImage(cvGetSize(video_frame),IPL_DEPTH_8U, 1);

	//pthread_create(&thread_new, NULL, video_server, NULL);// to the server


/*	video processing loop */	
	cvNamedWindow("QUADROTOR-SERVER",CV_WINDOW_AUTOSIZE); 
	while(video_frame > 0){
	video_frame = cvQueryFrame(video_capture);
	cvWriteFrame(writer, video_frame);

		if(!video_frame)
		break;
		video_frame -> origin = 0;

	pthread_mutex_lock(&mutex);
	cvCvtColor(video_frame, gray_frame, CV_BGR2GRAY);// we can as well do the compression here
	new_data = 1;
	pthread_mutex_unlock(&mutex);

/*	show video */
	cvShowImage("QUADROTOR-SERVER", video_frame);
	key = cvWaitKey(28);
	}


/*
	clen up memory after use
*/
	cvDestroyWindow("QUADROTOR-SERVER");
	cvReleaseVideoWriter(&writer);
	cvReleaseImage(&gray_frame);
	cvReleaseCapture(&video_capture);
	pthread_mutex_destroy(&mutex);

}
