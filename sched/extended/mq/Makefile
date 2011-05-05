CC=gcc
FLAGS= -Wall -g
SRC= src/mq.c
OBJ= mq.o
PROG=mq
LIB_OUT=lib/libmq.a
INC= -I./include

mq.o: 
	$(CC) $(INC) $(FLAGS) -c $(SRC) -o $@

lib: $(OBJ)
	ar rcs $(LIB_OUT) $(OBJ)
clean: 
	-rm $(LIB_OUT) *~ *.out $(OBJ)