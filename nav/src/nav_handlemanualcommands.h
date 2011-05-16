#ifndef NAV_HANDLEMANUALCOMMANDS_H
#define NAV_HANDLEMANUALCOMMANDS_H

#include <stdint.h>
#include "nav_indoorstructure.h"

typedef struct manualCommand {
    int value;
    struct manualCommand *next;
} manualCommand;

void receiveManualMovementCommand(uint8_t command);
void initManualToAuto(tile *end);
void initManualStart(tile *start);

#endif /* NAV_HANDLEMANUALCOMMANDS_H */