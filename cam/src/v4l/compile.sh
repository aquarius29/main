#!/bin/sh
export PKG_CONFIG_PATH=/opt/ffmpeg/lib/pkgconfig
rm *.o video-test &> /dev/null
<<<<<<< HEAD
gcc `pkg-config --cflags libavformat libavcodec libavutil` -c video-codec.c -o video-codec.o
gcc `pkg-config --libs libavformat libavcodec libavutil` -o video-codec video-codec.o
=======
gcc `pkg-config --cflags libavformat libavcodec libavutil` -c v4l-test.c -o v4l-test.o
gcc `pkg-config --cflags libavformat libavcodec libavutil` -c encode.c -o encode.o
gcc `pkg-config --libs libavformat libavcodec libavutil` -o v4l-test v4l-test.o encode.o
>>>>>>> b0cb99a39bc87d0bfbcefbf874ebe2de4c1aa830
