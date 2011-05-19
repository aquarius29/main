default:
	@echo "test_clinet"
	@echo "test_server"
	@echo "tcpserver"
	@echo "to run the client test youve to run"
	@echo "tcpserver first"

test_client: test_tcpclient.c
	gcc test_tcpclient.c -o clienttest.a -lcunit && ./clienttest.a

test_server: test_tcpserver.c
	gcc test_tcpserver.c -o servertest.a -lcunit && ./servertest.a

tcpserver: tcpserver.c
	gcc tcpserver.c -o tcpserver
