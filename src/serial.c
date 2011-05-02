/*
 *@File:serial.c
 *
 *@Date: Apr 7, 2011
 *      
 *@Author: Jianfeng Xie
 *
 *@Description: Under Ubuntu Operating System, open a external device and build serial communication.
 *	
 *
 */
#include "serial.h"


/* wirte data to external device
 * 
 *@param int port_number, const char* sending_data; 
 *@return a int what shows it works or faile, 0 == ok and -1 ==error
 */
int serial_write(int fd, const char* str)
{
    int len = strlen(str);
    int n = write(fd, str, len);         /*serial port,data,length of data*/
    if( n != len )
        return -1;
    return 0;
}



/*read data from external device
 *
 *@param int port_number,char* string_buffer and char until;
 *@return a int which shows it works well or fail, 0 == ok and -1 == error
 */
int serial_read(int fd, char* buf, char until)
{
    char b[1];
    int i=0;
    do {
        int n = read(fd, b, 1);  		/* read a char once */
        if( n == -1)
            return -1;    		        /* couldn't read, reutrn -1*/
        if( n == 0 ) {
            usleep( 10 * 1000);                 /*wait 10 msec try again*/
            continue;
        }
        buf[i] = b[0];                          /*buf get a char*/ 
        i++;

    } while(b[0] != until);

    buf[i] = 0;                                 /*string ends with null terminate */
    return 0;
}




/* open a serail port and set baudrate, the connection is via terminnal
 *
 *@param const char* prot_name and int baudrate 
 *@return a integer file_id or -1 (error)
 */
int serial_init(const char* port, int baud)
{
    struct termios toptions;                         /*define a termios structure to store data*/
    int fd;
    fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);   /*open a prot and set it as read and write*/ 
    if (fd == -1)  {
        printf("init_serialport: Unable to open port\n");    /*fail in opening file*/
        return -1;
    }

    if (tcgetattr(fd, &toptions) < 0) {          /*get the parameters associated with terminal*/
        printf("init_serialport: Couldn't get term attributes\n");   
        return -1;
    }
    speed_t brate = baud;                  /*override switch below if needed*/
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
    cfsetospeed(&toptions, brate);    /*set terminal write and read speed*/

 
    if( tcsetattr(fd, TCSANOW, &toptions) < 0) {                      /*set the parameters assoicated with terminal*/
        printf("init_serialport: Couldn't set term attributes\n");
        return -1;
 	  }

    return fd;
}



/* close the serial port
 *
 *@param int file_id
 *@return void
 */
void serial_kill(int fd){
    close(fd);
    }



/* loop for init gps device 
 *
 *@param char* device_name and int baudrate
 *@return int file_id;
 */

int dev_init(char* dev,int baud)
{
    int fd = -1;
    int i = 0;	    		    
    while(fd == -1)
    {
        if(i==5)
        return -1;
    fd = serial_init(dev,baud);	
    i++;
    }
    return fd;
}

