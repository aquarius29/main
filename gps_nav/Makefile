BIN=outdoor_nav
SRC=gps_nav.c dijk.c pn.c serial.c parser.c


$(BIN): $(SRC) 
	gcc $(SRC) -o $(BIN) -lm

clean:
	rm -f $(BIN)  


