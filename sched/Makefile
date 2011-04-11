
DEBUG_FLAGS=-g -DDEBUG
PC_FLAGS=-DPC
ARDUINO_FLAGS=-DARDUINO

# EXTRA_FLAGS defines what groups code to use instead of stubs
EXTRA_FLAGS=-DSTAB

export CFLAGS
export CC

OBJS=sched.o

BIN:$(OBJS)


pc: CC=gcc
pc: CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS)
pc:
	cd src && $(MAKE) pc
	

pc-debug: CC=gcc
pc-debug: CFLAGS+=$(PC_FLAGS) $(DEBUG_FLAGS) $(EXTRA_FLAGS)
pc-debug:
	cd src && $(MAKE) pc-debug


ardu: CC=avr-gcc
ardu: CFLAGS+=$(ARDUINO_FLAGS)
ardu:
	cd src && $(MAKE) ardu

normal:
	cd src && $(MAKE) normal

clean:
	cd src && $(MAKE) clean

windows-normal:
	cd src && $(MAKE) windows-normal

windows-clean:
	cd src && $(MAKE) windows-clean