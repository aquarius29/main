
DEBUG_FLAGS=-g -DDEBUG -Wall
PC_FLAGS=-DPC
ARDUINO_FLAGS=
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


mega: CC=avr-gcc
mega: CFLAGS+=$(ARDUINO_FLAGS) $(EXTRA_FLAGS) $(INCLUDES)
mega:
	cd sched/src && $(MAKE) lib-mega
	#cd stab/src && $(MAKE) mega
	#cd moto/src && $(MAKE) mega


mega-dbg: CC=avr-gcc
mega-dbg: CFLAGS+=$(ARDUINO_FLAGS) $(DEBUG_FLAGS)
mega-dbg:
	cd sched/src && $(MAKE) mega
	cd stab/src && $(MAKE) mega
	cd moto/src && $(MAKE) mega



clean:
	rm $(PROG) *.o
	cd sched/src && $(MAKE) clean
	cd stab/src && $(MAKE) clean
	cd moto/src && $(MAKSE) clean

	

.PHONY: lib