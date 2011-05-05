# 
#  Makefile for Abstract Navigation's src directory
# 
#  Created on: 10 apr 2011
#      Author: Shan Huang
# 

indoor: indoor_algorithms.h indoor_astar.c indoor_dijkstra.c indoor_navigation.c tilemap.h tilemap.c path_structure.h tmxparser.c
	gcc -o indoor -I/usr/include/libxml2 -lxml2 indoor_astar.c indoor_dijkstra.c indoor_navigation.c tilemap.c tmxparser.c $(EXTRAGCCFLAGS)

testobjs: indoor_algorithms.h indoor_astar.c indoor_dijkstra.c indoor_navigation.c path_structure.h tilemap.h tilemap.c tmxparser.c 
	gcc -o indoor_navigation.o -c indoor_navigation.c $(EXTRAGCCFLAGS)
	gcc -o indoor_astar.o -c indoor_astar.c $(EXTRAGCCFLAGS)
	gcc -o indoor_dijkstra.o -c indoor_dijkstra.c $(EXTRAGCCFLAGS)
	gcc -o tilemap.o -c tilemap.c $(EXTRAGCCFLAGS)
	gcc -o tmxparser.o -I/usr/include/libxml2 -lxml2 -c tmxparser.c  $(EXTRAGCCFLAGS)

testobjsv: EXTRAGCCFLAGS+= -g
testobjsv: testobjs

clean:
	rm -f indoor indoor.exe indoor.o *.gcov *.gcda *.gcno