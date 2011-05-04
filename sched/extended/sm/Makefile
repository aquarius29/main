#
# EXTSCHED_SM - IPC Based Shared memory Library.
# 
# INSTALL: 
#    make && make lib 
#    dont forget to clean after the mess.
#

CC=gcc
FLAGS= -Wall -g
SRC= src/extsched_sm.c
OBJ= extsched_sm.o
PROG=extsched_sm
LIB_OUT=lib/libsm.a
INC= -I./include -I../include

$(OBJ): $(SRC) 
	$(CC) $(INC) $(FLAGS) -c $(SRC) -o $@

lib: $(OBJ)
	ar rcs $(LIB_OUT) $(OBJ)
clean: 
	-rm $(LIB_OUT) *~ *.out $(OBJ) $(PROG)