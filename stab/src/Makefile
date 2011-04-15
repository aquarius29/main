# GLOBAL_CC and GLOBAL_CFLAGS are defined in higher level Makefile

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
	$(GLOBAL_CC) -c -I. $*.c $(GLOBAL_CFLAGS)


lib: $(OBJ)
	ar rvs ../lib/libstab.a $(OBJ)


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
