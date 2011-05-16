<<<<<<< HEAD
########################### Added by Adam 09/05/11 #########################

LIB_SRC=conn_tcpserver.c conn_tcpserver_main.c conn_ui_mask.c 

LIB_OBJ = $(LIB_SRC:.c=.o)

%.o: %.c
	$(GLOBAL_CC) -c -I. $*.c $(GLOBAL_CFLAGS)

lib-pc: $(LIB_OBJ)
	ar rvs ../lib/libconn.a $(LIB_OBJ)

lib-panda: $(LIB_OBJ)
	ar rvs ../lib/libconn.a $(LIB_OBJ)

lib-mega: $(LIB_OBJ)
	@echo Objects: $(LIB_OBJ)
	avr-ar rvs ../lib/libconn.a $(LIB_OBJ)

clean:
	rm -f *.o

##########################################################################
=======
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
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
