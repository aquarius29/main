PROG = sched_ext_mngr
CC=gcc
FLAGS= -Wall -g -I./include -I./sm/include -L./sm/lib -c #-I./mq/include -c -L./mq/lib -lm
SRC= src/$(PROG).c include/$(PROG).h
OBJ= $(PROG).o
LIB_OUT=lib/libextsched.a 

$(OBJ): $(SRC)
	$(CC) $(FLAGS) $(SRC)

sm: 
	cd sm && make && make lib

lib: $(OBJ)
	ar rcs $(LIB_OUT) $(OBJ)

clean: 
	-rm $(LIB_OUT) *~ *.out $(OBJ) 

