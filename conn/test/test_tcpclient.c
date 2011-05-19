#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "client.c"

/*Author Ali issa*/

void testCreate(void) {
    CU_ASSERT(createSocket() == 2);
    CU_ASSERT(connectSocket() == 2);
}

void sendTo(void) {
    CU_ASSERT(sendMessage() == 2);
}

void receiveMessage(void) {
    CU_ASSERT(receive() == 2);
}

int main() {
    /**************************************************************************/
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    /**************************************************************************/
    /* add socket tests */

    CU_pSuite Createsocket = CU_add_suite("Create and Connect socket", NULL, NULL);
    CU_add_test(Createsocket, "testing to create a socket", testCreate);
    /**************************************************************************/
    /* add send message to server tests */

    CU_pSuite SendToServer = CU_add_suite("Send message to server", NULL, NULL);
    CU_add_test(SendToServer, "testing to send a message to server", sendTo);
    /**************************************************************************/
    /* add receive message from server tests */

    CU_pSuite Receive = CU_add_suite("Receive message from server", NULL, NULL);
    CU_add_test(Receive, "testing the receive function", receiveMessage);
    /**************************************************************************/
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
