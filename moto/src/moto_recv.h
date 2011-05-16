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
