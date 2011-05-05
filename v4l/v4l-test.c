/* This file is written by Jon Kristensen and Mahdi Abdinejadi. */
//TODO: Add more comments
#include <asm/types.h> /* needed for videodev2.h */
#include <fcntl.h>
#include <linux/videodev2.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"

#include "v4l-test.h"
//#include "encode.h"
//#include "network.h"

//#define DEVICE_PATH "/dev/v4l/by-id/usb-046d_0809_F15A496F-video-index0" //A4Tech
#define DEVICE_PATH "/dev/v4l/by-id/usb-Microsoft_Microsoft_LifeCam_NX-3000-video-index0" //Microsoft

#define CAMERA_WIDTH 176 //800
#define CAMERA_HEIGHT 144 //600

#define BUFFER_DURATION 5.0
#define BUFFER_FRAME_RATE 25 /* 25 images/s */
#define BUFFER_NUM_FRAMES ((int)(BUFFER_DURATION * BUFFER_FRAME_RATE))
#define BUFFER_PIX_FORMAT PIX_FMT_YUV422P

AVFrame *picture;
uint8_t *video_output_buffer;
int frame_counter, video_output_buffer_size;

struct buffer *bs = NULL;

int fd = 0;

static AVStream *get_video_stream(AVFormatContext *format_context, enum CodecID codec_id)
{
  AVCodecContext *codec_context;
  AVStream *stream;

  stream = av_new_stream(format_context, 0);

  if(!stream)
  {
    fprintf(stderr, "Could not allocate stream.\n");
    exit(1);
  }

  codec_context = stream->codec;
  codec_context->bit_rate = 400000;
  codec_context->codec_id = codec_id;
  codec_context->codec_type = AVMEDIA_TYPE_VIDEO;
  codec_context->height = CAMERA_HEIGHT;
  codec_context->pix_fmt = BUFFER_PIX_FORMAT;
  codec_context->time_base.den = BUFFER_FRAME_RATE;
  codec_context->time_base.num = 1;
  codec_context->width = CAMERA_WIDTH;

  /* our format needs a global headers */
  codec_context->flags |= CODEC_FLAG_GLOBAL_HEADER;

  return stream;
}

static AVFrame *allocate_picture(enum PixelFormat pixel_format)
{
  AVFrame *picture;
  uint8_t *picture_buffer;
  int size;

  picture = avcodec_alloc_frame();

  if(!picture)
  {
    return NULL;
  }

  size = avpicture_get_size(pixel_format, CAMERA_WIDTH, CAMERA_HEIGHT);
  picture_buffer = av_malloc(size);

  if(!picture_buffer)
  {
    av_free(picture);
    return NULL;
  }

  avpicture_fill((AVPicture *) picture, picture_buffer, pixel_format, CAMERA_WIDTH, CAMERA_HEIGHT);
  return picture;
}

static void open_video(AVFormatContext *format_context, AVStream *stream)
{
  AVCodec *codec;
  AVCodecContext *codec_context;

  codec_context = stream->codec;

  codec = avcodec_find_encoder(codec_context->codec_id);
  if(!codec)
  {
    fprintf(stderr, "Codec was not found.\n");
    exit(1);
  }

  if(avcodec_open(codec_context, codec) < 0)
  {
    fprintf(stderr, "Codec could not be opened.\n");
    exit(1);
  }

  video_output_buffer = NULL;
  if(!(format_context->oformat->flags & AVFMT_RAWPICTURE))
  {
    video_output_buffer_size = 200000; /* TODO: optimize memory allocation */
    video_output_buffer = av_malloc(video_output_buffer_size);
  }

  picture = allocate_picture(codec_context->pix_fmt);

  if(!picture)
  {
    fprintf(stderr, "Could not allocate picture.\n");
    exit(1);
  }
}

static void fill_image(AVFrame *frame)
{
  int s, k;
  char *ptr;
  ptr = (char*) bs[0].start;
  s = bs[0].size;
  for(k=0; k < bs[0].size; k++)
  {
    switch (k % 4)
    {
    case 0: case 2:
      frame->data[0][k/2] = ptr[k];
      break;
    case 1:
      frame->data[1][((k-1)/4)] = ptr[k];
      break;
    case 3:
      frame->data[2][((k-3)/4)] = ptr[k];
      break;
    }
  }

  // printf(">>bs.size = %d and k = %d\n", s , k);
}

