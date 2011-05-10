github github

    Pricing and Signup
    Explore GitHub
    Features
    Blog
    Login

SEMB2011 / stab

    Watch
    Fork
        6
        3

    Source
    Commits
    Network
    Pull Requests (0)
    Graphs
    Branch: master

    Switch Branches (1)
    Switch Tags (0)
    Branch List

Downloads

Repository for the 'Stabilization' group Ñ Read more

http://129.16.157.207/redmine/projects/emb2011

    HTTP
    Git Read-Only

This URL has Read-Only access

Added makefile in src that is needed for root makefile later and removed... 

Adam Debbiche (author)
1 day ago
commit  96115443298a257b7353
tree    97f21922cc5b83ad6164
parent  afecdaa4207d6b0c8c5e
stab / stab / src / Makefile
	name 	age 	
history
message
directory 	ca/ 	March 17, 2011 	Collision group folder added [JoGr]
directory 	cam/ 	March 17, 2011 	rest of the group folders added [JoGr]
directory 	conn/ 	March 17, 2011 	rest of the group folders added [JoGr]
directory 	include/ 	April 07, 2011 	Some extra header files [PeMiAn]
directory 	lib/ 	April 07, 2011 	New libs which include Wire, Serial, SPI and EEPRO... [PeMiAn]
directory 	libarduino/ 	April 05, 2011 	removed libarduino/examples/Makefile.in~ temp file [izimbra]
directory 	moto/ 	March 17, 2011 	rest of the group folders added [JoGr]
directory 	nav/ 	March 17, 2011 	Navigation group folder added [JoGr]
directory 	proto/ 	March 17, 2011 	rest of the group folders added [JoGr]
directory 	sched/ 	March 17, 2011 	creating scheduler group folder [JoGr]
directory 	src/ 	April 11, 2011 	Improved Makefile (works for Serial) [PeMiAn]
directory 	stab/ 	1 day ago 	Added makefile in src that is needed for root make... [Adam Debbiche]
directory 	tint/ 	March 17, 2011 	test and integration folder added [JoGr]
directory 	ui/ 	March 17, 2011 	UI group folder added [JoGr]
file 	Makefile-template 	April 11, 2011 	Improved Makefile (works for Serial) [PeMiAn]
file 	README 	April 01, 2011 	removed trash from README [izimbra]
file 	checksize 	April 05, 2011 	initial libs, headers and makefile [PeMiAn]
	name 	age 	
history
message
	.. 		
directory 	bin/ 	April 18, 2011 	updated code to follow coding standards some more [AdaDeb]
directory 	doc/ 	April 18, 2011 	updated code to follow coding standards some more [AdaDeb]
directory 	lib/ 	April 13, 2011 	Added new make file that now compiles both for pc ... [AdaDeb]
directory 	src/ 	1 day ago 	Added makefile in src that is needed for root make... [Adam Debbiche]
directory 	test/ 	May 03, 2011 	cleaning up strange .DS_Store [Huilin Juniette Shi]
file 	Makefile 	1 day ago 	fixed a bug in the make file [Adam Debbiche]
file 	README 	April 18, 2011 	Fixed some bugs, code now follows code standards a... [AdaDeb]
	name 	age 	
history
message
	.. 		
file 	.gitignore 	April 27, 2011 	Cleaning...updated the ignore file so git ignores ... [AdaDeb]
file 	Makefile 	1 day ago 	Added makefile in src that is needed for root make... [Adam Debbiche]
file 	main.c 	April 20, 2011 	fixed stuff [AdaDeb]
file 	read_mg.c 	April 28, 2011 	the magn data should now work according to a real ... [AdaDeb]
file 	stab.h 	April 27, 2011 	Added filter to the arduino stuff now. Still needs... [AdaDeb]
file 	stab_filter.c 	April 27, 2011 	accel data is now converted to scaled value [AdaDeb]
file 	stab_interface.h 	April 18, 2011 	updated make file so that the group uses make stab... [AdaDeb]
file 	stab_main.c 	about 19 hours ago 	added msg sending to stab_main [lillamiu]
file 	stab_ra.c 	April 27, 2011 	accel data is now converted to scaled value [AdaDeb]
file 	stab_rb.c 	2 days ago 	Some integration work, height from stab_rb is now ... [Adam Debbiche]
file 	stab_rg.c 	April 27, 2011 	Fixed a bug in the write_data method that prevente... [AdaDeb]
file 	stab_sim.c 	April 20, 2011 	Updated make file, make stab no longer needed. A g... [AdaDeb]

    Edit this file

