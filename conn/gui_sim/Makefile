.SILENT:

frame: gui_frame.c gui_frame.h
	gcc gui_frame.c -o gui_frame `pkg-config --cflags --libs gtk+-2.0` 

server: gui_tcpserver_main.c
	gcc gui_tcpserver_main.c -o tcps
clean:
	rm -f gui_frame