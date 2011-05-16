<<<<<<< HEAD
=======
#ifndef NAV_HANDLEMANUALCOMMANDS_H
#define NAV_HANDLEMANUALCOMMANDS_H

#include <stdint.h>
#include "nav_indoorstructure.h"

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
typedef struct manualCommand {
    int value;
    struct manualCommand *next;
} manualCommand;

<<<<<<< HEAD
void initManualCommandsList(void);
void receiveManualMovementCommand(int command);
void freeManualCommandList(void);

// non static variables for testing
// manualCommand *first;
// manualCommand *last;
=======
/*Keep the thread running until it is killed externally*/
void initManualNavigation(void);
void receiveManualMovementCommand(uint8_t command);
void initManualToAuto(tile *end);
void initManualStart(tile *start);
void collisionOverManual(int32_t angle);

#endif /* NAV_HANDLEMANUALCOMMANDS_H */
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
