########################### Added by Adam 09/05/11 #########################

##LIB_SRC=nav_dijk.c nav_gps_nav.c nav_main.c nav_indoorastar.c nav_indoordijkstra.c nav_indoornavigation.c nav_movementcommands.c nav_tilemap.c nav_tmxparser.c ##nav_parser.c nav_pn.c nav_serial.c 

LIB_SRC=nav_pn.c nav_serial.c nav_indoordijkstra.c nav_indoorastar.c nav_gps_parser.c nav_gps_nav.c nav_indoornavigation.c nav_tmxparser.c nav_tilemap.c nav_movementcommands.c nav_outdoor_dijkstra.c nav_handlemanualcommands.c nav_corelogic.c

LIB_OBJ = $(LIB_SRC:.c=.o)

%.o: %.c
	$(GLOBAL_CC) -c -I. $*.c $(GLOBAL_CFLAGS)

lib-pc: $(LIB_OBJ)
	ar rvs ../lib/libnav.a $(LIB_OBJ)

lib-panda: $(LIB_OBJ)
		ar rvs ../lib/libnav.a $(LIB_OBJ)

lib-mega: $(LIB_OBJ)
	@echo Objects: $(LIB_OBJ)
	avr-ar rvs ../lib/libnav.a $(LIB_OBJ)

clean:
	rm -f *.o

##########################################################################

