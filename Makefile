# 
# Makefile for Abstract Navigation's base directory
# 
# Created on: 10 apr 2011
#     Author: Shan Huang
# 

default:
	@echo "--- Normal compilation ----------------------------------"
	@echo "make nav      produces binary in src/"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean    recursively clean up subdirs"
	@echo " "
	@echo "--- Verification and debugging --------------------------"
	@echo "make unit        run unit tests"
	@echo "make cov         run unit tests with gcov (branch coverage)"
	@echo "make val         run unit tests with valgrind"

nav:
	cd src && $(MAKE) nav

clean:
	cd src && $(MAKE) clean
	cd tests/unit && $(MAKE) clean

unit:
	cd src && $(MAKE) testobjsu
	cd tests/unit && $(MAKE) unit

cov: clean
	cd src && $(MAKE) testobjsg
	cd tests/unit && $(MAKE) cov

val: clean
	cd src && $(MAKE) testobjsv
	cd tests/unit && $(MAKE) val