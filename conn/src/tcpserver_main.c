#include "tcpserver.c"

/*Author Michal Musialik*/


int main(void){

  host_setup();
  socket_create();
  //socket_reusing();
  socket_bind();
  socket_listening();
  new_socket_creation();
  data_passing();
  


}
