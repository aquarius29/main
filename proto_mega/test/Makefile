<<<<<<< HEAD
SRCPATH = ../../test
SRCOBJS = $(wildcard $(SRCPATH)/*.o)
TESTSRCS = $(wildcard *.c)

test: testsuite
	@echo Running tests...
	./testsuite

testsuite.o: $(TESTSRCS)
	gcc -c test_proto.c -o testsuite.o $(ECTRAGCCFLAGS)

testsuite: $(SRCOBJS) testsuite.o
	gcc $(SRCOBJS) testsuite.o -o testsuite $(EXTRAGCCFLAGS) -lcunit


clean:
	rm -f testsuite testsuite.exe testsuite.o

=======
SRCPATH = ../../test
SRCOBJS = $(wildcard $(SRCPATH)/*.o)
TESTSRCS = $(wildcard *.c)

test: testsuite
	@echo Running tests...
	./testsuite

testsuite.o: $(TESTSRCS)
	gcc -c test_proto.c -o testsuite.o $(ECTRAGCCFLAGS)

testsuite: $(SRCOBJS) testsuite.o
	gcc $(SRCOBJS) testsuite.o -o testsuite $(EXTRAGCCFLAGS) -lcunit


clean:
	rm -f testsuite testsuite.exe testsuite.o

>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
