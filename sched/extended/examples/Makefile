##########################################################
#							 #
# Extended scheduler Makefile. Im blue badadi dabadai... #
#							 #
##########################################################

PROG= example_usage
CC= gcc 
CCFLAGS= -g -I../include -I../sm/include -L../lib -L../sm/lib
LIBS= -lsm -lextsched #for messageq queue:-lmq -lextsched
OBJ= $(PROG).o
SRC= example_usage.c

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CCFLAGS) -c $(SRC)

install: clean $(OBJ) 
	$(CC) $(OBJ) $(CCFLAGS) $(LIBS) -o $(PROG)

clean: 
	-rm -fr *.o $(PROG) *~