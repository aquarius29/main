LIB_SRC = src/moto_driver_functions.c src/moto_interface.c src/moto_msg_handler.c src/moto_msg_manipulation.c
INCLUDE = -I../../sched/proto/src -I src
SRC = src/*.c
OBJ = *.o

clean:
	rm -rf bin/*
	rm -rf lib/*
	rm -rf *.o *.a *.x
	
compile: clean
	gcc $(LIB_SRC) $(INCLUDE) -DPC -c

pc: 
	gcc -DPC src/main.c -I src -Llib -l moto -o bin/main.x
	
lib: $(OBJ)
	ar rvs lib/libmoto.a $(OBJ)