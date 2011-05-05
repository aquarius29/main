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
tcpclient: src/conn_tcpclient_main.c 
	 $(GCC) src/conn_tcpclient_main.c -o bin/tcpc 

#Compiling the TCP server
#tcpserver: tcpserver.c tcpserver_main.c
tcpserver: src/conn_tcpserver_main.c
	$(GCC) src/conn_tcpserver_main.c -o bin/tcps 

#Compiling velocity controll
velo: src/conn_velocity.c
	$(GCC) src/conn_velocity.c -o bin/velo  

#compiling maks for controll
mask_con: src/conn_mask_con.c
	$(GCC) src/conn_mask_con.c -o bin/mask_con

#compiling host
gethost: src/conn_gethost.c
	$(GCC) src/conn_gethost.c -o bin/gethost

#Removing creataed binary
clean:
	$(RM) bin/tcpc bin/tcps bin/velo bin/mask_con bin/gethost


all_tcp: ctcpserver tcpclient 