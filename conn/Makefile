BIN	= bin/
SRC	= src/
GCC 	= gcc
RM 	= rm -f

default:
	@echo "frame to compile gui and client "
	@echo "frame_dgb debug mode"
	@echo "server to compile a server"
	@echo "server_dbg debug mode "

#complile gui with client
.SILENT:

frame: $(SRC)conn_frame.c $(SRC)conn_tcpclient.c $(SRC)conn_tcpclient_main.c
	$(GCC) $(SRC)conn_frame.c $(SRC)conn_tcpclient_main.c $(SRC)conn_tcpclient.c -o $(BIN)frame `pkg-config --cflags --libs gtk+-2.0` 

frame_dbg:$(SRC)conn_frame.c $(SRC)conn_tcpclient.c $(SRC)conn_tcpclient_main.c
	$(GCC) $(SRC)conn_frame.c $(SRC)conn_tcpclient_main.c $(SRC)conn_tcpclient.c -DDEBUG -o $(BIN)frame_dbg `pkg-config --cflags  --libs gtk+-2.0` 

server_dbg: $(SRC)main.c $(SRC)conn_tcpserver_main.c $(SRC)conn_tcpserver.c $(SRC)conn_ui_mask.c 
	$(GCC) $(SRC)main.c $(SRC)conn_tcpserver_main.c $(SRC)conn_tcpserver.c $(SRC)conn_ui_mask.c -DDEBUG -DDEBUG_SPECIAL -o $(BIN)server_dbg


server: $(SRC)main.c $(SRC)conn_tcpserver_main.c $(SRC)conn_tcpserver.c $(SRC)conn_ui_mask.c 
	$(GCC) $(SRC)main.c $(SRC)conn_tcpserver_main.c $(SRC)conn_tcpserver.c $(SRC)conn_ui_mask.c -o $(BIN)server
clean:
	cd/bin & $(RM) *.* 