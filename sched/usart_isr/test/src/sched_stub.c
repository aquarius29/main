
#include "proto_stub.h"

void doSomeScheduling(void){
    proto_init();
    
    while (1) {
        proto_run();
        delay(2000);
    }
}