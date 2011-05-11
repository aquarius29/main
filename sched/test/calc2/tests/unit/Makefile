SRCPATH = ../../src
SRCOBJS = $(wildcard $(SRCPATH)/*.o)
TESTSRCS = $(wildcard *.c)

unit: testsuite
	@echo Running tests...
	./testsuite

gcovunit: EXTRAGCCFLAGS+= -fprofile-arcs -ftest-coverage
gcovunit: unit
	gcov testsuite
	cd $(SRCPATH) && gcov calc.c

gcovunitb: EXTRAGCCFLAGS+= -fprofile-arcs -ftest-coverage
gcovunitb: unit
	gcov -b -c testsuite
	cd $(SRCPATH) && gcov -b -c calc.c

memunit: EXTRAGCCFLAGS+= -g
memunit: testsuite
	@echo Running tests under valgrind...
	valgrind --leak-check=full ./testsuite 

testsuite.o: $(TESTSRCS)
	gcc -c unitmain.c -o testsuite.o $(EXTRAGCCFLAGS)

testsuite: $(SRCOBJS) testsuite.o
	gcc $(SRCOBJS) testsuite.o -o testsuite $(EXTRAGCCFLAGS) -lcunit 

clean:
	rm -f testsuite testsuite.exe testsuite.o *.gcov *.gcda *.gcno

