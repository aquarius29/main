PROG=stab
SRC=stab_main.c stab_rg.c stab_ra.c stab_gyro_sim.c stab_filter.c stab.h stab_sched.h 


pc:
	gcc $(SRC) -lm -o $(PROG) -DPC

# "pc-debug" make will compile with gcc and set the DEBUG and PC flag
pc-debug:
	gcc $(SRC) -o $(PROG) -DDEBUG -DPC
    
clean:
	rm -f $(PROG) $(PROG).o *.lst *.o
