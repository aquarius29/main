#Author Michal Musialik
GCC 	= gcc
RM 	= rm -f
.SILENT:
#List of aviable options
default:
	@echo "------------------------------------------------------"
	@echo " tcpclient: to compile client - run 'tcpc' and IP"
	@echo "------------------------------------------------------"
	@echo " tcpserver: to compile server - run 'tcps' "	
	@echo "------------------------------------------------------"
	@echo " velo: to compile velocity - run 'velo' "
	@echo "------------------------------------------------------"
	@echo " mask_con: mask for convertation - mask_con "
	@echo "------------------------------------------------------"
	@echo " gethost: crating host gathering program - gethost "
	@echo "------------------------------------------------------"
	@echo " clean: to remove bin"
	@echo "------------------------------------------------------"

#Compiling the TCP client
tcpclient: tcpclient.c tcpclient_main.c 
	 $(GCC) tcpclient_main.c -o tcpc 

#Compiling the TCP server
#tcpserver: tcpserver.c tcpserver_main.c
tcpserver: src/tcpserver_main.c
	$(GCC) src/tcpserver_main.c -o bin/tcps 

#Compiling velocity controll
velo: velocity.c
	$(GCC) velocity.c -o velo  

#compiling maks for controll
mask_con: mask_con.c
	$(GCC) mask_con.c -o mask_con

#compiling host
gethost: gethost.c
	$(GCC) gethost.c -o gethost

#Removing creataed binary
clean:
	$(RM) tcpc tcps velo mask_con gethost


all_tcp: tcpserver tcpclient 