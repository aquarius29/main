<<<<<<< HEAD
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
=======
#############################################################
#
#	Makefile for generating the Protocol library for Mega
#       Created By Elnaz Shahmehr and Mihail Anton
#
#############################################################

CODE_PATH=src/

pc: C=gcc
pc: AR=ar
pc: CFLAG=-DPC 
pc: compile
	
arduino: C=avr-gcc
arduino: AR=avr-ar
arduino: CFLAG=-DARDUINO
arduino: compile

compile: clean
	cd $(CODE_PATH) && \
	$(C) -c *.c $(CFLAG) && \
	$(AR) rcs ../libproto.a *.o  && \
	echo "Library created"

test:
	cd /proto/test/test_ca && \
	make unit
	cd /proto/test/test_move && \
	make unit

clean:
	@ rm -f *.a $(CODE_PATH)*.o

.PHONY: compile clean pc arduino test
.SILENT: compile
>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
