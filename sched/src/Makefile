<<<<<<< HEAD
PROG=sched_loop
SRC=$(PROG).c sched_loop.h sched_stubs.c sched_stubs.h
=======
PROG=scheduler
SRC=$(PROG).c scheduler.c scheduler.h stubs.c stubs.h
>>>>>>> bbd5f5e5a0a6f77389c0f626c53b430cc4ddb8e7

# modify according to the device file under /dev, /dev/tty.usbmodemNNN under mac for example.                                                                                   
DUE_USB_DEV=/dev/ttyUSB0
UNO_USB_DEV=/dev/tty.usbmodemfa141

# modify if the libarduino directory is different than what's below.
LIBARDUINO_PATH=/opt/libarduino

# change to $(AVRDUDE_DUE) if necessary.
AVRDUDE=$(AVRDUDE_UNO) 

include /opt/libarduino/build/arduino.mk

# "normal" make will compile with gcc and set the DEBUG flag
normal:
	gcc $(SRC) -o $(PROG) -DDEBUG
<<<<<<< HEAD
    
=======
    
clean:
	rm -f $(PROG) $(PROG).exe $(PROG).o

windows-normal:
	cl /Fe$(PROG) *.c

windows-clean:
	del *.obj $(PROG).exe
>>>>>>> bbd5f5e5a0a6f77389c0f626c53b430cc4ddb8e7
