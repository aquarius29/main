# 
#  Makefile for Abstract Navigation's src directory
# 
#  Created on: 10 apr 2011
#      Author: Shan Huang
# 

<<<<<<< HEAD
# indoor: ../src/nav_indooralgorithms.h ../src/nav_indoorastar.c ../src/nav_indoordijkstra.c ../src/nav_indoornavigation.c ../src/nav_tilemap.h ../src/nav_tilemap.c ../src/nav_indoorstructure.h ../src/nav_tmxparser.c ../src/nav_handlemanualcommands.h ../src/nav_handlemanualcommands.c
#   gcc -o indoor -I/usr/include/libxml2 -lxml2 ../src/nav_indoorastar.c ../src/nav_indoordijkstra.c ../src/nav_indoornavigation.c ../src/nav_tilemap.c ../src/nav_tmxparser.c ../src/nav_handlemanualcommands.c $(EXTRAGCCFLAGS)
# 
# testobjs: ../src/nav_indooralgorithms.h ../src/nav_indoorastar.c ../src/nav_indoordijkstra.c ../src/nav_indoornavigation.c ../src/nav_tilemap.h ../src/nav_tilemap.c ../src/nav_indoorstructure.h ../src/nav_tmxparser.c ../src/nav_handlemanualcommands.h ../src/nav_handlemanualcommands.c
#   gcc -o indoor_navigation.o -c ../src/nav_indoornavigation.c $(EXTRAGCCFLAGS)
#   gcc -o indoor_astar.o -c ../src/nav_indoorastar.c $(EXTRAGCCFLAGS)
#   gcc -o indoor_dijkstra.o -c ../src/nav_indoordijkstra.c $(EXTRAGCCFLAGS)
#   gcc -o tilemap.o -c ../src/nav_tilemap.c $(EXTRAGCCFLAGS)
#   gcc -o tmxparser.o -I/usr/include/libxml2 -lxml2 -c ../src/nav_tmxparser.c  $(EXTRAGCCFLAGS)
#   gcc -o manual.o -c ../src/nav_handlemanualcommands.c $(EXTRAGCCFLAGS)


indoor: ../src/nav_indooralgorithms.h ../src/nav_indoorastar.c ../src/nav_indoordijkstra.c ../src/nav_indoornavigation.c ../src/nav_tilemap.h ../src/nav_tilemap.c ../src/nav_indoorstructure.h ../src/nav_tmxparser.c 
	gcc -o indoor -I/usr/include/libxml2 -lxml2 ../src/nav_indoorastar.c ../src/nav_indoordijkstra.c ../src/nav_indoornavigation.c ../src/nav_tilemap.c ../src/nav_tmxparser.c $(EXTRAGCCFLAGS)
=======

simulation: ../src/*.h ../src/*.c
	gcc -o simulation -I/usr/include/libxml2 -lxml2 ../src/*.c $(EXTRAGCCFLAGS)
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

testobjs: ../src/nav_indooralgorithms.h ../src/nav_indoorastar.c ../src/nav_indoordijkstra.c ../src/nav_indoornavigation.c ../src/nav_tilemap.h ../src/nav_tilemap.c ../src/nav_indoorstructure.h ../src/nav_tmxparser.c 
	gcc -o indoor_navigation.o -c ../src/nav_indoornavigation.c $(EXTRAGCCFLAGS)
	gcc -o indoor_astar.o -c ../src/nav_indoorastar.c $(EXTRAGCCFLAGS)
	gcc -o indoor_dijkstra.o -c ../src/nav_indoordijkstra.c $(EXTRAGCCFLAGS)
	gcc -o tilemap.o -c ../src/nav_tilemap.c $(EXTRAGCCFLAGS)
	gcc -o tmxparser.o -I/usr/include/libxml2 -lxml2 -c ../src/nav_tmxparser.c $(EXTRAGCCFLAGS)

testobjsv: EXTRAGCCFLAGS+= -g
testobjsv: testobjs

clean:
<<<<<<< HEAD
	rm -f indoor indoor.exe indoor.o *.o *.gcov *.gcda *.gcno
=======
	rm -f simulation simulation.exe simulation.o *.o *.gcov *.gcda *.gcno
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
