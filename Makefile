#############################################################################
##  Makefile for use in the project root directory.
##  The purpose is to have one makefile to build the whole system
##  using flags that gets exported and invoke lower level makefiles
##  on a group level.
##
##  Author:	Joakim
##  Date: 	2011-04-15
##
##  History:
##  2011-04-13 - Created this file
##
##  2011-04-15 - Started work to merge with the arduino-flasher makefile
##
##  2011-04-18 - Merged with the makefile written by Eugene and Mihail,
##				 creating libs and linking with libcoremega and then 
##				 uploading to the mega-board now works.
##
##  Notes:
##  This needs to be merged with the makefile on the branch that
##  works for PC. All flags, targets and variables that are supposed to
##  make up the template part decided by TINT needs to be fixed in a 
##  nice way.
#############################################################################

##  Set name of usb-port
USB_PORT=/dev/tty.usbmodemfa141

##  Set name of micro controller
MMCU=atmega2560

F_CPU=16000000

STK=stk500v2
BAUD=115200
CORE_LIB=coremega

##  These flags are exported to be used in lower level makefiles
export GLOBAL_CFLAGS
export GLOBAL_CC

##  Linker flags for Arduino:
LDFLAGS_ARDUINO=-Os -Wl,--gc-sections -mmcu=$(MMCU)

##  Debug flags for PC:
DEBUG_FLAGS_PC=-g -DDEBUG -Wall

##  Debug flags for Arduino:
DEBUG_FLAGS_ARDUINO=-g -DDEBUG

##  PC specific flags:
PC_FLAGS=-DPC

##  Arduino specific flags:
ARDUINO_FLAGS=-Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MMCU) -DARDUINO=22 -DF_CPU=$(F_CPU)

##  Libraries to include, only include libs that work for all targets here!
LIBS=-Lstab/lib -Lsched/lib -Lmoto/lib -Llib -lsched -lstab -lmoto -lm

# Set paths to headers
INCLUDES=-I../../stab/src -I../../moto/src -I../../include

# EXTRA_FLAGS defines what groups code to use instead of stubs
EXTRA_FLAGS=

# PROG is the name of the executable
PROG=prog


pc: GLOBAL_CC=gcc
pc: GLOBAL_CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) $(INCLUDES)
pc:
	cd sched/src && $(MAKE) lib-pc
	cd stab/src && $(MAKE) lib-pc
	cd moto/src && $(MAKE) lib-pc
	$(GLOBAL_CC) -c main.c -Isched/src
	$(GLOBAL_CC) -o $(PROG) main.o $(LIBS)
	

pc-dbg: GLOBAL_CC=gcc
pc-dbg: GLOBAL_CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) $(DEBUG_FLAGS_PC) $(INCLUDES)
pc-dbg:
	cd sched/src && $(MAKE) lib-pc
	cd stab/src && $(MAKE) lib-pc
	cd moto/src && $(MAKE) lib-pc
	$(GLOBAL_CC) -c main.c -Isched/src
	$(GLOBAL_CC) -o $(PROG) main.o $(LIBS)


mega: LIBS+=-l$(CORE_LIB)
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
	$(GLOBAL_CC) main.o $(LIBS) $(LDFLAGS_ARDUINO) -o $(PROG).elf
	avr-objcopy -O srec $(PROG).elf $(PROG).rom


mega.dbg: LIBS+=-l$(CORE_LIB)
mega-dbg: GLOBAL_CC=avr-g++
mega-dbg: GLOBAL_CFLAGS+=$(ARDUINO_FLAGS) $(EXTRA_FLAGS) $(INCLUDES) $(DEBUG_FLAGS_ARDUINO)
mega-dbg:
	cd sched/src && $(MAKE) lib-mega
	avr-ranlib sched/lib/libsched.a
	
	cd stab/src && $(MAKE) lib-mega
	avr-ranlib stab/lib/libstab.a
	
	cd moto/src && $(MAKE) lib-mega
	avr-ranlib moto/lib/libmoto.a	
	
	$(GLOBAL_CC) -c main.c -Isched/src
	$(GLOBAL_CC) main.o $(LIBS) $(LDFLAGS_ARDUINO) -o $(PROG).elf
	avr-objcopy -O srec $(PROG).elf $(PROG).rom
	

panda:

panda-dbg:

n900:

n900-dbg:

ui:

ui-dbg:

flash:
	avrdude -p $(MMCU) -P $(USB_PORT) -c $(STK) -b $(BAUD) -F -u -U flash:w:$(PROG).rom

clean:
	cd sched/src && $(MAKE) clean
	cd sched/lib && rm *.a
	cd stab/src && $(MAKE) clean
	cd stab/lib && rm *.a
	cd moto/src && $(MAKE) clean
	cd moto/lib && rm *.a
	rm -f $(PROG) $(PROG).elf $(PROG).rom *.o *.map

	

.PHONY: lib