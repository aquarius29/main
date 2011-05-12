#   Make file

#created on:9th may 2011
#Author: Amanpreet Kaur
#
oudoor: nav_gps_nav.c nav_gps_nav.h nav_gps_parser.c nav_gps_parser.h nav_outdoor_dijkstra.c nav_outdoor_dijkstra.h nav_pn.h nav_serial.c nav_outdoor_structure.h nav_pn.c nav_serial.h nav_pn.o
	gcc -o outdoor -I/usr/include/lm nav_gps_nav.c nav_gps_nav.h nav_gps_parser.c nav_gps_parser.h nav_outdoor_dijkstra.c nav_outdoor_dijkstra.h nav_pn.h nav_serial.c nav_outdoor_structure.h nav_pn.c nav_serial.h nav_pn.o $(EXTRAGCCFLAGS)

testobjs: nav_gps_nav.c nav_gps_nav.h nav_gps_parser.c nav_gps_parser.h nav_outdoor_dijkstra.c nav_outdoor_dijkstra.h nav_pn.h nav_serial.c nav_outdoor_structure.h nav_pn.c nav_serial.h  
	gcc -o nav_pn.o -I/usr/include/lm -c nav_pn.c $(EXTRAGCCFLAGS)
	gcc -o nav_serial.o -c nav_serial.c $(EXTRAGCCFLAGS)
	gcc -o nav_outdoor_dijkstra.o -c nav_outdoor_dijkstra.c $(EXTRAGCCFLAGS)
	gcc -o nav_gps_nav.o -c nav_gps_nav.c $(EXTRAGCCFLAGS)
	gcc -o nav_gps_parser.o -c nav_gps_parser.c  $(EXTRAGCCFLAGS)

testobjsv: EXTRAGCCFLAGS+= -g
testobjsv: testobjs

clean:
	rm -f outdoor outdoor.exe outdoor.o *.gcov *.gcda *.gcno 