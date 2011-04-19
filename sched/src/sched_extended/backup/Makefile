##########################################################
#							 #
# Extended scheduler Makefile. Im blue badadi dabadai... #
#							 #
##########################################################

PROG= sched_ext_mngr
CC= gcc 
CCFLAGS= -g -c  
OBJ= $(PROG).o
SRC= *.c

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CCFLAGS) $(SRC)

install: clean $(OBJ) 
	$(CC) $(OBJ) -o $(PROG)

clean: 
	-rm -fr *.o $(PROG) *~