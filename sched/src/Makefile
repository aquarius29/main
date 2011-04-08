PROG=prog
SRC=sched_naive_main.c sched_naive_sched.c sched_stubs.c


pc:
	gcc $(SRC) -o $(PROG) -DPC

# "pc-debug" make will compile with gcc and set the DEBUG and PC flag
pc-debug:
	gcc $(SRC) -o $(PROG) -DDEBUG -DPC -DSTAB -pedantic
    
clean:
	rm -f $(PROG) $(PROG).exe *.o *.lst
