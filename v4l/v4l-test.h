#include <asm/types.h> /* needed for videodev2.h */
#include <fcntl.h>
#include <linux/videodev2.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>

#ifndef BUFFER_STRUCT
#define BUFFER_STRUCT

struct buffer
{ 
  void *start;
  size_t size;
};

#endif
