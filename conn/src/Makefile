########################### Added by Adam 09/05/11 #########################

LIB_SRC=conn_tcpserver.c conn_tcpserver_main.c conn_ui_mask.c   

LIB_OBJ = $(LIB_SRC:.c=.o)

%.o: %.c
	$(GLOBAL_CC) -c -I. $*.c $(GLOBAL_CFLAGS)

lib-pc: $(LIB_OBJ)
	ar rvs ../lib/libconn.a $(LIB_OBJ)

lib-panda: $(LIB_OBJ)
	ar rvs ../lib/libconn.a $(LIB_OBJ)

lib-mega: $(LIB_OBJ)
	@echo Objects: $(LIB_OBJ)
	avr-ar rvs ../lib/libconn.a $(LIB_OBJ)

clean:
	rm -f *.o

##########################################################################
