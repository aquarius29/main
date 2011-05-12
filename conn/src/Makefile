.SILENT:

frame: conn_frame.c conn_frame.h
	gcc conn_frame.c -o conn_frame `pkg-config --cflags --libs gtk+-2.0` 

server: main.c
	gcc main.c -o server
clean:
	rm -f conn_frame