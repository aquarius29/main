<<<<<<< HEAD
/*!@author Kristofer Hansson Aspman
 * @file moto_recv.h
 * @version v0.01
 * @date 2011-05-08
 *
 * @brief Header file belonging to moto_recv.c.\n
 * The functionality is described in the .c file.
 *
 * @history 2011-05-08: Now reads from the protocol.
 */

#include <stdint.h>
#include "moto_msg_manipulation.h"

msg_pointer moto_recvMsg(void);
=======
/*!@author Kristofer Hansson Aspman
 * @file moto_recv.h
 * @version v0.01
 * @date 2011-05-08
 *
 * @brief Header file belonging to moto_recv.c.\n
 * The functionality is described in the .c file.
 *
 * @history 2011-05-08: Now reads from the protocol.
 */
#ifndef MOTO_RECV_H
#define MOTO_RECV_H
#include <stdint.h>
#include "moto_msg_manipulation.h"

typedef struct _msgStruct {
    uint8_t msg1;
    uint8_t msg2;
    uint8_t msg3;
    uint8_t msg4;
    uint8_t msg5;
    uint8_t msg6;
    uint8_t msg7;
    uint8_t msg8;
} msgStruct, *msgStructPtr;   

msg_pointer moto_recvMsg(void);
msgStructPtr moto_recvMsg2(void);
#endif
>>>>>>> 0563398e31de42544502a0eaec1d08e9dc22c8e2
