default:
	@echo "--- Normal compilation ----------------------------------"
	@echo "make calc     produces binary in src/"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean    recursively clean up subdirs"
	@echo " "
	@echo "--- Verification and debugging --------------------------"
	@echo "make unit         run unit tests"
	@echo "make gcovunit     run unit tests with gcov (statement coverage)"
	@echo "make gcovunitb    run unit tests with gcov (branch coverage)"
	@echo "make memunit      run unit tests with valgrind"

calc:
	cd src && $(MAKE) calc

clean:
	cd src && $(MAKE) clean
	cd tests/unit && $(MAKE) clean

unit:
	cd src && $(MAKE) testobjs
	cd tests/unit && $(MAKE) unit

gcovunit: clean
	cd src && $(MAKE) testobjscov
	cd tests/unit && $(MAKE) gcovunit

gcovunitb: clean
	cd src && $(MAKE) testobjscov
	cd tests/unit && $(MAKE) gcovunitb

memunit: clean
	cd src && $(MAKE) testobjsgdb
	cd tests/unit && $(MAKE) memunit

