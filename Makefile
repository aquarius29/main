
DEBUG_FLAGS=-g -DDEBUG
PC_FLAGS=-DPC
ARDUINO_FLAGS=-DARDUINO

# INCLUDES holds paths to other groups headers
INCLUDES=../../stab/src

# EXTRA_FLAGS defines what groups code to use instead of stubs
EXTRA_FLAGS=-DSTAB

# PROG is the name of the executable
PROG=prog

export CFLAGS
export CC

BIN:$(OBJS)


# just calling this target "lib" does not work!
# do i have some other makefile with a "lib" target on a path or something???
lib: CC=gcc
lib: CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) $(DEBUG_FLAGS) -I$(INCLUDES)
lib:
	cd sched/src && $(MAKE) lib
	cd stab/src && $(MAKE) lib
	gcc -c main.c -Isched/src
	gcc -o $(PROG) main.o -Lstab/lib -Lsched/lib -lsched -lstab


pc: CC=gcc
pc: CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) -I$(INCLUDES)
pc:
	cd sched/src && $(MAKE) pc
	

pc-debug: CC=gcc
pc-debug: CFLAGS+=$(PC_FLAGS) $(DEBUG_FLAGS) $(EXTRA_FLAGS)
pc-debug:
	cd sched/src && $(MAKE) pc-debug


ardu: CC=avr-gcc
ardu: CFLAGS+=$(ARDUINO_FLAGS)
ardu:
	cd sched/src && $(MAKE) ardu

normal:
	cd sched/src && $(MAKE) normal

clean:
	rm $(PROG) *.o
	cd sched/src && $(MAKE) clean
	cd stab/src && $(MAKE) clean

windows-normal:
	cd src && $(MAKE) windows-normal

windows-clean:
	cd src && $(MAKE) windows-clean
	
.PHONY: lib