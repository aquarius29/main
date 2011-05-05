# CC and CFLAGS are defined in higher level Makefile

PROG=moto
SRC=moto_driver_functions.c moto_interface.c moto_msg_handler.c moto_msg_manipulation.c

moto_driver_functions.c: moto_driver_functions.h
moto_interface.c: moto_interface.h moto_state_definitions.h
moto_msg_handler.c: moto_msg_handler.c
moto_msg_manipulation.c: moto_msg_manipulation.c

$(PROG): $(SRC)

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c -I. $*.c $(CFLAGS)


lib: $(OBJ)
	ar rvs ../lib/libmoto.a $(OBJ)


pc: $(OBJ)
	@echo OBJ: $(OBJ)
	#$(CC) $(SRC) -o $(PROG) $(CFLAGS)

pc-debug:
	$(CC) $(SRC) -o $(PROG) $(CFLAGS)


# "ardu" will compile for the Arduino boards
ardu:
	$(CC) $(SRC) -o $(PROG) $(CFLAGS)

    
clean:
	rm -f $(PROG) $(PROG).exe *.o *.lst