Txt 100644 121 lines (86 sloc) 3.4 kb

    raw
    blame
    history

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121

	

########################### Added by Adam 09/05/11 #########################

LIB_SRC=read_mg.c stab_filter.c stab_main.c stab_ra.c stab_rb.c stab_rg.c stab_sim.c

LIB_OBJ = $(LIB_SRC:.c=.o)

%.o: %.c
$(GLOBAL_CC) -c -I. $*.c $(GLOBAL_CFLAGS)

lib-pc: $(LIB_OBJ)
ar rvs ../lib/libstab.a $(LIB_OBJ)

lib-mega: $(LIB_OBJ)
@echo Objects: $(LIB_OBJ)
avr-ar rvs ../lib/libstab.a $(LIB_OBJ)

clean:
rm -f *.o

##########################################################################






# #######################################################################
# Makefile for inclusion by other projects
# heavily copied from original libarduino sources
# (c) 2009, for all changes belong to Henrik Sandklef
# which lead to the current version
# (c) 2011, for all changes belong to Petre Mihail Anton
#######################################################################

# Change device names to corespond to your system
# Description
# =============
# DUE_USB_DEV - used for Arduino DueMillaNove
# UNO_USB_DEV - used for Arduino Uno
#
# here are various USB device names for various operating system and Arduinos:
# if you're using GNU/Linux (Ubuntu/Debian/Fedora.....):
# DUE_USB_DEV=/dev/ttyUSB0
# UNO_USB_DEV=/dev/ttyACM0
# if you're using Mac:
# DUE_USB_DEV=
# UNO_USB_DEV=/dev/tty.usbmodemfa141 (check name!)
# Hint:
# Launch the Arduino program to see what your USB device
# is called (look under the port settings)

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

# echo '#include "WProgram.h"' > $(TARGET).c
# cat $(PROG).c >> $(TARGET).c

#$(OBJ): $(SRC)
# cd bin && \
# avr-gcc -c -g -Os -ffunction-sections -fdata-sections -mmcu=$(MMCU) -DARDUINO=22 -DF_CPU=$(F_CPU) -Wall -Wstrict-prototypes \
# -Wa,-ahlms=$(PROG).lst -fno-exceptions -I../include ../$(SRC)

##-DENABLE_PWM

#$(PROG): MMCU=atmega328p
#$(PROG): LIB=coreuno
#$(PROG): $(OBJ)
# avr-gcc $(OBJ) lib/lib$(LIB).a -Wl,-Map=$(PROG).map,--cref -mmcu=$(MMCU) -DARDUINO=22 -Iinclude -lm -Llib \
# -fno-exceptions -ffunction-sections -fdata-sections -l$(LIB) -o bin/$(PROG).x
# @ echo "Test passed"

#install: $(OBJ)
# avr-gcc $(OBJ) lib/lib$(LIB).a -Wl,-Map=$(PROG).map,--cref -mmcu=$(MMCU) -Iinclude -lm -Llib \
# -fno-exceptions -ffunction-sections -fdata-sections -l$(LIB) -o bin/$(PROG).elf
# cd bin && avr-objcopy -O srec $(PROG).elf $(PROG).rom
## checksize $(PROG).elf
# avrdude -p $(MMCU) -P $(USB_PORT) -c $(STK) -b $(BAUD) -F -u -U flash:w:bin/$(PROG).rom


#mega: clean install

#uno: clean install

#pc: clean
# gcc -DPC $(SRC) -o bin/$(PROG).x

#clean:
# @ cd bin && rm -f *.o *.rom *.elf *.map *~ *.lst *.x
# @ echo "Project cleaned"

#help:
# @ echo "Check your code includes 'WProgram.h' \nCheck you call 'init()'"

## reprogram the fuses for the right clock source
##fuse:
## avrdude -p atmega168 -c stk200 -U lfuse:w:0x62:m

.PHONY : clean uno due mega install help lib




Dedicated Server Powered by the Dedicated Servers and
Cloud Computing of Rackspace Hosting¨

    Blog
    Support
    Training
    Job Board
    Shop
    Contact
    API
    Status

    © 2011 GitHub Inc. All rights reserved.
    Terms of Service
    Privacy
    Security

