
#############################################################################
#  Makefile for use in the project root directory.
#  The purpose is to have one makefile to build the whole system
#  using flags that gets exported and invoke lower level makefiles
#  on a group level. This will need to be changed to work with the 
#  Arduino makefile created by Mihail and Eugene.
#
#  Author: Joakim
#  Date: 2011-04-15
#
#  History:
#  2011-04-13 - Created this file
#
#  Notes:
#  This only works for building and compiling for PC at the moment.
#############################################################################

# these two are exported to be used in lower level makefiles
export GLOBAL_CFLAGS
export GLOBAL_CC


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

BIN:$(OBJS)


pc: GLOBAL_CC=gcc
pc: GLOBAL_CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) -I$(INCLUDES)
pc:
	cd sched/src && $(MAKE) lib
	cd stab/src && $(MAKE) lib
	cd moto/src && $(MAKE) lib
	$(CC) -c main.c -Isched/src
	$(CC) -o $(PROG) main.o $(GROUP_LIBS)
	

pc-dbg: GLOBAL_CC=gcc
pc-dbg: GLOBAL_CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) $(DEBUG_FLAGS) $(INCLUDES)
pc-dbg:
	cd sched/src && $(MAKE) lib
	cd stab/src && $(MAKE) lib
	cd moto/src && $(MAKE) lib
	$(CC) -c main.c -Isched/src
	$(CC) -o $(PROG) main.o $(GROUP_LIBS)


mega: GLOBAL_CC=avr-gcc
mega: GLOBAL_CFLAGS+=$(ARDUINO_FLAGS)
mega:
	cd sched/src && $(MAKE) ardu
	cd stab/src && $(MAKE) ardu


mega-dbg: GLOBAL_CC=avr-gcc
mega-dbg: GLOBAL_CFLAGS+=$(ARDUINO_FLAGS) $(DEBUG_FLAGS)
mega-dbg:
	cd sched/src && $(MAKE) ardu
	cd stab/src && $(MAKE) ardu



clean:
	rm $(PROG) *.o
	cd sched/src && $(MAKE) clean
	cd stab/src && $(MAKE) clean

	

.PHONY: pc pc-dbg mega mega-dbg