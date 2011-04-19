#!/bin/sh
export PKG_CONFIG_PATH=/opt/ffmpeg/lib/pkgconfig
rm *.o video-test &> /dev/null
gcc `pkg-config --cflags libavformat libavcodec` -c v4l-test.c -o v4l-test.o
gcc `pkg-config --cflags libavformat libavcodec` -c encode.c -o encode.o
gcc `pkg-config --libs libavformat libavcodec` -o v4l-test v4l-test.o encode.o
