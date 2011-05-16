<<<<<<< HEAD
#############################################################################
##  Description:
##  Makefile for use in the project root directory.
##  The purpose is to have one makefile to build the whole system
##  using flags that gets exported and invoke lower level makefiles
##  on a group level.
##
##  Usage:
##  All platforms have a target and a debug-target. For example the
##  mega-board has a "mega" and a "mega-dbg" target.
##
##  The "mega-targets" creates a file that can be flashed to the board
##  by invoking the "flash" target.
##
##  Some flags gets exported and are used in lower level makefiles.
##  These are prefixed with "GLOBAL_". The various targets constructs the 
##  content of these variables to create a certain configuration that is 
##  used in the lower level makefiles.
##
##  The BASIC_LIBS variable specifies what libraries to include and the path
##  to those. This variable should only specify libraries that are needed
##  and work with all targets that has to do with the basic functionality
##  sub-system. This is a good place to choose to use code stubs representing
##  other groups code, or to use those groups real code.
##
##  The BASIC_INCLUDES variable specifies paths to headers in the code
##  that is used in the basic functionality sub-system. This makes it
##  possible for source files to include project headers by name only.
##  Any potential structural changes only needs to be taken care of here.
##
##  Any temporary or extra flags should be added to EXTRA_FLAGS when for
##  example testing ideas.
##
##  Author:	Joakim
##  Date: 	2011-04-15
##
##  History:
##  2011-04-13 - Created this file. - Joakim
##
##  2011-04-15 - Started work to merge with the arduino-flasher
##  			 makefile. - Joakim
##
##  2011-04-18 - Merged with the makefile written by Eugene and Mihail,
##				 creating libs and linking with libcoremega and then 
##				 uploading to the mega-board now works. Also merged the
##				 makefile that worked with PC targets. Added "Usage" part
##				 in comments. - Joakim
##
##  2011-04-20 - Fixed problems with linking so correct math lib is used.
##				 Order matters among the link-flags! - Joakim
##
##  2011-04-27 - re-structured and merged scheduler implementations and added
##				 SCHED_FLAG to define implementation. - Anders
##  2011-05-05 - Fixed some things related to the mega - Anders
##
##  2011-05-11 - changed Mega protocol paths from proto/src to proto_mega/src
##
##  2011-05-11 - Added everything related to the panda target. Compiling all the
##               groups code for the board is now possible - Adam
##  Notes:
##  Missing instructions in targets not related to basic system. 
##  By no means done and decided with regards to what flags are set and
##  stuff like that.
##
#############################################################################

##  Name of usb-port
USB_PORT=/dev/tty.usbmodemfa141

##  Name of executable or image
PROG=prog

##  Libraries to include when building the basic system, 
##  only include libs that work for all targets for that system here!
BASIC_LIBS=-Lstab/lib -Lsched/lib -Lmoto/lib -Lmov/lib -Lca/lib -Lproto_mega/lib -Llib -lsched -lstab -lmoto -lmov -lca -lproto -lm

##  Set paths to headers used by code on the basic system
BASIC_INCLUDES=-I../../stab/src -I../../moto/src -I../../mov/src -I../../ca/src -I../../proto_mega/src -I../../include

##  Libraries to include when building the panda system, 
##  only include libs that work for all targets for that system here!
PANDA_LIBS= -Lpsched/lib -Lnav/lib -Lconn/lib -Lcam/lib -Llib -lnav -lpsched -lconn -lcam -lm -lxml2 -lm -lpthread 
#-Lpsched/lib -Lnav/lib -Lconn/lib -Lcam/lib -Lproto_panda/lib -Llib -lnav -lpsched -lconn -lcam -lprotopanda -lm -lxml2 -lm -lpthread 

##  Set paths to headers used by code on the panda system
PANDA_INCLUDES=-I../..psched/src -I../../psched/lib/ -I./include -I../../nav/src -I../..cam/src -I../..conn/src  -I/usr/include/libxml2
#-Iproto_panda/src -Ipsched/src -Ipsched/lib/ -I./include -Inav/src -Icam/src -Iconn/src  -I/usr/include/libxml2

