#!/bin/sh
export PKG_CONFIG_PATH=/opt/ffmpeg/lib/pkgconfig
rm *.o test &> /dev/null
gcc `pkg-config --cflags libavformat` -c camStatus.c -o camStatus.o
gcc `pkg-config --libs libavformat` camStatus.o -o camStats
