#!/bin/sh
export PKG_CONFIG_PATH=/opt/ffmpeg/lib/pkgconfig
rm *.o video-test &> /dev/null
gcc `pkg-config --cflags libavformat libavcodec libavutil` -c video-codec.c -o video-codec.o
gcc `pkg-config --libs libavformat libavcodec libavutil` -o video-codec video-codec.o
