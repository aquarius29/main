.SILENT:

frame: conn_frame.c conn_frame.h
	gcc conn_frame.c -o conn_frame `pkg-config --cflags --libs gtk+-2.0` 

frame_dbg: conn_frame.c conn_frame.h
	gcc conn_frame.c -DDEBUG -o conn_frame `pkg-config --cflags  --libs gtk+-2.0` 

server_dbg: main.c conn_tcpserver_main.c conn_tcpserver.c conn_ui_mask.c 
	gcc main.c conn_tcpserver_main.c conn_tcpserver.c conn_ui_mask.c  -DDEBUG  -o server_dbg


server: main.c conn_tcpserver_main.c conn_tcpserver.c conn_ui_mask.c
	gcc main.c  conn_tcpserver_main.c conn_tcpserver.c conn_ui_mask.c -o server
clean:
	rm -f conn_frame