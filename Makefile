<<<<<<< .merge_file_XxTeJ2

DEBUG_FLAGS=-g -DDEBUG -Wall
PC_FLAGS=-DPC
ARDUINO_FLAGS=-DARDUINO
GROUP_LIBS=-Lstab/lib -Lsched/lib -Lmoto/lib -lsched -lstab -lmoto

# INCLUDES holds paths to other groups headers
INCLUDES=-I../../stab/src -I../../moto/src

# EXTRA_FLAGS defines what groups code to use instead of stubs
EXTRA_FLAGS=

# PROG is the name of the executable
PROG=prog

export CFLAGS
export CC

BIN:$(OBJS)


pc: CC=gcc
pc: CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) -I$(INCLUDES)
pc:
	cd sched/src && $(MAKE) lib
	cd stab/src && $(MAKE) lib
	cd moto/src && $(MAKE) lib
	$(CC) -c main.c -Isched/src
	$(CC) -o $(PROG) main.o $(GROUP_LIBS)
	

pc-dbg: CC=gcc
pc-dbg: CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) $(DEBUG_FLAGS) $(INCLUDES)
pc-dbg:
	cd sched/src && $(MAKE) lib
	cd stab/src && $(MAKE) lib
	cd moto/src && $(MAKE) lib
	$(CC) -c main.c -Isched/src
	$(CC) -o $(PROG) main.o $(GROUP_LIBS)


ardu: CC=avr-gcc
ardu: CFLAGS+=$(ARDUINO_FLAGS)
ardu:
	cd sched/src && $(MAKE) ardu
	cd stab/src && $(MAKE) ardu


ardu: CC=avr-gcc
ardu: CFLAGS+=$(ARDUINO_FLAGS) $(DEBUG_FLAGS)
ardu:
	cd sched/src && $(MAKE) ardu
	cd stab/src && $(MAKE) ardu



clean:
	rm $(PROG) *.o
	cd sched/src && $(MAKE) clean
	cd stab/src && $(MAKE) clean

	

.PHONY: lib
=======
################################################################################
## Description:
## Makefile is used to build several programs that purpouse is to provide wireless
## communication throu sockets.
##
##
##
##
##
##  @author Michal Musialik
##  @date 2011-05-07
## @history    2011-04-05 - first outcast of conn_tcpclient.c file
##
################################################################################


BIN	= bin/
SRC	= src/
GCC 	= gcc
RM 	= rm -f

.SILENT:
#List of aviable options
default:
	@echo "------------------------------------------------------"
	@echo " tcpclient: to compile client - run 'tcpc' and IP"
	@echo "------------------------------------------------------"
	@echo " tcpserver: to compile server - run 'tcps' "	
	@echo "------------------------------------------------------"
	@echo " velo: to compile velocity - run 'velo' "
	@echo "------------------------------------------------------"
	@echo " mask_con: mask for convertation - mask_con "
	@echo "------------------------------------------------------"
	@echo " gethost: crating host gathering program - gethost"
	@echo "------------------------------------------------------"
	@echo " tcpclient_debug: to compile client in debug mode"	
	@echo "------------------------------------------------------"
	@echo " tcpserver_debug: to compile in debug mode"
	@echo "------------------------------------------------------"
	@echo " frame - clent server with a GUI"						       
	@echo "------------------------------------------------------"
	@echo " clean: to remove bin"
	@echo "------------------------------------------------------"

#Compiling the TCP client
tcpclient: $(SRC)conn_tcpclient_main.c 
	 $(GCC) $(SRC)conn_tcpclient_main.c -o  $(BIN)tcpc 

#Compiling the TCP server
#tcpserver: tcpserver.c tcpserver_main.c
tcpserver: $(SRC)conn_tcpserver_main.c
	$(GCC) $(SRC)conn_tcpserver_main.c -o $(BIN)tcps 

#Compiling velocity controll
velo: src/conn_velocity.c
	$(GCC) $(SRC)conn_velocity.c -o $(BIN)velo  

#compiling maks for controll
mask_con: src/conn_mask_con.c
	$(GCC) $(SRC)conn_mask_con.c -o $(BIN)mask_con

#compiling host
gethost: src/conn_gethost.c
	$(GCC) $(SRC)conn_gethost.c -o $(BIN)gethost

#server in debug mode
tcpserver_debug: $(SRC)conn_tcpserver_main.c
	$(GCC) $(SRC)conn_tcpserver_main.c -DDEBUG -o $(BIN)tcps_debug

#client in debug mode
tcpclient_debug: $(SRC)conn_tcpclient_main.c
	$(GCC) $(SRC)conn_tcpclient_main.c -DDEBUG -o $(BIN)tcpc_debug

#Client server with gui
frame: $(SRC)conn_frame.c $(SRC)conn_tcpserver_main.c
	$(GCC) $(SRC)conn_frame.c -o $(BIN)conn_frame `pkg-config --cflags --libs gtk+-2.0` 
frame_debug:$(SRC)conn_frame.c $(SRC)conn_tcpserver_main.c
	$(GCC) $(SRC)conn_frame.c -o $(BIN)conn_frame -DDBUG `pkg-config --cflags --libs gtk+-2.0` 
#Removing creataed binary
clean:
	cd $(BIN) && $(RM) *
>>>>>>> .merge_file_j8AiP3
