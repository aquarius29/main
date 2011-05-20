CUNIT_PROG=testsuite
SCHED_PROG=scheduler
SRCDIR=../src
SRC=$(SRCDIR)/sched_batman_scheduler.c $(SRCDIR)/sched_stubs.c -DPC -DCUNIT
CUNIT=test_scheduler_h.c $(SRC)
RUN=run_scheduler.c $(SRC) -DLOG $(SRCDIR)/sched_batman_main.c

default:
	@echo "--- test batman compilation -----------------------------"
	@echo "make test    runs test suite"
	@echo " "
	@echo "--- test scheudler  -------------------------------------"
	@echo "make sched-run  makes a simulated scheduler"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean   clean up test"

test:
	gcc -o $(CUNIT_PROG) $(CUNIT) -I../src -lcunit

sched-run:
	gcc -o $(SCHED_PROG) $(RUN) -I../src

clean:
	rm -f $(CUNIT_PROG).exe $(CUNIT_PROG).elf $(CUNIT_PROG) $(SCHED_PROG).elf $(SCHED_PROG).exe $(SCHED_PROG) scheduler_log.txt