##  Set scheduler implementation (-DBATMAN |-DNAIVE)
SCHED_FLAG=-DBATMAN
=======
<<<<<<< .merge_file_wEzWGB
<<<<<<< .merge_file_XxTeJ2

DEBUG_FLAGS=-g -DDEBUG -Wall
PC_FLAGS=-DPC
ARDUINO_FLAGS=-DARDUINO
GROUP_LIBS=-Lstab/lib -Lsched/lib -Lmoto/lib -lsched -lstab -lmoto

# INCLUDES holds paths to other groups headers
INCLUDES=-I../../stab/src -I../../moto/src
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04

# EXTRA_FLAGS defines what groups code to use instead of stubs
EXTRA_FLAGS=

# PROG is the name of the executable
PROG=prog

export CFLAGS
export CC

BIN:$(OBJS)


<<<<<<< HEAD
## pc-targets ###############################################################
pc: GLOBAL_CC=gcc
pc: GLOBAL_CFLAGS+=$(SCHED_FLAG) $(PC_FLAGS) $(EXTRA_FLAGS) $(BASIC_INCLUDES)
pc:
	cd sched/src && $(MAKE) lib-pc
	cd stab/src && $(MAKE) lib-pc
	cd moto/src && $(MAKE) lib-pc
	cd mov/src && $(MAKE) lib-pc
	cd ca/src && $(MAKE) lib-pc
	cd proto_mega/src && $(MAKE) lib-pc
	$(GLOBAL_CC) -c main.c $(SCHED_FLAG) -Isched/src
	$(GLOBAL_CC) -o $(PROG) main.o $(BASIC_LIBS)


pc-dbg: GLOBAL_CC=gcc
pc-dbg: GLOBAL_CFLAGS+=$(SCHED_FLAG) $(PC_FLAGS) $(EXTRA_FLAGS) $(DEBUG_FLAGS_PC) $(BASIC_INCLUDES)
pc-dbg:
	cd sched/src && $(MAKE) lib-pc
	cd stab/src && $(MAKE) lib-pc
	cd moto/src && $(MAKE) lib-pc
	cd mov/src && $(MAKE) lib-pc
	cd ca/src && $(MAKE) lib-pc
	cd proto_mega/src && $(MAKE) lib-pc
	$(GLOBAL_CC) -c main.c $(SCHED_FLAG) -Isched/src
	$(GLOBAL_CC) -o $(PROG) main.o $(BASIC_LIBS)


## mega-targets #############################################################
mega: BASIC_LIBS+=-l$(CORE_LIB)  ## add the arduino-specific lib to BASIC_LIBS
mega: GLOBAL_CC=avr-g++
mega: GLOBAL_CFLAGS+=$(ARDUINO_FLAGS) $(EXTRA_FLAGS) $(BASIC_INCLUDES)
mega:
	cd sched/src && $(MAKE) lib-mega
	avr-ranlib sched/lib/libsched.a

	cd stab/src && $(MAKE) lib-mega
	avr-ranlib stab/lib/libstab.a

	cd moto/src && $(MAKE) lib-mega
	avr-ranlib moto/lib/libmoto.a	

	cd mov/src && $(MAKE) lib-mega
	avr-ranlib mov/lib/libmov.a	
=======
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
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04


<<<<<<< HEAD
	cd proto_mega/src && $(MAKE) lib-mega
	avr-ranlib proto_mega/lib/libproto.a	

	$(GLOBAL_CC) -c main.c $(SCHED_FLAG) -Isched/src
	$(GLOBAL_CC) main.o $(BASIC_LIBS) $(LDFLAGS_ARDUINO) -o $(PROG).elf
	avr-objcopy -O srec $(PROG).elf $(PROG).rom
=======
ardu: CC=avr-gcc
ardu: CFLAGS+=$(ARDUINO_FLAGS)
ardu:
	cd sched/src && $(MAKE) ardu
	cd stab/src && $(MAKE) ardu

>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04

ardu: CC=avr-gcc
ardu: CFLAGS+=$(ARDUINO_FLAGS) $(DEBUG_FLAGS)
ardu:
	cd sched/src && $(MAKE) ardu
	cd stab/src && $(MAKE) ardu

