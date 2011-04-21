#ifndef SERIAL
#define SERIAL

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

#define UNO "/dev/ttyACM0"
#define UNO1 "/dev/ttyACM1"
#define UNO2 "/dev/ttyACM2"
#define UNO3 "/dev/ttyACM3"
#define UNO4 "/dev/ttyACM4"
#define UNO5 "/dev/ttyACM5"


int serial_write(int fd, const char* str);

int serial_read(int fd, char* buf, char until);

int serial_init(const char* port, int baud);

void serial_kill(int fd);

int dev_init(char* dev,int baud);

#endif
