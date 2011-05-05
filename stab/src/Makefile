# CC and CFLAGS are defined in higher level Makefile

PROG=stab
SRC=stab_main.c stab_filter.c stab_gyro_sim.c stab_ra.c stab_rg.c

stab_main.c: stab.h stab_sched.h
stab_filter.c: stab.h
stab_gyro_sim.c: stab.h
stab_ra.c: stab.h
stab_rg.c: stab.h


$(PROG): $(SRC)

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c -I. $*.c $(CFLAGS)


lib: $(OBJ)
	ar rvs ../lib/libstab.a $(OBJ)


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
