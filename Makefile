#############################################################
#
#	Makefile for generating the Protocol library
#
#############################################################

CODE_PATH=Core/

compile:
	cd $(CODE_PATH) && \
	$(C) -c *.c -DPC && \
	$(AR) rcs ../libproto.a *.o  && \
	rm *.o
	@ echo "Library created"

pc: C=gcc
pc: AR=ar
pc: compile
	
arduino: C=avr-gcc
arduino: AR=avr-ar
arduino: compile

.PHONY: compile clean pc arduino
.SILENT: compile
