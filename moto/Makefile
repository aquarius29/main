# #####################################################################
# This makefile has been modified from the original version to better
# suit the motor control group.
# 
# Changes include targets for:
# - default (just gives a nice printout with instructions)
#   (Kristofer Hansson Aspman)
# - valgrind (Kristofer Hansson Aspman)
# - gcov (...coverage) (Kristofer Hansson Aspman)
# - CUnit master test suite (Kristofer Hansson Aspman and Björn Eriksson)
#
# In addition to this the following targets have been altered by
# Kristofer Hansson Aspman, Björn Eriksson and Magnus Bergqvist:
# - mega
# - pc
# #####################################################################
# Makefile for inclusion by other projects
#   heavily copied from original libarduino sources
#   (c) 2009, for all changes belong to Henrik Sandklef
#	which lead to the current version
#	(c) 2011, for all changes belong to Petre Mihail Anton
#######################################################################

#     Change device names to corespond to your system
#
# here are various USB device names for various operating system and Arduinos:
# if you're using GNU/Linux (Ubuntu/Debian/Fedora.....):
#	UUSB_PORT=/dev/ttyACM0
# if you're using Mac:
#	USB_PORT=/dev/tty.usbmodemfa141 (check name!)
# Hint:
#    Launch the Arduino program to see what your USB device 
#    is called (look under the port settings)


USB_PORT=/dev/ttyACM0
#USB_PORT=/dev/tty.usbmodem411

#########################################################################
#########################################################################
#########################################################################

# the speed that corresponds to your arduino (normally 16MHz)
F_CPU=16000000
#F_CPU=8000000

VERS="Arduino Portable Makefile [APM] version 1.2, dated 10-04-2011"

PROG=test
TESTNAME=test_suite
SRC=src/*.c
SRC2=include/*.cpp
PROTO_SRC=../proto_mega/src/*.c
CUNIT_SRC=test/cunit_master_test_suite.c test/cunit_moto_msg_handler.h test/cunit_moto_msg_handler.c test/cunit_moto_driver_functions.c
OBJ=bin/*.o
TESTSUITE_OBJ=bin/test_suite.o

default:
	@echo "--- Normal compilation ----------------------------------"
	@echo "make pc     produces binary in bin/"
	@echo "make mega   produces binary for the Arduino and uploads"
	@echo "            to the board"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean    recursively clean up subdirs"
	@echo " "
	@echo "--- Verification and debugging --------------------------"
	@echo "make test         compiles unit tests"
	@echo "make gcov         run unit tests with gcov (statement coverage)"
	@echo "make gcov2        run unit tests with gcov (branch coverage)"
	@echo "make valgrind     run unit tests with valgrind"
	@echo " "

mega: MMCU=atmega2560
mega: STK=stk500v2
mega: BAUD=115200
mega: LIB=coremega
mega: EXT=elf

uno: MMCU=atmega328p
uno: STK=stk500v1
uno: BAUD=115200
uno: LIB=coreuno
uno: EXT=elf

test: MMCU=atmega328p
test: LIB=coreuno
test: EXT=x

$(OBJ): $(SRC)

	@ cd bin && \
	avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MMCU) -DARDUINO_DBG=22 -DF_CPU=$(F_CPU) -DARDUINO_DBG=22 -I../../include ../$(SRC) ../$(SRC2) ../$(PROTO_SRC)
	@ echo "Object files created"

compile:
	@ avr-gcc $(OBJ) -Os -Wl,--gc-sections -mmcu=$(MMCU) -o bin/$(PROG).$(EXT) -l$(LIB) -Llib -lm
	@ echo "Project compiled"

#-DENABLE_PWM
# avr-gcc $(OBJ) -Os -Wl,-Map=$(PROG).map,--cref -mmcu=$(MMCU) -DARDUINO=22 -l$(LIB) -Llib -lm \
#		-fno-exceptions  -ffunction-sections -fdata-sections -o bin/$(PROG).x


test: clean
	gcc -DPC -DMASTER_TEST_SUITE $(CUNIT_SRC) $(SRC) $(PROTO_SRC) -o bin/$(TESTNAME).o -lcunit

install: $(OBJ) compile
	@ cd bin && avr-objcopy -O srec $(PROG).elf $(PROG).rom
#	checksize $(PROG).elf
	@ avrdude -p $(MMCU) -P $(USB_PORT) -c $(STK) -b $(BAUD) -F -u -U flash:w:bin/$(PROG).rom


mega: clean install

uno: clean install

pc: clean
	gcc -DPC $(SRC) $(PROTO_SRC) -o bin/$(PROG).o

valgrind: clean
	gcc -g -DPC $(SRC) $(PROTO_SRC) -o bin/$(PROG).o
	@ echo "Run with valgrind --leak-check=yes bin/test.o"

gcov: clean
	gcc -lgcov -fprofile-arcs -ftest-coverage -DPC -DMASTER_TEST_SUITE -DAUTOMATED $(CUNIT_SRC) $(SRC) $(PROTO_SRC) -o bin/$(TESTNAME).o -lcunit
	@ echo "Compiled for gcov, now running testsuite..."
#	rm -fr ./gcov_output
#	mkdir ./gcov_output
#	pwd
#	cd gcov_output/ && pwd && ./../bin/test_suite.o
#	pwd
	$(TESTSUITE_OBJ)
	@ echo "After exec testsuite"
	gcov src/*.c
	rm -fr ./gcov_out
	mkdir ./gcov_out
	mv *.gcov gcov_out/
#	lcov  --directory ./covs --zerocounters 
#	lcov  --directory ./ --directory ./bin --directory ./src --directory ./../proto_mega/src/ --capture --output-file ./covs/stap.info
#	genhtml -o covs/ covs/stap.info
	@ echo ".gcov-files created in src-folder"

gcov2: clean
	gcc -lgcov -fprofile-arcs -ftest-coverage -DPC -DMASTER_TEST_SUITE -DAUTOMATED $(CUNIT_SRC) $(SRC) $(PROTO_SRC) -o bin/$(TESTNAME).o -lcunit
#	gcc -fprofile-arcs -ftest-coverage -DPC $(SRC) $(PROTO_SRC) -o bin/$(PROG).o
	@ echo "Compiled for gcov, now running testsuite..."
	$(TESTSUITE_OBJ)
	@ echo "After exec testsuite"
	gcov -b -c src/*.c
	@ echo ".gcov-files created in src-folder"

clean:
	@ cd bin && rm -f *.o *.rom *.elf *.map *~ *.lst *.o ../src/*.gcov \
	../*.gcno ../*.gcov ../*.gcda ../../proto_mega/bin/*.o \
	../../../mov/bin/*.o ../../../ca/bin/*.o ../../main.o
	@ echo "Project cleaned"

version:
	@ echo $(VERS)

help:
	@ echo "Check: \n	- the declared usb port\n	- if all required folders exist\n	- if your code includes 'WProgram.h'\n	- if you call 'init()'\n	- try removing '@' from this makefile to get more output"

# reprogram the fuses for the right clock source
#fuse:
#	avrdude -p atmega168 -c stk200 -U lfuse:w:0x62:m

.PHONY : clean compile test uno mega pc install help version
