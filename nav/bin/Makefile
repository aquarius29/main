# 
#  Makefile for Abstract Navigation's src directory
# 
#  Created on: 10 apr 2011
#      Author: Shan Huang
# 

indoor: ../src/nav_indooralgorithms.h ../src/nav_indoorastar.c ../src/nav_indoordijkstra.c ../src/nav_indoornavigation.c ../src/tilemap.h ../src/tilemap.c ../src/nav_indoorstructure.h ../src/tmxparser.c
	gcc -o indoor -I/usr/include/libxml2 -lxml2 ../src/nav_indoorastar.c ../src/nav_indoordijkstra.c ../src/nav_indoornavigation.c ../src/tilemap.c ../src/tmxparser.c $(EXTRAGCCFLAGS)

testobjs: ../src/nav_indooralgorithms.h ../src/nav_indoorastar.c ../src/nav_indoordijkstra.c ../src/nav_indoornavigation.c ../src/tilemap.h ../src/tilemap.c ../src/nav_indoorstructure.h ../src/tmxparser.c
	gcc -o indoor_navigation.o -c ../src/nav_indoornavigation.c $(EXTRAGCCFLAGS)
	gcc -o indoor_astar.o -c ../src/nav_indoorastar.c $(EXTRAGCCFLAGS)
	gcc -o indoor_dijkstra.o -c ../src/nav_indoordijkstra.c $(EXTRAGCCFLAGS)
	gcc -o tilemap.o -c ../src/tilemap.c $(EXTRAGCCFLAGS)
	gcc -o tmxparser.o -I/usr/include/libxml2 -lxml2 -c ../src/tmxparser.c  $(EXTRAGCCFLAGS)

testobjsv: EXTRAGCCFLAGS+= -g
testobjsv: testobjs

clean:
	rm -f indoor indoor.exe indoor.o *.o *.gcov *.gcda *.gcno