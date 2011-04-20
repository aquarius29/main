default:
	@echo "--- Normal Robin compilation ----------------------------"
	@echo "make normal_robin produces binary in src/arduino/robin_impl_src"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean    recursively clean up subdirs"
	@echo " "
	@echo "--- Normal compilation : windows style ------------------"
	@echo "make windows_normal_robin    procudes binary in sched/"
	@echo " "
	@echo "--- Cleaning up : windows style -------------------------"
	@echo "make windows_clean    recursively clean up subdirs"

normal_batman:
	cd src/arduino/batman_impl && $(MAKE) normal

clean:
	cd src/arduino/batman_impl_src && $(MAKE) clean

windows_normal_robin:
	cd src\arduino\batman_impl_src && $(MAKE) windows_normal

windows_clean:
	del *.exe
	cd src\arduino\batman_impl_src && $(MAKE) windows_clean