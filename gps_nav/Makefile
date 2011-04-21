BIN=outdoor_nav
SRC=gps_nav.c dijk.c pn.c serial.c parser.c threadTest.c


$(BIN): $(SRC) 
	gcc $(SRC) -o $(BIN) -lm -lpthread

clean:
	rm -f $(BIN)  


