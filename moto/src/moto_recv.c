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
#include "../../proto_mega/src/proto_lib.h"

uint8_t inputFromProto;
msg binary;

msg_pointer moto_recvMsg(void){

/* get message from protocol group and return it */


    inputFromProto = proto_read_motor();
    binary = INT_TO_BITFIELD(&inputFromProto);
    return &binary;

}

