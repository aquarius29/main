<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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

=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
/*! @author Kristofer Hansson Aspman
 * @file moto_recv.c
 * @version v0.01
 * @date 2011-04-14
 * @brief Intended to pick up the message held by the protocol
 */

int moto_recvMsg(void){

/* get message from protocol group and return it */

}
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
=======
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
  
    return (msgStructPtr)proto_read_motor2();
}

>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
