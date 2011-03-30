INCL = include/libarduino.h include/irkeys.h include/timercountercalcs.h
SRC  = src/libarduino.c 
SRC_MAKEFILE = src/Makefile
LIB  = src/libarduino.a
INSTALL_PATH = /opt/libarduino
LIBARDUINO_MAKEFILE = build/arduino.mk
EXAMPLES_DIR = examples
EXAMPLE_MAKEFILE = $(EXAMPLES_DIR)/Makefile
TAR_FILENAME = libarduino

lib: $(LIB)

all: lib

check: $(LIB)
	cd examples && PROG=adctemperatureexample    make clean all && \
	PROG=adcexample               make clean all && rm -f adcexample && \
	PROG=adctoledpwm              make clean all && rm -f adctoledpwm && \
	PROG=irandadcexample          make clean all && rm -f irandadcexample && \
	PROG=irandserialexample       make clean all && rm -f irandserialexample && \
	PROG=pwmofledexample          make clean all && rm -f pwmofledexample && \
	PROG=readbuttonoutputled      make clean all && rm -f readbuttonoutputled && \
	PROG=serialandpwmservoexample make clean all && rm -f serialandpwmservoexample && \
	echo " " && \
	echo " If you see this text libarduino built ok :) " && \
	echo " " 

check-hw:
	cd examples && make check

clean:
	cd src      && make clean
	-rm -f *~
	-rm -f  build/*~ $(LIBARDUINO_MAKEFILE) $(EXAMPLE_MAKEFILE)
	-rm -f src/*.o src/*.a
	-rm -f examples/*.a examples/*.o examples/*.map examples/*.elf  examples/*.rom examples/*.lst




$(LIB): $(SRC) $(LIBARDUINO_MAKEFILE) $(EXAMPLE_MAKEFILE)
	cd src && make lib


$(LIBARDUINO_MAKEFILE): $(LIBARDUINO_MAKEFILE).in
	echo "*** Creating libarduino user makefile from $(LIBARDUINO_MAKEFILE).in"
	cat $(LIBARDUINO_MAKEFILE).in | sed "s,__INSTALL_PATH__,$(INSTALL_PATH),g" > $(LIBARDUINO_MAKEFILE)

$(EXAMPLE_MAKEFILE): $(EXAMPLE_MAKEFILE).in
	echo "*** Creating example makefile from $(EXAMPLE_MAKEFILE).in"
	cat $(EXAMPLE_MAKEFILE).in | sed -e "s,__INSTALL_PATH__,$(INSTALL_PATH),g" -e "s,__LIBARDUINO_MAKEFILE__,$(LIBARDUINO_MAKEFILE),g" > $(EXAMPLE_MAKEFILE)


install: $(LIB)	
	@if [ -d $(INSTALL_PATH) ]; then echo " " && echo "*** $(INSTALL_PATH) exists, please delete the folder and try again... ***" && echo " " ; exit 1; fi;

	@echo "[+] Creating $(INSTALL_PATH)...";
	@mkdir -p $(INSTALL_PATH)
	@mkdir -p $(INSTALL_PATH)/include
	@cp include/*.h $(INSTALL_PATH)/include

	@echo "[+] Creating $(INSTALL_PATH)/lib...";
	@mkdir -p $(INSTALL_PATH)/lib
	@cp $(LIB) $(INSTALL_PATH)/lib

	@echo "[+] Creating $(INSTALL_PATH)/bin...";
	@mkdir -p $(INSTALL_PATH)/bin
	@cp bin/checksize $(INSTALL_PATH)/bin

	@echo "[+] Creating $(INSTALL_PATH)/build...";
	@mkdir -p $(INSTALL_PATH)/build
	@cp $(LIBARDUINO_MAKEFILE) $(INSTALL_PATH)/$(LIBARDUINO_MAKEFILE)

	@echo "[+] Creating $(INSTALL_PATH)/examples...";
	@mkdir -p $(INSTALL_PATH)/examples
	@cp $(EXAMPLE_MAKEFILE) $(INSTALL_PATH)/examples
	@cp $(EXAMPLES_DIR)/test.c $(INSTALL_PATH)/examples/
	@cp Makefile.out $(INSTALL_PATH)/Makefile

	@echo "[+] Creating $(INSTALL_PATH)/src...";
	@mkdir $(INSTALL_PATH)/src
	@cp $(SRC) $(INSTALL_PATH)/$(SRC)
	@cp $(LIB) $(INSTALL_PATH)/$(LIB)
	@cat $(SRC_MAKEFILE) | sed -e "s,$(LIBARDUINO_MAKEFILE).in,$(LIBARDUINO_MAKEFILE),g" > $(INSTALL_PATH)/$(SRC_MAKEFILE)

	@echo " " && \
	echo "*** Library is now installed in $(INSTALL_PATH) ***" && \
	echo " "

dist: 
	@make clean
	#@echo "Compress to filename: "
	#@read TAR_FILENAME
	@echo "[+] Creating $(TAR_FILENAME)..."
	#exit 1;
	
	make $(LIBARDUINO_MAKEFILE) $(EXAMPLE_MAKEFILE)
	-rm -f $(TAR_FILENAME)
	tar cvf  $(TAR_FILENAME).tar src $(INCL) Makefile $(LIBARDUINO_MAKEFILE).in $(EXAMPLE_MAKEFILE).in  examples/*.c  bin/checksize
	gzip $(TAR_FILENAME).tar
	@echo "Done..."