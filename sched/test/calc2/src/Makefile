calc: calc.h calc.c main.c
	gcc -o calc calc.c main.c $(EXTRAGCCFLAGS)

testobjs: calc.h calc.c 
	gcc -o calc.o -c calc.c $(EXTRAGCCFLAGS)

testobjscov: EXTRAGCCFLAGS+= -fprofile-arcs -ftest-coverage
testobjscov: testobjs

testobjsgdb: EXTRAGCCFLAGS+= -g
testobjsgdb: testobjs

gdb: EXTRAGCCFLAGS+= -g
gdb: calc

gcovcalc: EXTRAGCCFLAGS+= -fprofile-arcs -ftest-coverage
gcovcalc: calc

clean:
	rm -f calc calc.exe calc.o *.gcov *.gcda *.gcno
