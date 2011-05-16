#  
#  Makefile for Abstract Navigation's base directory
#  
#  Created on: 10 apr 2011
#      Author: Shan Huang
#  

default:
<<<<<<< HEAD
	@echo "make indoor      produces binary in bin/"
=======
	@echo "make simulation  produces binary in bin/"
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
	@echo "make clean       recursively clean up subdirs"
	@echo "make unit        run unit tests"
	@echo "make valg        run unit tests with valgrind"

<<<<<<< HEAD
indoor: 
	cd bin && $(MAKE) indoor
=======
simulation: 
	cd bin && $(MAKE) simulation
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

clean:
	cd bin && $(MAKE) clean
	cd test/unit && $(MAKE) clean

unit:
	cd bin && $(MAKE) testobjs
	cd test/unit && $(MAKE) unit

valg: clean
	cd bin && $(MAKE) testobjsv
	cd test/unit && $(MAKE) valg