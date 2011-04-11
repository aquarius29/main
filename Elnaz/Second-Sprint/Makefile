##########################################################
#
#make file for generating the protocol library 
#
########################################################
#  cd $(PATH) && \
#PATH=Core

compile:
	@ cd $(PATH) && \
	$(C) -c *.c && \
	$(AR) rcs libproto.a *.o && \
	rm *.o
	@ echo "Library created" 
  

pc: C=gcc
pc: AR=ar
pc: compile


arduino: C=avr-gcc
arduino: AR=avr-ar
arduino: compile
