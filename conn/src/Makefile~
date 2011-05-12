.SILENT:

frame: conn_frame.c conn_frame.h
	gcc conn_frame.c -o conn_frame `pkg-config --cflags --libs gtk+-2.0` 

server: conn_tcpserver_main.c
	gcc conn_tcpserver_main.c -o tcps
clean:
	rm -f conn_frame