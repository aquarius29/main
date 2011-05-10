
default:
	@echo "--- Normal compilation ----------------------------------"
	@echo "make pn     produces binary in src/"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean    recursively clean up subdirs"
	@echo " "
	@echo "--- Verification and debugging --------------------------"
	@echo "make unit      run unit tests"

pn:
	cd src && $(MAKE) pn

clean:
	cd src && $(MAKE) clean
	cd test/unit && $(MAKE) clean

unit:
	cd src && $(MAKE) testobjs
	cd test/unit && $(MAKE) unit
