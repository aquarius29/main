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
			 2011-05-13 - changed the video saving. to reduce larging

  * Description: Contains the functions that captures video from the web cam 
  				 and convert video frames for streaming 
**********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "cv.h"
#include "highgui.h"

#include "cam_interface.h"
#include "cam_cam.h"

/*
	video capture structure for opencv and the IplImage structure / global variable
*/
    CvCapture* video_capture;
    IplImage* video_frame; // uncompressed array of BGR images
    IplImage *gray_frame; // to hold the processed images
    int new_data;
    int key;

/*
	Function Prototypes
*/
    void initialize();
    void grab_frame(void);
    void convert_and_send_video(void);


/*
	declare threads to be used
*/
    pthread_mutex_t	 mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_t 	server_thread;

/*
	Function that initializes the camera
*/
	
void initialize()
{
<<<<<<< HEAD
	//if(cam_index){
	video_capture = cvCaptureFromCAM(0);
	//}
		if(!video_capture){
		perror("could not capture from device");
		}
	printf("Initializing ...\n");
=======
>>>>>>> b64f14e505c1a54f5e93aefebe0751ca42cc01fe

    video_capture = cvCaptureFromCAM(0);

        if(!video_capture){
        perror("could not capture from device");
        }
    else{
    printf("Initializing ...\n");
    }
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

}

/*
	Function that saves a compressed mpeg4 video stream to file
*/
void convert_and_send_video(void)
{
/*	create a variable to hold processed frames*/
    gray_frame = cvCreateImage(cvGetSize(video_frame),IPL_DEPTH_8U, 1);

/*  create a thread to send the frame */
    pthread_create(&server_thread, NULL, video_server, NULL);


/*	video processing loop */	
    while(video_frame > 0){
    video_frame = cvQueryFrame(video_capture);

        if(!video_frame)
        break;
        video_frame -> origin = 0;

    pthread_mutex_lock(&mutex);
    cvCvtColor(video_frame, gray_frame, CV_BGR2GRAY);
    new_data = 1;
    pthread_mutex_unlock(&mutex);


    }

/*
	clean up memory after use
*/

    cvReleaseImage(&gray_frame);
    cvReleaseCapture(&video_capture);
    pthread_mutex_destroy(&mutex);

}
