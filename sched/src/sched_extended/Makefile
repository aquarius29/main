##########################################################
#							 #
# Extended scheduler Makefile. Im blue badadi dabadai... #
#							 #
##########################################################

PROG= fork
CC= gcc 
CCFLAGS= -Wall -c  
OBJ= $(PROG).o
SRC= $(PROG).c

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CCFLAGS) $(SRC)

install: $(OBJ) 
	$(CC) $(OBJ) -o $(PROG)

clean: 
	-rm -fr *.o $(PROG) *~