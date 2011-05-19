/*
 * Function:    void sendMsg()
 * Author(s):   Björn Eriksson

 *
 * Description: sends a message as a struct to movement
 *              
 */
#include <stdint.h>  

/* from the header file, a struct which can be sent to the movement */

struct pulses{
    uint16_t right;
    uint16_t left;
    uint16_t front;
    uint16_t rear;
};

/* 
 * creates the struct, sends it to the movement with the current pulse,
 * will be discarded after sending.
 */

void sendMsg(void){
    struct pulses currentPulsess = {rightPulse, leftPulse, 
                                    frontPulse, rearPulse};
    proto_write_move(currentPulses);
}


