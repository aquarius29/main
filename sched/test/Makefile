SRCDIR=../src/arduino/robin_impl_src
SRC=$(SRCDIR)/sched_scheduler.c  $(SRCDIR)/sched_stubs.c 
TESTSRC=test_scheduler_h.c $(SRC)

default:
	@echo "--- test Robin compilation ----------------------------"
	@echo "make test    runs test suite"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean   clean up test"

test:
	gcc -o test $(TESTSRC) -lcunit

clean:
	rm -r test.exe
