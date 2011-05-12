  

/* Author:                                          */

/* header file for the cam client program */

	void initialize_client (int argc, char *argv[]);
	void create_socket(void);
	void establish_connection(void);
	void receive_and_convert(void);
	void close_and_free(void);
	void Exit_Error_func(const char *msg);

