SRCPATH = ../src
SRCOBJS = $(wildcard $(SRCPATH)/*.o)
TESTSRCS = $(wildcard *.c)

unit: testsuite
	@echo Running tests...
	./testsuite

testsuite.o: $(TESTSRCS)
	gcc -c unitmain.c -o testsuite.o $(ECTRAGCCFLAGS) -I../src -I/usr/local/include

testsuite: $(SRCOBJS) testsuite.o
	gcc $(SRCOBJS) testsuite.o -o testsuite $(EXTRAGCCFLAGS) -L../lib -lcunit -lsm -lextsched


clean:
	rm -f testsuite testsuite.exe testsuite.o

