#  
#  Makefile for Abstract Navigation's base directory
#  
#  Created on: 10 apr 2011
#      Author: Shan Huang
#  

default:
	@echo "make indoor      produces binary in src/"
	@echo "make clean       recursively clean up subdirs"
	@echo "make unit        run unit tests"
    # @echo "make gcov        run unit tests with gcov"
	@echo "make valg        run unit tests with valgrind"

indoor:
	cd src/indoor && $(MAKE) indoor

clean:
	cd src/indoor && $(MAKE) clean
	cd test/unit && $(MAKE) clean

unit:
	cd src/indoor && $(MAKE) testobjs
	cd test/unit && $(MAKE) unit

valg: clean
	cd src/indoor && $(MAKE) testobjsv
	cd test/unit && $(MAKE) valg