<<<<<<< HEAD
mega-dbg: BASIC_LIBS+=-l$(CORE_LIB)  ## add the arduino-specific lib to BASIC_LIBS
mega-dbg: GLOBAL_CC=avr-g++
mega-dbg: GLOBAL_CFLAGS+=$(ARDUINO_FLAGS) $(EXTRA_FLAGS) $(BASIC_INCLUDES) $(DEBUG_FLAGS_ARDUINO)
mega-dbg:
	cd sched/src && $(MAKE) lib-mega
	avr-ranlib sched/lib/libsched.a

	cd stab/src && $(MAKE) lib-mega
	avr-ranlib stab/lib/libstab.a

	cd moto/src && $(MAKE) lib-mega
	avr-ranlib moto/lib/libmoto.a	

	cd mov/src && $(MAKE) lib-mega
	avr-ranlib mov/lib/libmov.a	

	cd ca/src && $(MAKE) lib-mega
	avr-ranlib ca/lib/libca.a	

	cd proto_mega/src && $(MAKE) lib-mega
	avr-ranlib proto_mega/lib/libproto.a	

	$(GLOBAL_CC) -c main.c $(SCHED_FLAG) -Isched/src
	$(GLOBAL_CC) main.o  $(BASIC_LIBS) $(LDFLAGS_ARDUINO) -o $(PROG).elf
	avr-objcopy -O srec $(PROG).elf $(PROG).rom


## panda-targets ############################################################
panda: GLOBAL_CC= gcc `pkg-config --cflags --libs opencv`
panda: GLOBAL_CFLAGS+= $(PC_FLAGS) $(EXTRA_FLAGS) $(PANDA_INCLUDES)
panda: 
	cd psched/src && $(MAKE) lib-panda
	cd nav/src && $(MAKE) lib-panda
	cd cam/src && $(MAKE) lib-panda
	cd conn/src && $(MAKE) lib-panda
	cd serial_comm/src && $(MAKE) lib-panda
	#cd proto_panda/src && $(MAKE) lib-panda
	$(GLOBAL_CC) -c panda_main.c  $(PANDA_INCLUDES)
	$(GLOBAL_CC) -o $(PROG) panda_main.o $(PANDA_LIBS)


panda-dbg: GLOBAL_CC= gcc
panda-dbg: GLOBAL_CFLAGS+= $(PC_FLAGS) $(EXTRA_FLAGS) $(PANDA_INCLUDES)
panda-dbg: 

	cd psched/src && $(MAKE) lib-panda
	cd nav/src && $(MAKE) lib-panda
	cd cam/src && $(MAKE) lib-panda
	cd conn/src && $(MAKE) lib-panda
	cd proto_panda/src && $(MAKE) lib-panda
	$(GLOBAL_CC) -c panda_main.c -Ipsched/src
	$(GLOBAL_CC) -o $(PROG) panda_main.o $(PANDA_LIBS)

## n900-targets #############################################################
n900:

n900-dbg:


## ui-targets ###############################################################
ui:

ui-dbg:
=======
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04


clean:
	rm $(PROG) *.o
	cd sched/src && $(MAKE) clean
<<<<<<< HEAD
	cd sched/lib && rm  -f *.a

	cd stab/src && $(MAKE) clean
	cd stab/lib && rm -f *.a

	cd moto/src && $(MAKE) clean
	cd moto/lib && rm -f *.a

	cd mov/src && $(MAKE) clean
	cd mov/lib && rm -f *.a

	cd ca/src && $(MAKE) clean
	cd ca/lib && rm -f *.a

	cd proto_mega/src && $(MAKE) clean
	cd proto_mega/lib && rm -f *.a

	cd nav/src && $(MAKE) clean
	cd nav/lib && rm -f *.a

	cd cam/src && $(MAKE) clean
	cd cam/lib && rm -f *.a

	cd conn/src && $(MAKE) clean
	cd conn/lib && rm -f *.a

	rm -f $(PROG) $(PROG).exe $(PROG).elf $(PROG).rom *.o *.map

=======
	cd stab/src && $(MAKE) clean
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04


.PHONY: lib
=======
=======
>>>>>>> .merge_file_0UbhQC
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
<<<<<<< .merge_file_wEzWGB
>>>>>>> .merge_file_j8AiP3
=======
>>>>>>> .merge_file_0UbhQC
