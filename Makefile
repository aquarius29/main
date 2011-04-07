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

compile:
	cd $(CODE_PATH) && \
	$(C) -c *.c $(CFLAG) && \
	$(AR) rcs ../libproto.a *.o  && \
	rm *.o
	@ echo "Library created"

.PHONY: compile clean pc arduino
.SILENT: compile
