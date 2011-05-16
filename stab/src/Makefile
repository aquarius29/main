<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
########################### Added by Adam 09/05/11 #########################

LIB_SRC=read_mg.c stab_filter.c stab_main.c stab_ra.c stab_rb.c stab_rg.c stab_sim.c
=======
########################### Added by jogr 110413 #########################

LIB_SRC=stab_main.c stab_filter.c stab_ra.c stab_rg.c stab_sim.c
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
########################### Added by jogr 110413 #########################

LIB_SRC=stab_main.c stab_filter.c stab_ra.c stab_rg.c stab_sim.c
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
########################### Added by Adam 09/05/11 #########################

LIB_SRC=read_mg.c stab_filter.c stab_main.c stab_ra.c stab_rb.c stab_rg.c stab_sim.c
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93

LIB_OBJ = $(LIB_SRC:.c=.o)

%.o: %.c
	$(GLOBAL_CC) -c -I. $*.c $(GLOBAL_CFLAGS)

lib-pc: $(LIB_OBJ)
	ar rvs ../lib/libstab.a $(LIB_OBJ)
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93

lib-mega: $(LIB_OBJ)
	@echo Objects: $(LIB_OBJ)
	avr-ar rvs ../lib/libstab.a $(LIB_OBJ)

clean:
	rm -f *.o

<<<<<<< HEAD
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
	
lib-mega: $(LIB_OBJ)
	@echo Objects: $(LIB_OBJ)
	avr-ar rvs ../lib/libstab.a $(LIB_OBJ)
	
clean:
	rm -f *.o
	
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
##########################################################################






<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
# #######################################################################
# Makefile for inclusion by other projects
#   heavily copied from original libarduino sources
#   (c) 2009, for all changes belong to Henrik Sandklef
#	which lead to the current version
#	(c) 2011, for all changes belong to Petre Mihail Anton
#######################################################################

#     Change device names to corespond to your system
#  Description
#  =============
#    DUE_USB_DEV - used for Arduino DueMillaNove
#    UNO_USB_DEV - used for Arduino Uno
#
# here are various USB device names for various operating system and Arduinos:
# if you're using GNU/Linux (Ubuntu/Debian/Fedora.....):
#	DUE_USB_DEV=/dev/ttyUSB0
#	UNO_USB_DEV=/dev/ttyACM0
# if you're using Mac:
#	DUE_USB_DEV=
#	UNO_USB_DEV=/dev/tty.usbmodemfa141 (check name!)
# Hint:
#    Launch the Arduino program to see what your USB device 
#    is called (look under the port settings)
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

=======
                                                                                  
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
                                                                                  
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======

>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
#USB_PORT=/dev/ttyACM0
USB_PORT=/dev/tty.usbmodem411

#########################################################################
#########################################################################
#########################################################################

# the speed that corresponds to your arduino (normally 16MHz)
#F_CPU=16000000
#F_CPU=8000000

#PROG=prog
#OBJ=bin/*.o

#mega: MMCU=atmega2560
#mega: STK=stk500v2
#mega: BAUD=115200
#mega: LIB=coremega

#uno: MMCU=atmega328p
#uno: STK=stk500v1
#uno: BAUD=115200
#uno: LIB=coreuno

#	echo '#include "WProgram.h"' > $(TARGET).c
#	cat $(PROG).c >> $(TARGET).c

#$(OBJ): $(SRC)
#	cd bin && \
#	avr-gcc -c -g -Os -ffunction-sections -fdata-sections -mmcu=$(MMCU) -DARDUINO=22 -DF_CPU=$(F_CPU) -Wall -Wstrict-prototypes \
#		-Wa,-ahlms=$(PROG).lst -fno-exceptions -I../include ../$(SRC)

##-DENABLE_PWM

#$(PROG): MMCU=atmega328p
#$(PROG): LIB=coreuno
#$(PROG): $(OBJ)
#	avr-gcc $(OBJ) lib/lib$(LIB).a -Wl,-Map=$(PROG).map,--cref -mmcu=$(MMCU) -DARDUINO=22 -Iinclude -lm -Llib \
#		-fno-exceptions  -ffunction-sections -fdata-sections -l$(LIB) -o bin/$(PROG).x
#	@ echo "Test passed"

#install: $(OBJ)
#	avr-gcc $(OBJ) lib/lib$(LIB).a -Wl,-Map=$(PROG).map,--cref -mmcu=$(MMCU) -Iinclude -lm -Llib \
#		-fno-exceptions  -ffunction-sections -fdata-sections -l$(LIB) -o bin/$(PROG).elf
#	cd bin && avr-objcopy -O srec $(PROG).elf $(PROG).rom
##	checksize $(PROG).elf
#	avrdude -p $(MMCU) -P $(USB_PORT) -c $(STK) -b $(BAUD) -F -u -U flash:w:bin/$(PROG).rom


#mega: clean install

#uno: clean install

#pc: clean
#	gcc -DPC $(SRC) -o bin/$(PROG).x

#clean:
#	@ cd bin && rm -f *.o *.rom *.elf *.map *~ *.lst *.x
#	@ echo "Project cleaned"
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

=======
	
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
	
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======

>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
#help:
#	@ echo "Check your code includes 'WProgram.h' \nCheck you call 'init()'"

## reprogram the fuses for the right clock source
##fuse:
##	avrdude -p atmega168 -c stk200 -U lfuse:w:0x62:m
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

.PHONY : clean uno due mega install help lib

=======
# CC and CFLAGS are defined in higher level Makefile

PROG=stab
SRC=stab_main.c stab_filter.c stab_gyro_sim.c stab_ra.c stab_rg.c

stab_main.c: stab.h stab_sched.h
stab_filter.c: stab.h
stab_gyro_sim.c: stab.h
stab_ra.c: stab.h
stab_rg.c: stab.h


$(PROG): $(SRC)

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c -I. $*.c $(CFLAGS)


lib: $(OBJ)
	ar rvs ../lib/libstab.a $(OBJ)


pc: $(OBJ)
	@echo OBJ: $(OBJ)
	#$(CC) $(SRC) -o $(PROG) $(CFLAGS)

pc-debug:
	$(CC) $(SRC) -o $(PROG) $(CFLAGS)


# "ardu" will compile for the Arduino boards
ardu:
	$(CC) $(SRC) -o $(PROG) $(CFLAGS)

    
clean:
	rm -f $(PROG) $(PROG).exe *.o *.lst
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
	
.PHONY : clean uno due mega install help lib
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
	
.PHONY : clean uno due mega install help lib
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======

.PHONY : clean uno due mega install help lib

>>>>>>> ed2040bde53af04e22ec8814834f2a56f8ff6a93
