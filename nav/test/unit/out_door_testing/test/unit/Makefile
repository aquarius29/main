# 
#  Makefile for Abstract Navigation's test/unit directory
# 
#  Amanpreet
#      
# 

BINPATH = ../../src/outdoor
SRCOBJS = $(wildcard $(BINPATH)/*.o)
TESTSRCS = $(wildcard *.c)

unit: testsuite
	@echo Running tests...
	./testsuite

valg: EXTRAGCCFLAGS+= -g
valg: testsuite
	@echo Running tests under valgrind...
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./testsuite

testsuite.o: $(TESTSRCS)
	gcc -I/usr/include/lm -c unitmain.c -o testsuite.o $(EXTRAGCCFLAGS)

testsuite: $(SRCOBJS) testsuite.o
	gcc -I/usr/include/lm $(SRCOBJS) testsuite.o -o testsuite $(EXTRAGCCFLAGS) -lcunit 

clean:
	rm -f testsuite testsuite.exe testsuite.o *.gcov *.gcda *.gcno