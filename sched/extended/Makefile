##########################################################
#							 #
# Extended scheduler Makefile. Im blue badadi dabadai... #
#							 #
##########################################################

PROG= sched_ext_mngr
SRC_F= src
BIN_DIR=bin
CC= gcc 
CCFLAGS= -Wall -c  
OBJ = $(SRC_F)/$(PROG).o
SRC= $(SRC_F)/$(PROG).c
PROG_EXEC= $(BIN_DIR)/$(PROG)

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CCFLAGS) $(SRC) -o $(OBJ)

install: $(OBJ) 
	$(CC) $(OBJ) -o $(PROG_EXEC)

clean: 
	-rm -fr $(SRC_F)/*.o $(BIN_DIR)/$(PROG) src/*~

