/*!
* @file proto_init.c
* @brief Initializing protocol
* @author Mihail
*/

#include <proto_lib.h>

void proto_init(void){
    createDefaultmove_to_nav();
    createDefaultmove();
    createDefaultstabatt();
    createDefaultstabgyro();
}
