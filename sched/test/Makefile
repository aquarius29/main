SRCDIR=../src/arduino/batman_impl
SRC=$(SRCDIR)/sched_scheduler.c  $(SRCDIR)/sched_stubs.c 
TESTSRC=test_scheduler_h.c $(SRC)

default:
	@echo "--- test batman compilation -----------------------------"
	@echo "make test    runs test suite"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean   clean up test"

test:
	gcc -o test $(TESTSRC) -lcunit

clean:
	rm -r test.exe
