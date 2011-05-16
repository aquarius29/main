########################### Added by Adam 09/05/11 #########################

LIB_SRC=nav_gps_nav.c nav_corelogic.c nav_indoorastar.c nav_indoordijkstra.c nav_indoornavigation.c nav_movementcommands.c nav_tilemap.c nav_tmxparser.c nav_pn.c nav_serial.c nav_gps_parser.c nav_outdoor_dijkstra.c

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

