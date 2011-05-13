# 
#  Makefile for Abstract Navigation's test/unit directory
# 
#  Amanpreet
#      
# 

SRCPATH = ../src
SRCOBJS = $(wildcard $(SRCPATH)/*.o)
TESTSRCS = $(wildcard *.c)

default:
	@echo " "
	@echo "--- Verification and debugging --------------------------"
	@echo "make unit         run unit tests"
	@echo "make gcovunit     run unit tests with gcov (statement coverage)"
	@echo "make gcovunitb    run unit tests with gcov (branch coverage)"
	@echo "make memunit      run unit tests with valgrind"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean    recursively clean up subdirs"
	@echo " "

unit: testsuite
	@echo Running tests...
	./testsuite

gcovunit: EXTRAGCCFLAGS+= -fprofile-arcs -ftest-coverage
gcovunit: unit
	gcov testsuite
	gcov ca_filters.cs

gcovunitb: EXTRAGCCFLAGS+= -fprofile-arcs -ftest-coverage
gcovunitb: unit
	gcov -b -c testsuite
	gcov -b -c ca_filters.c

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
