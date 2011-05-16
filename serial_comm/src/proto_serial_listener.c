
#define TRUE 1
#define FALSE 0

static doListen = FALSE;

static proto_serialListen(int32_t portHandle);


uint8_t proto_serialStartListen(int32_t portHandle){
    doListen = TRUE;
    proto_serialListen(portHandle);
    
    return 1;
}

uint8_t proto_serialStopListen(int32_t portHandle){
    doListen = FALSE;
    
    return 1;
}

static void proto_serialListen(int32_t portHandle){
    while (doListen == TRUE) {
        
    }
}