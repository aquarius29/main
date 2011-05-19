PROG=testsuite
SRCDIR=../src
SRC=$(SRCDIR)/sched_batman_scheduler.c $(SRCDIR)/sched_stubs.c -DPC -DCUNIT
TESTSRC=test_scheduler_h.c $(SRC)

default:
	@echo "--- test batman compilation -----------------------------"
	@echo "make test    runs test suite"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean   clean up test"

test:
	gcc -o $(PROG) $(TESTSRC) -I../src -lcunit

clean:
	rm -f $(PROG).exe $(PROG).elf $(PROG)
