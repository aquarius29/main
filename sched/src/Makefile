PROG=prog
SRC=sched_naive_main.c sched_naive_sched.c sched_naive_sched.h sched_stubs.c sched_stubs.h


pc:
	gcc $(SRC) -o $(PROG) -DPC

# "pc-debug" make will compile with gcc and set the DEBUG and PC flag
pc-debug:
	gcc $(SRC) -o $(PROG) -DDEBUG -DPC -pedantic
    
clean:
	rm -f $(PROG) $(PROG).exe $(PROG).o *.lst
