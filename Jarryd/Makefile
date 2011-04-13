# make file template

SOURCES:=TMXParser.c
OBJECTS:=$(SOURCES:%.c=%.o)
CC=gcc
CFLAGS=-g -Wall -I/usr/include/libxml2
LD=gcc
LDFLAGS=
LIBS=-lxml2
TARGET:=TMXParser

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $(OBJECTS) $(LDFLAGS) $(LIBS)
	
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

depend:
	$(CC) $(CFLAGS) -MM $(SOURCES) > .depend
	
clean:
	rm -f $(OBJECTS) $(TARGET)
	
.depend: depend

include .depend