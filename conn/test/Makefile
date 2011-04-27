default:
	@echo "test_clinet"
	@echo "test_server"
	@echo "tcpserver"
	@echo "to run the client test youve to run"
	@echo "tcpserver first"

test_client: client.c clienttest.c
	gcc clienttest.c -o clienttest.a -lcunit

test_server: server.c test_tcpserver.c
	gcc test_tcpserver.c -DTEST -o servertest.a -lcunit && ./servertest.a

tcpserver: tcpserver.c
	gcc tcpserver.c -o tcpserver
