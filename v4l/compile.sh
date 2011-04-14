#!/bin/sh
rm *.o video-test &> /dev/null
gcc -c v4l-test.c -o v4l-test.o
gcc -o v4l-test v4l-test.o
