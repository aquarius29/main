# GLOBAL_CC and GLOBAL_CFLAGS are defined in higher level Makefile

PROG=sched
SRC=sched_naive_main.c sched_naive_sched.c sched_stubs.c

sched_naive_main.c: sched_naive_sched.h sched_interface.h
sched_naive_sched.c: sched_naive_sched.h
sched_stubs.c: sched_stubs.h


$(PROG): $(SRC)

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(GLOBAL_CC) -c -I. $*.c $(GLOBAL_CFLAGS)


lib: $(OBJ)
	ar rvs ../lib/libsched.a $(OBJ)


pc: $(OBJ)
	@echo OBJ: $(OBJ)
	#$(GLOBAL_CC) $(SRC) -o $(PROG) $(GLOBAL_CFLAGS)

pc-debug:
	$(GLOBAL_CC) $(SRC) -o $(PROG) $(GLOBAL_CFLAGS)


# "ardu" will compile for the Arduino boards
ardu:
	$(GLOBAL_CC) $(SRC) -o $(PROG) $(GLOBAL_CFLAGS)

    
clean:
	rm -f $(PROG) $(PROG).exe *.o *.lst
