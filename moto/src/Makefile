# GLOBAL_CC and GLOBAL_CFLAGS are defined in higher level Makefile

PROG=moto
SRC=moto_driver_functions.c moto_interface.c moto_msg_handler.c moto_msg_manipulation.c

moto_driver_functions.c: moto_driver_functions.h
moto_interface.c: moto_interface.h moto_state_definitions.h
moto_msg_handler.c: moto_msg_handler.c
moto_msg_manipulation.c: moto_msg_manipulation.c

$(PROG): $(SRC)

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(GLOBAL_CC) -c -I. $*.c $(GLOBAL_CFLAGS)


lib: $(OBJ)
	ar rvs ../lib/libmoto.a $(OBJ)


pc: $(OBJ)
	@echo OBJ: $(OBJ)
	#$(GLOBAL_CC) $(SRC) -o $(PROG) $(GLOBAL_CFLAGS)

pc-debug:
	$(GLOBAL_CC) $(SRC) -o $(PROG) $(GLOBAL_CFLAGS)


# "ardu" will compile for the Arduino boards
ardu:
	$(GLOBAL_CC) $(SRC) -o $(PROG) $(GLOBAL_CFLAGS)

    
clean:
	rm -f $(PROG) $(PROG).exe *.o *.lst
