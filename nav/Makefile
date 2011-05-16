#  
#  Makefile for Abstract Navigation's base directory
#  
#  Created on: 10 apr 2011
#      Author: Shan Huang
#  

default:
	@echo "make simulation  produces binary in bin/"
	@echo "make clean       recursively clean up subdirs"
	@echo "make unit        run unit tests"
	@echo "make valg        run unit tests with valgrind"

simulation: 
	cd bin && $(MAKE) simulation

clean:
	cd bin && $(MAKE) clean
	cd test/unit && $(MAKE) clean

unit:
	cd bin && $(MAKE) testobjs
	cd test/unit && $(MAKE) unit

valg: clean
	cd bin && $(MAKE) testobjsv
	cd test/unit && $(MAKE) valg