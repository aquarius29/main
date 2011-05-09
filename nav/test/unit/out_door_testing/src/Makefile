pn: pn.h pn.c main.c
	gcc -o pn pn.c main.c $(EXTRAGCCFLAGS)

testobjs: pn.h pn.c 
	gcc -o pn.o -c pn.c $(EXTRAGCCFLAGS)

gdb: EXTRAGCCFLAGS+= -g
gdb: pn

clean:
	rm -f pn pn.exe pn.o


