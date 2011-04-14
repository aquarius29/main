#############################################################
#
#	Makefile for generating the Protocol library
#
#############################################################

CODE_PATH=Core/

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

.PHONY: compile clean pc arduino
.SILENT: compile
