
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


MMCU=atmega2560
STK=stk500v2
BAUD=115200
LIB=coremega

mega: CC=avr-g++
mega: CFLAGS+=$(ARDUINO_FLAGS) $(EXTRA_FLAGS) $(INCLUDES)
mega:
	cd sched/src && $(MAKE) lib-mega
	avr-ranlib sched/lib/libsched.a
	
	cd stab/src && $(MAKE) lib-mega
	avr-ranlib stab/lib/libstab.a
	
	cd moto/src && $(MAKE) lib-mega
	avr-ranlib moto/lib/libmoto.a	
	
	$(CC) -c main.c -Isched/src
	$(CC) main.o $(GROUP_LIBS) -Wl,-Map=$(PROG).map,--cref -mmcu=$(MMCU) -Iinclude -lm -fno-exceptions  -ffunction-sections -fdata-sections -o $(PROG).elf


mega-dbg: CC=avr-gcc
mega-dbg: CFLAGS+=$(ARDUINO_FLAGS) $(DEBUG_FLAGS)
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
	rm $(PROG) *.o

	

.PHONY: lib