/*
 * 	serial.c
 *
 *  	Created on: Apr 7, 2011
 *      
 *	Author: Jianfeng Xie & Qiushi Wang
 *
 *	Description: Under Ubuntu Operating System, open a external device and build serial communication.
 *	
 *
 */

#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h>
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>


#define MEGA "/dev/ttyUSB0"
#define MEGA1 "/dev/ttyUSB1"
#define MEGA2 "/dev/ttyUSB2"
#define MEGA3 "/dev/ttyUSB3"
#define MEGA4 "/dev/ttyUSB4"
#define MEGA5 "/dev/ttyUSB5"
#define MEGA6 "/dev/ttyUSB6"
#define MEGA7 "/dev/ttyUSB7"
#define MEGA8 "/dev/ttyUSB8"
#define MEGA9 "/dev/ttyUSB9"
#define MEGA10 "/dev/ttyUSB10"



int serial_write(int fd, const char* str)
{
    int len = strlen(str);
    int n = write(fd, str, len);
    if( n!=len )
        return -1;
    return 0;
}

int serial_read(int fd, char* buf, char until)
{
    char b[1];
    int i=0;
    do {
        int n = read(fd, b, 1);  // read a char at a time
        if( n==-1) return -1;    // couldn't read
        if( n==0 ) {
            usleep( 10 * 1000 ); // wait 10 msec try again
            continue;
        }
        buf[i] = b[0]; i++;

    } while( b[0] != until );

    buf[i] = 0;  // null terminate the string
    return 0;
}

int serial_init(const char* serialport, int baud)
{
    struct termios toptions;
    int fd;



    fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)  {
        printf("init_serialport: Unable to open port\n ");
        return -1;
    }

    if (tcgetattr(fd, &toptions) < 0) {
        printf("init_serialport: Couldn't get term attributes\n");
        return -1;
    }
    speed_t brate = baud; // let you override switch below if needed
    switch(baud) {
    case 4800:   brate=B4800;   break;
    case 9600:   brate=B9600;   break;
#ifdef B14400
    case 14400:  brate=B14400;  break;
#endif
    case 19200:  brate=B19200;  break;
#ifdef B28800
    case 28800:  brate=B28800;  break;
#endif
    case 38400:  brate=B38400;  break;
    case 57600:  brate=B57600;  break;
    case 115200: brate=B115200; break;
    }
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);

 
    if( tcsetattr(fd, TCSANOW, &toptions) < 0) {
        printf("init_serialport: Couldn't set term attributes\n");
        return -1;
 	  }

    return fd;
}


void serial_kill(int fd){
	close(fd);
	}








/* 0 = correct; 1 = failed*/
int dev_init(char* dev,int baud)
{
	int fd = -1;

	int i = 0;	    		    
	while(fd == -1)
	{
		if(i==100)
		return -1;
		
		fd = serial_init(dev,baud);	
		i++;
		}

	return fd;
}




int main(){
	
	int fd = 0;
	int baud = 57600;
	char buf [256];

	fd = dev_init(MEGA3,baud);

	if(fd == -1)
	return 0;

	usleep(3000*1000);

	while(1){
	    	serial_read(fd,buf,10);
	    	printf("%s",buf);
		usleep(100000);
		}

return 0;
}




/*
int main()
{
	    int fd = 0;
	    char serialport[256]= MEGA;

	    char buf[256];
	 
	    int baudrate = 9600;

		fd = serial_init(serialport,baudrate);	

	    usleep(3000*1000);

	    while(1){
	    	serial_read(fd,buf,10);
	    	printf("read: %s",buf);
		usleep(1000*10);
		}
}*/
