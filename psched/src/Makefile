########################### Added by jogr 110413 #########################
LIB_SRC= extsched_sm.c psched_mq.c sched_ext_mngr.c 

LIB_OBJ = $(LIB_SRC:.c=.o)

GLOBAL_CC = gcc

%.o: %.c
	$(GLOBAL_CC) -c -I. $*.c $(GLOBAL_CFLAGS)

lib-pc: $(LIB_OBJ)
	ar rvs ../lib/libpsched.a $(LIB_OBJ)
	
lib-mega: $(LIB_OBJ)
	@echo Objects: $(LIB_OBJ)
	avr-ar rvs ../lib/libpsched.a $(LIB_OBJ)
	
clean:
	rm -f *.o ../lib/*.a example_usage *~

example: $(LIB_OBJ)
	gcc -o example_usage -lpsched -L../lib example_usage.c

##########################################################################

