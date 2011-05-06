
#include "proto_serial_port.h"
#include "proto_serial_comm.h"
#include "proto_serializer.h"
#include "port_test.h"

void port_test(void){
    int32_t portHandle;
    uint8_t data[] = {3, 1, 2, 3, '\0'};
    
    struct status navInfo;
    struct status *p_navInfo;
    
    uint8_t serializedData[DATA_BUFFER_LEN];
    
    p_navInfo = &navInfo;
    
    p_navInfo->uInt8 = 0x0A;
    p_navInfo->int8 = 0x09;
    p_navInfo->uInt16 = 0x0101;
    p_navInfo->int16 = 0x1F10;
    
    proto_serializeData(p_navInfo, serializedData);
    
    portHandle = proto_serialOpen();
    sleep(1);
    
    proto_serialSend(portHandle, data);
    
    sleep(2);
    proto_serialClose(portHandle);
}