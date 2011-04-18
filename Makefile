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
#  2011-04-15 - Started work to merge with the arduino flasher makefile
#
#  Notes:
#  This only works for building and compiling for PC at the moment.
#############################################################################

# these two are exported to be used in lower level makefiles
export GLOBAL_CFLAGS
export GLOBAL_CC


DEBUG_FLAGS=-g -DDEBUG -Wall
PC_FLAGS=-DPC
ARDUINO_FLAGS=
GROUP_LIBS=-Lstab/lib -Lsched/lib -Lmoto/lib -Llib -lsched -lstab -lmoto -lcoremega

# INCLUDES holds paths to other groups headers
INCLUDES=-I../../stab/src -I../../moto/src -I../../include

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
	$(GLOBAL_CC) -c main.c -Isched/src
	$(GLOBAL_CC) -o $(PROG) main.o $(GROUP_LIBS)
	

pc-dbg: GLOBAL_CC=gcc
pc-dbg: GLOBAL_CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) $(DEBUG_FLAGS) $(INCLUDES)
pc-dbg:
	cd sched/src && $(MAKE) lib
	cd stab/src && $(MAKE) lib
	cd moto/src && $(MAKE) lib
	$(GLOBAL_CC) -c main.c -Isched/src
	$(GLOBAL_CC) -o $(PROG) main.o $(GROUP_LIBS)


MMCU=atmega2560
STK=stk500v2
BAUD=115200
LIB=coremega

mega: GLOBAL_CC=avr-g++
mega: GLOBAL_CFLAGS+=$(ARDUINO_FLAGS) $(EXTRA_FLAGS) $(INCLUDES)
mega:
	cd sched/src && $(MAKE) lib-mega
	avr-ranlib sched/lib/libsched.a
	
	cd stab/src && $(MAKE) lib-mega
	avr-ranlib stab/lib/libstab.a
	
	cd moto/src && $(MAKE) lib-mega
	avr-ranlib moto/lib/libmoto.a	
	
	$(GLOBAL_CC) -c main.c -Isched/src
	$(GLOBAL_CC) main.o $(GROUP_LIBS) -Os -Wl,--gc-sections -mmcu=$(MMCU) -lm -o $(PROG).elf


mega-dbg: GLOBAL_CC=avr-gcc
mega-dbg: GLOBAL_CFLAGS+=$(ARDUINO_FLAGS) $(DEBUG_FLAGS)
mega-dbg:
	cd sched/src && $(MAKE) mega
	cd stab/src && $(MAKE) mega
	cd moto/src && $(MAKE) mega



clean:
	cd sched/src && $(MAKE) clean
	cd sched/lib && rm *.a
	cd stab/src && $(MAKE) clean
	cd stab/lib && rm *.a
	cd moto/src && $(MAKE) clean
	cd moto/lib && rm *.a
	rm $(PROG) *.o *.map

	

.PHONY: lib