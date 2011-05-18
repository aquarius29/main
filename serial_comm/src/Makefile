#############################################################################
## Makefile for source level to be used by root level makefile.
##
## Variables GLOBAL_CC and GLOBAL_CFLAGS are defined in root level makefile
## and must not be changed in this file.
##
## Source files for the various targets are listed on each respective
## LIB_SRC_<target> variable. Some of the files there are meant to be the
## same for more than one target, these files have their content ifdef:ed 
## to work for more than one target.
##
## Author: Joakim
## Date: 2011-05-16
##
#############################################################################

LIB_SRC_MEGA=	sched_stub.c 				\
				group_stub.c 				\
				serial_interface.c			\
				proto_usart_isr_mega.c 		\
				proto_stub.c 				\
				proto_serial_comm.c 		\
				proto_serializer.c 			\
				proto_deserializer.c 

LIB_SRC_PC=					\
				proto_serial_port.c 		\
				proto_serial_comm.c 		\
				proto_serializer.c 			\
				proto_deserializer.c

LIB_SRC_UNO=

LIB_OBJ_MEGA = $(LIB_SRC_MEGA:.c=.o)
LIB_OBJ_PC = $(LIB_SRC_PC:.c=.o)
LIB_OBJ_UNO = $(LIB_SRC_UNO:.c=.o)

%.o: %.c
	$(GLOBAL_CC) -c -I. $*.c $(GLOBAL_CFLAGS)

lib-pc: $(LIB_OBJ_PC)
	@echo Objects: $(LIB_OBJ_PC)
	ar rvs ../lib/libserial.a $(LIB_OBJ_PC)
	
## panda targets use the same files and flags as the pc target	
lib-panda: $(LIB_OBJ_PC)
	@echo Objects: $(LIB_OBJ_PC)
	ar rvs ../lib/libserial.a $(LIB_OBJ_PC)	
	
lib-mega: $(LIB_OBJ_MEGA)
	@echo Objects: $(LIB_OBJ_MEGA)
	avr-ar rvs ../lib/libserial.a $(LIB_OBJ_MEGA)
	
lib-uno: $(LIB_OBJ_UNO)
	@echo Objects: $(LIB_OBJ_UNO)
	avr-ar rvs ../lib/libserial.a $(LIB_OBJ_UNO)

clean:
	rm -f *.o
	
#############################################################################
