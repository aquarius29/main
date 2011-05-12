/*	function main() to run the cam_client */

#include "cam_client.c"

int main(int argc, char *argv[]) 
{

initialize_client (argc,argv);
create_socket();
establish_connection();
receive_and_convert();
display();

return 0;
}
