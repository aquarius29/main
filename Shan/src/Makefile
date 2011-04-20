# 
#  Makefile for Abstract Navigation's src directory
# 
#  Created on: 10 apr 2011
#      Author: Shan Huang
# 

nav: indoor_navigation.c path_data.c path_structure.h main.c
	gcc -o nav indoor_navigation.c path_data.c main.c $(EXTRAGCCFLAGS)

testobjsu: indoor_navigation.c path_data.c path_structure.h 
	gcc -o nav.o -c indoor_navigation.c path_data.c $(EXTRAGCCFLAGS)

testobjsg: EXTRAGCCFLAGS+= -fprofile-arcs -ftest-coverage
testobjsg: testobjsv

testobjsv: EXTRAGCCFLAGS+= -g
testobjsv: testobjsv

clean:
	rm -f nav nav.exe nav.o *.gcov *.gcda *.gcno
