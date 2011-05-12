/*!@author Kristofer Hansson Aspman
 * @file moto_recv.c
 * @version v0.02
 * @date 2011-05-08
 *
 * @brief Intended to pick up the message held by the protocol.\n
 * Uses the types msg and msg_pointer defined in\n
 * moto_msg_manipulation.h.
 *
 * @history 2011-04-14: Created the file.
 *          2011-05-08: Now reads from the protocol.
 */

#include "moto_recv.h"
#include "proto_lib.h"

uint8_t inputFromProto;
msg binary;
/* binaryStruct, only for moto_rcvMsg2 */
msgStruct binaryStruct;

msg_pointer moto_recvMsg(void){

/* get message from protocol group and return it */


    inputFromProto = proto_read_motor();
    binary = INT_TO_BITFIELD(&inputFromProto);
    return &binary;

}


msgStructPtr moto_recvMsg2(void){

/* get message struct from protocol group and return it */


    //binaryStruct = (msgStruct)proto_read_motor2();   
    //return &binaryStruct;
    return (msgStructPtr)proto_read_motor2();

}