static void write_frame(AVFormatContext *format_context, AVStream *stream)
{
  int output_size, result;
  AVCodecContext *codec_context;

  codec_context = stream->codec;

  if(frame_counter < BUFFER_NUM_FRAMES)
  {
    fill_image(picture);
  }

  if(format_context->oformat->flags & AVFMT_RAWPICTURE)
  {
    AVPacket packet;
    av_init_packet(&packet);

    packet.data = (uint8_t *) picture;
    packet.flags |= AV_PKT_FLAG_KEY;
    packet.size = sizeof(AVPicture);
    packet.stream_index = stream->index;

    result = av_interleaved_write_frame(format_context, &packet);
  }
  else
  {
    /* encoding image */
    output_size = avcodec_encode_video(codec_context, video_output_buffer, video_output_buffer_size, picture);

    /* zero sized means it was buffered */
    if(output_size > 0)
    {
      AVPacket packet;
      av_init_packet(&packet);

      if(codec_context->coded_frame->pts != AV_NOPTS_VALUE)
      {
        packet.pts= av_rescale_q(codec_context->coded_frame->pts, codec_context->time_base, stream->time_base);
      }

      if(codec_context->coded_frame->key_frame)
      {
        packet.flags |= AV_PKT_FLAG_KEY;
      }

      packet.stream_index = stream->index;
      packet.data = video_output_buffer;
      packet.size = output_size;

      result = av_interleaved_write_frame(format_context, &packet);
    }
    else
    {
      result = 0;
    }
  }
  if(result != 0)
  {
    fprintf(stderr, "Error writing video frame.\n");
    exit(1);
  }

  frame_counter++;
}

static void close_video(AVStream *stream)
{
  avcodec_close(stream->codec);
  av_free(picture->data[0]);
  av_free(picture);
  av_free(video_output_buffer);
}

/* reads a frame and prints its content */
int read_frame()
{
  struct v4l2_buffer b;
  unsigned int i;

  memset(&(b), 0, sizeof(b));

  b.memory = V4L2_MEMORY_MMAP;
  b.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if(ioctl(fd, VIDIOC_DQBUF, &b) == -1) /* blocks if no buffer in queue */
  {
    switch(errno)
    {
      case EAGAIN:
        return 0;

      case EIO:

    default:
      fprintf(stderr, "Error dequeing the buffer.\n");
    }
  }

  if(ioctl(fd, VIDIOC_QBUF, &b) == -1)
  {
    fprintf(stderr, "Error enqueing the buffer.\n");
    return -1;
  }

  return 0;
}

