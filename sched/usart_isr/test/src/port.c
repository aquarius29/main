
/*
 *  code to send data over serial port (USB to arduino-board)
 *  
 *  will be exchanged for real code later when testing on the mega-side
 *  is complete
 *
 *  author: Michal, Joakim
 */

#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

void serialSend(uint8_t *data, FILE *fd);

int port_run(){
    int done = FALSE;

  struct termios options;

  int fd;
  int wr;
  int flag;

  uint8_t data[] = {3, 1, 2, 3, '\0'};
  uint8_t data1[] = {3, 1, 2, 3};

  fd = open ("/dev/tty.usbmodemfa141",O_RDWR |O_NOCTTY | O_NDELAY);
  if (fd < 0){
    printf("Cant open port\n");

  }
  else{
    printf("Port opened \n");
    //fcntl(fd, F_SETFL,0);

  }

 tcgetattr(fd, &options);
 cfsetispeed(&options, B9600);
 cfsetospeed(&options, B9600);
 options.c_cflag |= (CLOCAL | CREAD);
 options.c_cflag |= CS8;
 
 options.c_oflag &= ~OPOST;

 // options.c_cflag |= CSTOPB; original

 tcsetattr(fd, TCSANOW, &options);
 
    uint8_t first = 0;
 
    sleep(1);
 
    while(!done){
        uint8_t i;
        if (first != 1) {     
            // for (i = 0; i < 4; i++) {
            //     write(fd, &data1[i], 1);
            // }
            serialSend(data, fd);
            first = 1;
        }
        done = TRUE;
    }
    sleep(3);
 
 printf("Closing\n");
 //  close(fd);
  return 0;
}

void serialSend(uint8_t *data, FILE *fd){
    while (*data != '\0') {
        printf("*data is: %d\n", *data);
        write(fd, data, 1);
        data++;
    }    
}

