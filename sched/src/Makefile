PROG=scheduler
SRC=sched_main.c sched_scheduler.c sched_scheduler.h sched_stubs.c sched_stubs.h

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
    
clean:
	rm -f $(PROG) $(PROG).exe $(PROG).o

windows_normal: $(PROG)
	cl /Fe..\..\..\$(PROG) *.c

windows_clean:
	del *.obj $(PROG).exe