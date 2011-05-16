<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
# #######################################################################
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
<<<<<<< HEAD
<<<<<<< HEAD

#USB_PORT=$(MYUSB)
#/dev/ttyACM2
USB_PORT=/dev/ttyACM0
=======
                                                                                  
USB_PORT=/dev/ttyACM0
#USB_PORT=/dev/tty.usbmodem411
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
                                                                                  
USB_PORT=/dev/ttyACM0
#USB_PORT=/dev/tty.usbmodem411
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

#########################################################################
#########################################################################
#########################################################################

# the speed that corresponds to your arduino (normally 16MHz)
F_CPU=16000000
#F_CPU=8000000

VERS="Arduino Portable Makefile [APM] version 1.2, dated 10-04-2011"

PROG=test
SRC=src/*.c
OBJ=src/*.o

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

# -Wstrict-prototypes
#-Wa,-ahlms=$(PROG).lst
$(OBJ): $(SRC)
<<<<<<< HEAD
<<<<<<< HEAD
	@ cd src && \
	avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MMCU) -DARDUINO=22 -DF_CPU=$(F_CPU) -DARDUINO=22 -I../../include ../$(SRC)
	@ echo "Object files created"

compile:
	@ avr-gcc $(OBJ) -Os -Wl,--gc-sections -mmcu=$(MMCU) -o src/$(PROG).$(EXT) -l$(LIB) -Llib -lm
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

	@ cd bin && \
	avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MMCU) -DARDUINO_DBG=22 -DF_CPU=$(F_CPU) -DARDUINO_DBG=22 -I../../include ../$(SRC)
	@ echo "Object files created"

compile:
	@ avr-gcc $(OBJ) -Os -Wl,--gc-sections -mmcu=$(MMCU) -o bin/$(PROG).$(EXT) -l$(LIB) -Llib -lm
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
	@ echo "Project compiled"

#-DENABLE_PWM
# avr-gcc $(OBJ) -Os -Wl,-Map=$(PROG).map,--cref -mmcu=$(MMCU) -DARDUINO=22 -l$(LIB) -Llib -lm \
<<<<<<< HEAD
<<<<<<< HEAD
#		-fno-exceptions  -ffunction-sections -fdata-sections -o src/$(PROG).x
=======
#		-fno-exceptions  -ffunction-sections -fdata-sections -o bin/$(PROG).x
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
#		-fno-exceptions  -ffunction-sections -fdata-sections -o bin/$(PROG).x
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

test: clean $(OBJ) compile
	@ echo "Test passed"

install: $(OBJ) compile
<<<<<<< HEAD
<<<<<<< HEAD
	@ cd src && avr-objcopy -O srec $(PROG).elf $(PROG).rom
#	checksize $(PROG).elf
	@ avrdude -p $(MMCU) -P $(USB_PORT) -c $(STK) -b $(BAUD) -F -u -U flash:w:src/$(PROG).rom
#	@ avrdude -p $(MMCU) -c $(STK) -b $(BAUD) -F -u -U flash:w:src/$(PROG).rom	
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
	@ cd bin && avr-objcopy -O srec $(PROG).elf $(PROG).rom
#	checksize $(PROG).elf
	@ avrdude -p $(MMCU) -P $(USB_PORT) -c $(STK) -b $(BAUD) -F -u -U flash:w:bin/$(PROG).rom

<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

mega: clean install

uno: clean install

pc: clean
	gcc -lm -DPC $(SRC) -o src/$(PROG).x


clean:
	@ cd src && rm -f *.o *.rom *.elf *.map *~ *.lst *.x
	@ echo "Project cleaned"
<<<<<<< HEAD
<<<<<<< HEAD

=======
	
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
	
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
version:
	@ echo $(VERS)

help:
	@ echo "Check: \n	- the declared usb port\n	- if all required folders exist\n	- if your code includes 'WProgram.h'\n	- if you call 'init()'\n	- try removing '@' from this makefile to get more output"

# reprogram the fuses for the right clock source
#fuse:
#	avrdude -p atmega168 -c stk200 -U lfuse:w:0x62:m

.PHONY : clean compile test uno mega pc install help version
<<<<<<< HEAD
<<<<<<< HEAD
=======
PROG=stab
SRC=stab_main.c stab_rg.c stab_ra.c stab_gyro_sim.c stab_filter.c stab.h stab_sched.h main.c


pc:
	gcc $(SRC) -lm -o $(PROG) -DPC

# "pc-debug" make will compile with gcc and set the DEBUG and PC flag
pc-debug:
	gcc $(SRC) -o $(PROG) -DDEBUG -DPC
    
clean:
	rm -f $(PROG) $(PROG).o *.lst *.o
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
