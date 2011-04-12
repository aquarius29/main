# CC and CFLAGS are defined in higher level Makefile

PROG=sched
SRC=sched_naive_main.c sched_naive_sched.c sched_stubs.c

sched_naive_sched.c: sched_naive_sched.h
sched_stubs.c: sched_stubs.h


$(PROG): $(SRC)

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c -I. $*.c $(CFLAGS)


lib: $(OBJ)
	ar rvs ../lib/libsched.a $(OBJ)


pc: $(OBJ)
	@echo OBJ: $(OBJ)
	#$(CC) $(SRC) -o $(PROG) $(CFLAGS)

pc-debug:
	$(CC) $(SRC) -o $(PROG) $(CFLAGS)


# "ardu" will compile for the Arduino boards
ardu:
	$(CC) $(SRC) -o $(PROG) $(CFLAGS)

    
clean:
	rm -f $(PROG) $(PROG).exe *.o *.lst