int main(int argc, char **argv)
{
  const char *filename;
  AVOutputFormat *output_format;
  AVFormatContext *format_context;
  AVStream *video_stream;
  double video_pts;
  int i;

  /* open the v4l2 device, get a file descriptor */

  printf("Opening device...\n");

  fd = open(DEVICE_PATH, O_NONBLOCK | O_RDWR);

  if(fd == -1)
  {
    fprintf(stderr, "Could not open device.\n");
    return -1;
  }

  /* check the capabilities of the device */

  printf("Checking device capabilities...\n");

  struct v4l2_capability c;

  /* assumption: we can use ioctl instead of xioctl */

  if(ioctl(fd, VIDIOC_QUERYCAP, &c) == -1) // todo: error checking
  {
    fprintf(stderr, "Device is not a V4L2 device.\n");
    return -1;
  }

  if(!(c.capabilities & V4L2_CAP_VIDEO_CAPTURE))
  {
    fprintf(stderr, "Device is not a video capturing device.\n");
    return -1;
  }

  if(!(c.capabilities & V4L2_CAP_STREAMING))
  {
    fprintf(stderr, "Device does not support streaming.\n");
    return -1;
  }

  /* set format */

  printf("Setting video format...\n");

  struct v4l2_format f;
  memset(&(f), 0, sizeof(f));

  f.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  f.fmt.pix.width = CAMERA_WIDTH;
  f.fmt.pix.height = CAMERA_HEIGHT;
  f.fmt.pix.field = V4L2_FIELD_INTERLACED;
  f.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
  if(ioctl(fd, VIDIOC_S_FMT, &f) == -1)
  {
    fprintf(stderr, "Could not negotiate format.\n");
    return -1;
  }

  /* initialize memory mapping */

  printf("Initializing memory mapping...\n");

  struct v4l2_requestbuffers rb;
  memset(&(rb), 0, sizeof(rb));

  rb.count = 4;
  rb.memory = V4L2_MEMORY_MMAP;
  rb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if(ioctl(fd, VIDIOC_REQBUFS, &rb) == -1)
  {
    fprintf(stderr, "Device does not support memory mapping.\n");
    return -1;
  }

  if(rb.count < 2)
  {
    fprintf(stderr, "Insufficient buffer memory.\n");
    return -1;
  }

  bs = calloc(rb.count, sizeof(*bs));

  if(!bs)
  {
    fprintf(stderr, "Out of memory.\n");
    return -1;
  }

  av_register_all();

  filename = "test_video.webm";

  output_format = av_guess_format("vp8", filename, NULL);

  if(!output_format)
  {
    fprintf(stderr, "Could not find/guess VP8 output format.\n");
    exit(1);
  }

  format_context = avformat_alloc_context();

  if(!format_context)
  {
    fprintf(stderr, "Format context memory error.\n");
    exit(1);
  }

  format_context->oformat = output_format;
  snprintf(format_context->filename, sizeof(format_context->filename), "%s", filename);
  printf("snprint \n");

  video_stream = NULL;

  if(output_format->video_codec != CODEC_ID_NONE)
  {
    video_stream = get_video_stream(format_context, output_format->video_codec);
    printf("video_stream initialized.\n");
  }

  if(av_set_parameters(format_context, NULL) < 0)
  {
    fprintf(stderr, "Invalid output format parameters.\n");
    exit(1);
  }

  av_dump_format(format_context, 0, filename, 1);
  printf("3\n");

  if(video_stream)
  {
    open_video(format_context, video_stream);
  }

  if(!(format_context->flags & AVFMT_NOFILE))
  {
    if(avio_open(&format_context->pb, filename, URL_WRONLY) < 0)
    {
      fprintf(stderr, "Could not open \"%s\".\n", filename);
      exit(1);
    }
  }

  av_write_header(format_context);
  printf("Can write the header file.\n");

  int ii = 0;
  for(ii = 0; ii < rb.count; ii++)
  {
    struct v4l2_buffer b;
    memset(&(b), 0, sizeof(b));

    b.index = ii;
    b.memory = V4L2_MEMORY_MMAP;
    b.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(ioctl(fd, VIDIOC_QUERYBUF, &b) == -1)
    {
      fprintf(stderr, "Buffer status error; invalid buffer type or index.\n");
      return -1;
    }

    bs[ii].size = b.length;
    bs[ii].start = mmap(NULL, b.length, PROT_READ | PROT_WRITE, MAP_SHARED,
                       fd, b.m.offset);

     if(bs[ii].start == MAP_FAILED)
    {
      fprintf(stderr, "Memory mapping failed.\n");
      return -1;
    }
  }

  printf("Initializing capturing...\n");

  unsigned int j;
  enum v4l2_buf_type t;

  for(j = 0; j < ii; j++)
  {
    struct v4l2_buffer b;
    memset(&(b), 0, sizeof(b));

    b.index = j;
    b.memory = V4L2_MEMORY_MMAP;
    b.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(ioctl(fd, VIDIOC_QBUF, &b) == -1)
    {
      fprintf(stderr, "Error enqueing the buffer.\n");
    }
  }

  t = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if(ioctl(fd, VIDIOC_STREAMON, &t) == -1)
  {
    fprintf(stderr, "Error streaming IO.\n");
  }

  printf("Capturing...\n");

  unsigned int count;

  while(1)
  {
    fd_set fds;
    struct timeval tv;

    int r;

    FD_ZERO (&fds);
    FD_SET (fd, &fds);

    tv.tv_sec = BUFFER_DURATION;
    tv.tv_usec = 0;

    r = select(fd + 1, &fds, NULL, NULL, &tv);

    if(r == -1)
    {
      if(EINTR == errno)
      {
        continue;
      }

      fprintf(stderr, "Select error.\n");
      return -1;
    }

    if(r == 0)
    {
      fprintf(stderr, "Select time-out.\n");
      return -1;
    }

    if(video_stream)
    {
      video_pts = (double) video_stream->pts.val * video_stream->time_base.num / video_stream->time_base.den;
    }
    else
    {
      video_pts = 0.0;
    }

    if(!video_stream || video_pts >= BUFFER_DURATION)
    {
      break;
    }

    if(read_frame() == -1)
    {
      fprintf(stderr, "read_frame() error.\n");
      return -1;
    }

    write_frame(format_context, video_stream);
  }

  av_write_trailer(format_context); /* TODO: stream to socket instead of file */

  /* close each codec */
  if(video_stream)
  {
    close_video(video_stream);

    for(i = 0; i < format_context->nb_streams; i++)
    {
      av_freep(&format_context->streams[i]->codec);
      av_freep(&format_context->streams[i]);
    }
  }

  if(!(format_context->flags & AVFMT_NOFILE))
  {
    /* close file */
    avio_close(format_context->pb);
  }

  av_free(format_context);
  return 0;
}
