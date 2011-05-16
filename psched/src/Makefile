########################### Added by jogr 110413 #########################
<<<<<<< HEAD

LIB_SRC= extsched_sm.c sched_ext_mngr.c
=======
LIB_SRC= extsched_sm.c psched_mq.c sched_ext_mngr.c 
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04

LIB_OBJ = $(LIB_SRC:.c=.o)

GLOBAL_CC = gcc

%.o: %.c
	$(GLOBAL_CC) -c -I. $*.c $(GLOBAL_CFLAGS)

lib-pc: $(LIB_OBJ)
	ar rvs ../lib/libpsched.a $(LIB_OBJ)
<<<<<<< HEAD

lib-panda: $(LIB_OBJ)
	ar rvs ../lib/libpsched.a $(LIB_OBJ)

lib-mega: $(LIB_OBJ)
	@echo Objects: $(LIB_OBJ)
	avr-ar rvs ../lib/libpsched.a $(LIB_OBJ)

clean:
	rm -f *.o ../lib/*.a example_usage
=======
	
lib-mega: $(LIB_OBJ)
	@echo Objects: $(LIB_OBJ)
	avr-ar rvs ../lib/libpsched.a $(LIB_OBJ)
	
clean:
	rm -f *.o ../lib/*.a example_usage *~
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04

example: $(LIB_OBJ)
	gcc -o example_usage -lpsched -L../lib example_usage.c

##########################################################################

