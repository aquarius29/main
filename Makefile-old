#############################################################################
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
##  2011-04-13 - Created this file
##
##  2011-04-15 - Started work to merge with the arduino-flasher makefile
##
##  2011-04-18 - Merged with the makefile written by Eugene and Mihail,
##				 creating libs and linking with libcoremega and then 
##				 uploading to the mega-board now works. Also merged the
##				 makefile that worked with PC targets. Added "Usage" part
##				 in comments.
##
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
BASIC_LIBS=-Lstab/lib -Lsched/lib -Lmoto/lib -Lmov/lib -Lca/lib -Lproto/lib -Llib -lsched -lstab -lmoto -lmov -lca -lproto -lm

##  Set paths to headers used by code on the basic system
BASIC_INCLUDES=-I../../stab/src -I../../moto/src -I../../mov/src -I../../ca/src -I../../proto_mega/src -I../../include

##  Free of charge
EXTRA_FLAGS=

##  Name of micro controller
MMCU=atmega2560

##  Specify what "corelib" to be linked, "coremega" or "coreuno" depending on board
CORE_LIB=coremega

##  cpu speed
F_CPU=16000000

##  Name of programmer
STK=stk500v2

##  Baud rate
BAUD=115200

##  These flags are exported to be used in lower level makefiles
export GLOBAL_CFLAGS
export GLOBAL_CC

##  PC specific flags
PC_FLAGS=-DPC

##  Debug flags for PC
DEBUG_FLAGS_PC=-g -DDEBUG -Wall

##  Arduino specific flags
ARDUINO_FLAGS=-Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MMCU) -DARDUINO=22 -DF_CPU=$(F_CPU)

##  Debug flags for Arduino
DEBUG_FLAGS_ARDUINO=-g -DDEBUG

##  Linker flags for Arduino
LDFLAGS_ARDUINO=-Os -Wl,--gc-sections -mmcu=$(MMCU) -lm


## pc-targets ###############################################################
pc: GLOBAL_CC=gcc
pc: GLOBAL_CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) $(BASIC_INCLUDES)
pc:
	cd sched/src && $(MAKE) lib-pc
	cd stab/src && $(MAKE) lib-pc
	cd moto/src && $(MAKE) lib-pc
	cd mov/src && $(MAKE) lib-pc
	cd ca/src && $(MAKE) lib-pc
	cd proto/src && $(MAKE) lib-pc
	$(GLOBAL_CC) -c main.c -Isched/src
	$(GLOBAL_CC) -o $(PROG) main.o $(BASIC_LIBS)
	

pc-dbg: GLOBAL_CC=gcc
pc-dbg: GLOBAL_CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) $(DEBUG_FLAGS_PC) $(BASIC_INCLUDES)
pc-dbg:
	cd sched/src && $(MAKE) lib-pc
	cd stab/src && $(MAKE) lib-pc
	cd moto/src && $(MAKE) lib-pc
	cd mov/src && $(MAKE) lib-pc
	cd ca/src && $(MAKE) lib-pc
	cd proto/src && $(MAKE) lib-pc
	$(GLOBAL_CC) -c main.c -Isched/src
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

	cd ca/src && $(MAKE) lib-mega
	avr-ranlib ca/lib/libca.a	

	cd proto/src && $(MAKE) lib-mega
	avr-ranlib proto/lib/libproto.a	

	$(GLOBAL_CC) -c main.c -Isched/src
	$(GLOBAL_CC) main.o $(BASIC_LIBS) $(LDFLAGS_ARDUINO) -o $(PROG).elf
	avr-objcopy -O srec $(PROG).elf $(PROG).rom


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

	cd proto/src && $(MAKE) lib-mega
	avr-ranlib proto/lib/libproto.a	

	$(GLOBAL_CC) -c main.c -Isched/src
	$(GLOBAL_CC) main.o $(BASIC_LIBS) $(LDFLAGS_ARDUINO) -o $(PROG).elf
	avr-objcopy -O srec $(PROG).elf $(PROG).rom
	
	
## panda-targets ############################################################
panda:

panda-dbg:


## n900-targets #############################################################
n900:

n900-dbg:


## ui-targets ###############################################################
ui:

ui-dbg:


## flash-target #############################################################
flash:
	avrdude -p $(MMCU) -P $(USB_PORT) -c $(STK) -b $(BAUD) -F -u -U flash:w:$(PROG).rom


## clean-target #############################################################
clean:
	cd sched/src && $(MAKE) clean
	cd sched/lib && rm *.a

	cd stab/src && $(MAKE) clean
	cd stab/lib && rm *.a

	cd moto/src && $(MAKE) clean
	cd moto/lib && rm *.a

	cd mov/src && $(MAKE) clean
	cd mov/lib && rm *.a

	cd ca/src && $(MAKE) clean
	cd ca/lib && rm *.a

	cd proto/src && $(MAKE) clean
	cd proto/lib && rm *.a

	rm -f $(PROG) $(PROG).elf $(PROG).rom *.o *.map

	

.PHONY: pc pc-dbg mega mega-dbg panda panda-dbg n900 n900-dbg ui ui-dbg flash clean