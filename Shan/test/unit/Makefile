# 
#  Makefile for Abstract Navigation's test/unit directory
# 
#  Created on: 10 apr 2011
#      Author: Shan Huang
# 

SRCPATH = ../../src/indoor
SRCOBJS = $(wildcard $(SRCPATH)/*.o)
TESTSRCS = $(wildcard *.c)

unit: testsuite
	@echo Running tests...
	./testsuite

testsuite.o: $(TESTSRCS)
	gcc -c unitmain.c -o testsuite.o $(EXTRAGCCFLAGS)

testsuite: $(SRCOBJS) testsuite.o
	gcc $(SRCOBJS) testsuite.o -o testsuite $(EXTRAGCCFLAGS) -lcunit 

clean:
	rm -f testsuite testsuite.exe testsuite.o *.gcov *.gcda *.gcno