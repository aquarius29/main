#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "../src/conn_tcpclient.c"

/*!
    @author Ali Issa, Eugene Groshev
*/

void test1_create(void) {
    CU_ASSERT(socket_create() == 0);
}

void test2_connect(void) {
    int crap = socket_binding();
    CU_ASSERT(socket_connection() == 0);
}

/* 
void sendTo(void) {
    CU_ASSERT(sendMessage() == 2);
}

void receiveMessage(void) {
    CU_ASSERT(receive() == 2);
} 
*/

int main() {
    /**************************************************************************/
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    /**************************************************************************/
    /* add socket tests */

    CU_pSuite Client = CU_add_suite("TCP Client (conn_tcpclient.c)", NULL, NULL);
    CU_add_test(Client, "Creating a socket", test1_create);
    /**************************************************************************/
    /* add connect to server tests */

    CU_add_test(Client, "Connecting to a server", test2_connect);
    /**************************************************************************/
    /* add receive message from server tests 

    CU_pSuite Receive = CU_add_suite("Receive message from server", NULL, NULL);
    CU_add_test(Receive, "testing the receive function", receiveMessage);
    /**************************************************************************/
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
