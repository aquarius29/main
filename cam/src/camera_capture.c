/*-------------------------------------------------------------------------------------------------------
**	camera_capture.c
**	Authors: Henry Ikuh, Abdirashid Jama

* The program captures frames from webcam using opencv computer vision library in c.
* file name: camera_capture.c
 
**	Prerequisite:
**	Install: ffmpeg
**	OpenCV
**	v4l2 (comes with your linux distribution)
**	References: http://www.ffmpeg.org/
				http://opencv.willowgarage.com/documentation/reading_and_writing_images_and_video.html
				http://www.nashrudding.com
 
*--------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../include/cv.h"
#include "../include/highgui.h"


/*	opencv video capture structure and video image */
CvCapture* video_capture;
IplImage* video_frame;
IplImage* gray_frame;

/*	available frame */
int new_data;

/*	create two threads thats will convert frames to gray and 
	the other thread to send the gray frame to the server */
pthread_mutex_t	 mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t 	thread_new;

void *video_server();
void capture(int argc, char** argv)
{
	char key;
/*	Initialize the video capturing from webcam. The video device number: 1 or 0 */
	video_capture = cvCaptureFromCAM(1);
	if(!video_capture){
	terminate("could not capture from device",1);
	}

/*	Grab, decompress and return the video_frame image. */
	video_frame = cvQueryFrame(video_capture);

/*	We create a new image in gray which will have only onw color or 1-channel image
 	byte. this will kind of reduce complexity in compression since we stripe off the
	the multiple color in the original image and set to zero clear the array - 
	gray_frame. the gray_frame will be used later for conversion */
	gray_frame = cvCreateImage(cvGetSize(video_frame),IPL_DEPTH_8U, 1);
	cvZero(gray_frame);

/*	display the frame width and height in the terminal, client will need this as an argument*/
	fprintf(stdout, "Frame Width: %d\n", video_frame -> width);
	fprintf(stdout, "Frame Height: %d\n\n", video_frame -> height);
	printf("******************************\n");
	fprintf(stdout, "Press Ctrl+C to stop streaming\n");

/*	create a window using highgui to display streaming on the server side*/
	//cvNamedWindow("QUADROTOR-SERVER",CV_WINDOW_AUTOSIZE);

/*	create a new thread thread_new to stream the gray images to the server
	int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    void *(*start_routine)(void*), void *arg);
*/
	pthread_create(&thread_new, NULL, video_server, NULL);

/*	writing the video frames to a file we will need to get the exact frame size 
	from the frame property. calling the CvSize function*/
	CvSize size = cvSize((int)cvGetCaptureProperty(video_capture,CV_CAP_PROP_FRAME_WIDTH),
						(int)cvGetCaptureProperty(video_capture,CV_CAP_PROP_FRAME_WIDTH));

	CvVideoWriter *writer = cvCreateVideoWriter("out.avi", CV_FOURCC('D','I','V','X'), 25,size, 1);

/*	create a loop that gets the video_frame from the camera, save video to a file,
	convert the video_frames to gray_frames, data is available to stream to client*/
	while(key != 'c'){
	video_frame = cvQueryFrame(video_capture);
	cvWriteFrame(writer, video_frame);

		if(!video_frame)
		break;
		video_frame -> origin = 0;

	pthread_mutex_lock(&mutex);
	cvCvtColor(video_frame, gray_frame, CV_BGR2GRAY);
	new_data = 1;
	pthread_mutex_unlock(&mutex);

/*	show the video */
	//cvShowImage("QUADROTOR-SERVER", video_frame);
	key = cvWaitKey(28);

	}
	
/* memory management */
	cvDestroyWindow("QUADROTOR-SERVER");
	cvReleaseVideoWriter(&writer);
	terminate(NULL,0);

}
