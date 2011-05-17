#ifndef NAV_HANDLEMANUALCOMMANDS_H
#define NAV_HANDLEMANUALCOMMANDS_H

#include <stdint.h>
#include "nav_indoorstructure.h"

typedef struct manualCommand {
    int value;
    struct manualCommand *next;
} manualCommand;

/*Keep the thread running until it is killed externally*/
void initManualNavigation(void);
void receiveManualMovementCommand(uint8_t command);
void initManualToAuto(tile *end);
void initManualStart(tile *start);
void collisionOverManual(int32_t angle);

#endif /* NAV_HANDLEMANUALCOMMANDS_H */
