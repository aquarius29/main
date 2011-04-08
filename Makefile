BIN=prog
#OBJS=stab/src/stab.h stab/src/stab_filter.o stab/src/stab_gyro_sim.o stab/src/stab_main.o stab/src/stab_ra.o stab/src/stab_rg.o sched/src/sched_naive_main.o sched/src/sched_naive_sched.o sched/src/sched_naive_sched.h sched/src/sched_stubs.o sched/src/sched_stubs.h
OBJS=stab/src/stab_filter.o stab/src/stab_gyro_sim.o stab/src/stab_main.o stab/src/stab_ra.o stab/src/stab_rg.o sched/src/sched_naive_main.o sched/src/sched_naive_sched.o sched/src/sched_stubs.o



CC=gcc
CFLAGS= -DPC -DSTAB -DDEBUG

$(BIN): $(OBJS)

    
clean:
	rm -f $(BIN) $(BIN).exe $(BIN).o *.lst

$(BIN): $(OBJS)
	gcc $(OBJS) -o $(BIN)