INCL = libarduino.h irkeys.h timercountercalcs.h
SRC = libarduino.c 
OBJ = $(SRC:.c=.o)
LIB=libarduino.a

include ../build/arduino.mk.in

CFLAGS= -I../include -g -Os -Wall -Wstrict-prototypes  -mmcu=$(CPU) -DF_CPU=$(F_CPU) -DENABLE_PWM 



# compile .c into .o
%.o: %.c
	avr-gcc -c $(CFLAGS) -I. $*.c 

$(LIB): $(OBJ)
	avr-ar r    $(LIB) libarduino.o
	avr-ranlib  $(LIB)

lib: $(LIB)

install-lib:
	@echo " ==== install-lib: implemented later on"