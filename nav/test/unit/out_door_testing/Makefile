#  Makefile for Abstract Navigation's base directory
#  
#  Created on: 10 apr 2011
#      Amanpreet
#  

default:
	@echo "make outdoor      produces binary in src/"
	@echo "make clean       recursively clean up subdirs"
	@echo "make unit        run unit tests"
    # @echo "make gcov        run unit tests with gcov"
	@echo "make valg        run unit tests with valgrind"

indoor:
	cd src/outdoor && $(MAKE) outdoor

clean:
	cd src/outdoor && $(MAKE) clean
	cd test/unit && $(MAKE) clean

unit:
	cd src/outdoor && $(MAKE) testobjs
	cd test/unit && $(MAKE) unit

valg: clean
	cd src/outdoor && $(MAKE) testobjsv
	cd test/unit && $(MAKE) valg 