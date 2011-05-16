#############################################################
#
#	Makefile for generating the Protocol library for Mega
#       Created By Mihail Anton and Elnaz Shahmehr
#
#############################################################

CODE_PATH=src/

pc: C=gcc
pc: FILES=
pc: AR=ar
pc: CFLAG=-DPC
pc: compile
	
arduino: C=avr-gcc
arduino: FILES=
arduino: AR=avr-ar
arduino: CFLAG=-DARDUINO
arduino: compile

compile: clean
	cd $(CODE_PATH) && \
	$(C) -c *.c $(CFLAG) && \
	$(AR) rcs ../lib/libproto.a *.o  && \
	echo "Library created"

test:
	cd /proto/test/test_ca && \
	make unit
	cd /proto/test/test_move && \
	make unit
	
valgrind: 
	cd valgrind && \
	gcc motor.c stab.c test_old.c -L../lib -lproto -o test && \
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -v ./test

clean:
	@ rm -f *.a lib/*.a $(CODE_PATH)*.o valgrind/test

.PHONY: compile clean pc arduino test valgrind
.SILENT: compile valgrind
